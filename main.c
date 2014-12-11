#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>


#include "mem.h"
#include "notify.h"
#include "bits.h"
#include "formats.h"
#include "types.h"
#include "syms.h"
#include "section.h"
#include "reg.h"
#include "cmd.h"
#include "is_.h"
#include "emulateur.h"
#include "dico.h"
#include "typesmem.h"
#include "fct.h"
/**
*
* @brief parse la chaine courante de l'interpreteur à la recherche d'une commande, et execute cette commande.
* @param inter l'interpreteur qui demande l'analyse
* @return cmd_ok si la commande s'est exécutée avec succès (0)
* @return cmd_exit si c'est la commande exit. Dans ce cas, le programme doit se terminer. (-1)
* @return cmd_unknown si la commande n'est pas reconnue. (-2)
* @return tout autre nombre (eg tout nombre positif) si erreur d'execution de la commande
*/

int execute_cmd(interpreteur inter, mem memory, registre* reg, Liste dico, Liste_int* pbreaklist) {
    //DEBUG_MSG("input '%s'", inter->input);
    char cmdStr[MAX_STR];
	
	
    memset( cmdStr, '\0', MAX_STR );

    /* gestion des commandes vides, commentaires, etc*/
    if(strlen(inter->input) == 0
            || sscanf(inter->input, "%s", cmdStr) == 0
            || strlen(cmdStr) == 0
            || cmdStr[0] == '#') { /* ligne commence par # => commentaire*/
        return cmd_ok;
    }
	
	//if (is_conform_line(inter) != cmd_ok) return cmd_unknown;
    /*on identifie la commande avec un premier appel à get_next_token*/
	//DEBUG_MSG("ok");
    char * token = get_next_token(inter);

    if(strcmp(token, "exit") == 0) {
	DEBUG_MSG("");
        exitcmd(inter, memory, reg, dico, *pbreaklist);
		exit(EXIT_SUCCESS);
    }
    if(strcmp(token, "test") == 0) {
        return testcmd(inter);
    }
    if(strcmp(token, "load") == 0)
 	{
		return loadcmd(inter, memory, reg);
	}
	if(strcmp(token, "disp") == 0){
		//print_segment_raw_content(memory->seg);
		return dispcmd(inter, memory, reg);
	}
	if(strcmp(token, "set") == 0){
		return setcmd(inter, memory, reg);
	}
	
	if(strcmp(token, "assert") == 0){
		return assertcmd(inter, memory, reg);
	}

	if(strcmp(token, "disasm") == 0){
		return disasmcmd(inter, memory, reg, dico);
	}
	if(strcmp(token, "run") == 0){
		return runcmd(inter, memory, reg, dico, *pbreaklist);
	}
	if(!strcmp(token, "step")){
	  token = get_next_token(inter);
	  if(token && !strcmp(token,"into")){
	    return step_intocmd(memory,reg,dico);
	  }
	  else if (!token){
	    return cmd_ok;
	  }

	}
	if(!strcmp(token, "break")){
		return breakcmd(inter, memory, pbreaklist);
	}
		if(!strcmp(token, "debug")){
		return debugcmd(inter, memory, reg);
	}
	if(!strcmp(token, "resume")){
		return resumecmd(inter, memory, reg);
		}



	WARNING_MSG("Unknown Command : '%s'", cmdStr);
    return cmd_unknown;
}



/**
 * Programme principal
 */

int main ( int argc, char *argv[] ) {
    //exemples d'utilisation des macros du fichier notify.h
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]); /* macro INFO_MSG */
   // WARNING_MSG("Un message WARNING_MSG !"); /* macro INFO_MSG */
   // DEBUG_MSG("Un message DEBUG_MSG !"); /* macro DEBUG_MSG : uniquement si compil en mode DEBUG_MSG */
    interpreteur inter=init_inter(); /* structure gardant les infos et états de l'interpreteur*/
    FILE *fp = NULL; /* le flux dans lequel les commandes seront lues : stdin (mode shell) ou un fichier */

    if ( argc > 2 ) {
        usage_ERROR_MSG( argv[0] );
        exit( EXIT_FAILURE );
    }
    if(argc == 2 && strcmp(argv[1], "-h") == 0) {
        usage_ERROR_MSG( argv[0] );
        exit( EXIT_SUCCESS );
    }

    /*par defaut : mode shell interactif */
    fp = stdin;
    inter->mode = INTERACTIF;
    if(argc == 2) {
        /* mode fichier de commandes */
        fp = fopen( argv[1], "r" );
        if ( fp == NULL ) {
            perror( "fopen" );
            exit( EXIT_FAILURE );
        }
        inter->mode = SCRIPT;
    }
	mem memory=NULL;
	registre* reg=NULL;
	memory=alloue_mem();
	reg=alloue_reg();

	WARNING_MSG("Chargement des registres");
	if (!(init_reg(reg) ) )
	{	ERROR_MSG("Probleme dans l'initialisation des registres");
		return cmd_exit;
	}
	INFO_MSG("Registres chargés");

	WARNING_MSG("Chargement du dictionnaire d'instructions");
	Liste dico =  read_dico("./src/dico/dico.txt");
	INFO_MSG("Dictionnaire d'instructions chargé");
	//visualiser(dico);
	int res;
	Liste_int* pbreaklist = calloc(1, sizeof(*pbreaklist));
    /* boucle infinie : lit puis execute une cmd en boucle */
    while ( 1 ) {

      //DEBUG_MSG("");
        if (acquire_line( fp, inter)  == 0 ) {
            /* Une nouvelle ligne a ete acquise dans le flux fp*/
	  //printf("%d\n", known_cmd(inter->input));
	
            res = execute_cmd(inter, memory, reg, dico, pbreaklist); /* execution de la commande */
			
            // traitement des erreurs
            switch(res) {
            case cmd_ok:
                break;
            case cmd_exit://DEBUG_MSG("");
	      //sortie propre du programme 
	      if ( fp != stdin ) {
                fclose( fp );               		
                del_inter(inter);
		del_mem(memory);INFO_MSG("Liberation memoire");	
		del_reg(reg);INFO_MSG("Liberation des registres");
		del_dico(dico);INFO_MSG("Liberation du dictionnaire d'instructions");
                exit(EXIT_SUCCESS);
	      }
	      break;
	    case cmd_unknown:
	      //DEBUG_MSG("");
	      if ( fp != stdin ) { //Mode fichier; on sort
		fclose( fp );	//DEBUG_MSG("");
		exitcmd(inter, memory, reg, dico, *pbreaklist);
		exit(EXIT_SUCCESS);
	      }
	      break;
            default://DEBUG_MSG("");
                // erreur durant l'execution de la commande 
                // En mode "fichier" toute erreur implique la fin du programme ! 
                if (inter->mode == SCRIPT) {
                    fclose( fp );
                    exitcmd(inter, memory, reg, dico, *pbreaklist);
		    //macro ERROR_MSG : message d'erreur puis fin de programme !
		    exit(EXIT_SUCCESS);
		} 
		/*else {
		      ERROR_MSG("ERREUR DETECTEE. Aborts");
		      exit(EXIT_SUCCESS);
		      }*/
                    
                
                break;
            }
   
	}
	//DEBUG_MSG("");	
        if( inter->mode == SCRIPT && feof(fp) ) {
             //mode fichier, fin de fichier => sortie propre du programme 
            DEBUG_MSG("FIN DE FICHIER");
            fclose( fp );
	    exitcmd(inter, memory, reg, dico, *pbreaklist);
            exit(EXIT_SUCCESS);
        }
    }
    /* tous les cas de sortie du programme sont gérés plus haut*/
    ERROR_MSG("SHOULD NEVER BE HERE\n");
}
