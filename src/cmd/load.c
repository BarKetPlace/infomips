#include <stdio.h>
#include <stdlib.h>



#include "cmd.h"
#include "mem.h"
#include "notify.h"
#include "bits.h"
#include "formats.h"
#include "types.h"
#include "syms.h"
#include "section.h"
#include "reg.h"
#include "is_.h"
#include "relocator.h"

#define START_MEM 0x0

// Cette fonction calcule le nombre de segments à prevoir
// Elle cherche dans les symboles si les sections predefinies
// s'y trouve
// parametres :
//  symtab : la table des symboles
//
// retourne le nombre de sections trouvées

unsigned int get_nsegments(stab symtab,char* section_names[],int nb_sections) {
    unsigned int n=0;
    int i;
    for (i=0; i<nb_sections; i++) {
        if (is_in_symbols(section_names[i],symtab)) n++;
    }
    return n;
}

int loadcmd(interpreteur inter, mem memory, registre* reg)
{/*
  ///////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// Chargement de la mémoire /////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////
	
  char *fichier = get_next_token(inter);
  if (memory->nseg) 
    {	WARNING_MSG("Un programme est déjà chargé en mémoire");
      WARNING_MSG("Liberation memoire");
      del_mem(memory);	
		
      INFO_MSG("Memoire liberee");

      memory = alloue_mem();
    }

  //Si on a specifie une adresse de depart
  char* token = get_next_token(inter);
  //uint32_t tmp;
	


  WARNING_MSG("Chargement de '%s' en mémoire",fichier);
  FILE* felf;
  FILE* pf_libc;
  //segment* seg=NULL;
	
  uint i,j;
  //Info machine
  unsigned int type_machine;
  unsigned int endianness;   //little ou big endian
  unsigned int bus_width;    // 32 bits ou 64 bits
  //Table des symboles
  stab symtab= new_stab(0); // table des symboles
  stab symtab_libc= new_stab(0); // table des symboles de la libc

  //Sections possibles
  char* section_names[NB_SECTIONS]= {TEXT_SECTION_STR,RODATA_SECTION_STR,DATA_SECTION_STR,BSS_SECTION_STR};
  unsigned int segment_permissions[NB_SECTIONS]= {R_X,R__,RW_,RW_};
  unsigned int next_segment_start; // compteur pour designer le début de la prochaine section

	pf_libc = fopen(PATH_TO_LIBC,"r");
    if (pf_libc == NULL) {
        ERROR_MSG("cannot open file %s", PATH_TO_LIBC);
    }
  	


	
  //Ouverture du fichier elf
	



  if (   (felf = fopen(fichier, "r") ) == NULL  )
    {
      ERROR_MSG(" Impossible d'ouvrir %s \n", fichier);
      return NULL;
    }

  //On vérifie que le nombre d'argument est correct et que le fichier est bien un fichier elf
  if ( (is_elf(fichier,  felf)) != cmd_ok ) 
    {	
      return cmd_unknown;
    }

	

    if (!assert_elf_file(pf_libc))
        ERROR_MSG("file %s is not an ELF file", PATH_TO_LIBC);


  //DEBUG_MSG("ok");
  //On récupère les informations sur la machine
  elf_get_arch_info(felf, &type_machine, &endianness, &bus_width);
  // et des symboles
  elf_load_symtab(felf, bus_width, endianness, &symtab);
  elf_load_symtab(pf_libc, bus_width, endianness, &symtab_libc);

  uint nsegments=0;
  nsegments = get_nsegments(symtab,section_names,NB_SECTIONS);
  nsegments += get_nsegments(symtab_libc,section_names,NB_SECTIONS);


  // initialiser la memoire virtuelle
  if (!init_mem(nsegments, reg, memory)) {
    WARNING_MSG("Erreur d'initialisation de la mémoire");
    return cmd_unknown;
  }
 

  next_segment_start = LIBC_MEM_END;
    printf("\ndebut : %08x\n",next_segment_start);
    j=0;

    // on alloue libc
    for (i=0; i<NB_SECTIONS; i++) {
        if (is_in_symbols(section_names[i],symtab_libc)) {
            elf_load_section_in_memory(pf_libc,memory, section_names[i],segment_permissions[i],next_segment_start);
            next_segment_start-= ((memory->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k suppérieur
            memory->seg[j].start._32 = next_segment_start;
//            print_segment_raw_content(&memory->seg[j]);
            j++;
        }
    }

    // on reloge libc
    for (i=0; i<j; i++) {
        reloc_segment(NULL, memory->seg[i], memory,endianness,NULL,&symtab_libc,pf_libc);
    }

    // on change le nom des differents segments de libc
    for (i=0; i<j; i++) {
        char seg_name [256]= {0};
        strcpy(seg_name,"libc");
        strcat(seg_name,memory->seg[i].name);
        free(memory->seg[i].name);
        memory->seg[i].name=strdup(seg_name);
    }

     // Si on a specifie une valeur de depart
  if (token && is_hexa(token) ) {
    sscanf(token, "%x", &next_segment_start);
    next_segment_start += (next_segment_start% 4);
    memory->start_mem = next_segment_start;
		
  }

  // Ne pas oublier d'allouer les differentes sections
  j=0;
  for (i=0; i<NB_SECTIONS; i++) {
    if (is_in_symbols(section_names[i],symtab)) {
      elf_load_section_in_memory(felf,memory, section_names[i],segment_permissions[i],next_segment_start);
      next_segment_start+= (((memory)->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k supérieurx
      //print_segment_raw_content(&memory->seg[j]);
      j++;
    }
  }

  for (i=0; i<nsegments; i++) {
    reloc_segment(felf, memory->seg[i], memory,endianness,&symtab,NULL,NULL );

  }
	
  //printf("\n------ Fichier ELF \"%s\" : sections lues lors du chargement ------\n", fichier) ;
  //print_mem(memory);

  //////////////////////////////////////////////////
  //////////////////////////////////////////////////
  //AFFICHAGE TABLE DES SYMBOLES
  stab32_print( symtab);
  stab32_print(symtab_libc);
  //////////////////////////////////////////////////
  //////////////////////////////////////////////////


  //if(!(init_tab_mem(memory))) WARNING_MSG("Problème de recopie de la mémoire");
  INFO_MSG("Programme chargé en mémoire avec succés");
  //print_mem( memory );
	
  //printf("\n\n");
  //DEBUG_MSG("%x",memory->start_mem);

// on fait le ménage avant de partir
    del_mem(memory);
    del_stab(symtab_libc);
    del_stab(symtab);
    fclose(felf);
    fclose(pf_libc);
    puts("");*/
  

    char* section_names[NB_SECTIONS]= {TEXT_SECTION_STR,RODATA_SECTION_STR,DATA_SECTION_STR,BSS_SECTION_STR};
    unsigned int segment_permissions[NB_SECTIONS]= {R_X,R__,RW_,RW_};

    unsigned int nsegments;
    int i=0,j=0;
    unsigned int type_machine;
    unsigned int endianness;   //little ou big endian
    unsigned int bus_width;    // 32 bits ou 64bits
    unsigned int next_segment_start = START_MEM; // compteur pour designer le début de la prochaine section

   // mem memory;  // memoire virtuelle, c'est elle qui contiendra toute les données du programme
    stab symtab= new_stab(0); // table des symboles
    stab symtab_libc= new_stab(0); // table des symboles de la libc
    FILE * pf_elf, *pf_libc;
/*
    if ((argc < 2) || (argc > 2)) {
        printf("Usage: %s <fichier elf> \n", argv[0]);
        exit(1);
    }
*/


	
	char *fichier = get_next_token(inter);
  if (memory->nseg) 
    {	WARNING_MSG("Un programme est déjà chargé en mémoire");
      WARNING_MSG("Liberation memoire");
      del_mem(memory);	
		
      INFO_MSG("Memoire liberee");

      memory = alloue_mem();
    }


	
  //Si on a specifie une adresse de depart
  char* token = get_next_token(inter);
  //uint32_t tmp;


    if ((pf_elf = fopen(fichier,"r")) == NULL) {
        ERROR_MSG("cannot open file %s", fichier);
    }

    if (!assert_elf_file(pf_elf))
        ERROR_MSG("file %s is not an ELF file", fichier);


    if ((pf_libc = fopen(PATH_TO_LIBC,"r")) == NULL) {
        ERROR_MSG("cannot open file %s", PATH_TO_LIBC);
    }

    if (!assert_elf_file(pf_libc))
        ERROR_MSG("file %s is not an ELF file", PATH_TO_LIBC);



    // recuperation des info de l'architecture
    elf_get_arch_info(pf_elf, &type_machine, &endianness, &bus_width);
    // et des symboles
    elf_load_symtab(pf_elf, bus_width, endianness, &symtab);
    elf_load_symtab(pf_libc, bus_width, endianness, &symtab_libc);


    nsegments = get_nsegments(symtab,section_names,NB_SECTIONS);
    nsegments += get_nsegments(symtab_libc,section_names,NB_SECTIONS);

	//stab32_print( symtab_libc);
	//stab32_print( symtab);


    // allouer la memoire virtuelle
    // initialiser la memoire virtuelle
  if (init_mem(nsegments, reg, memory)!= cmd_ok) {
    WARNING_MSG("Erreur d'initialisation de la mémoire");
    return cmd_unknown;
  }
	memory->start_mem = START_MEM;
    next_segment_start = LIBC_MEM_END;
    //printf("\ndebut : %08x\n",next_segment_start);
    j=0;

    // on alloue libc
    for (i=0; i<NB_SECTIONS; i++) {
        if (is_in_symbols(section_names[i],symtab_libc)) {
            elf_load_section_in_memory(pf_libc,memory, section_names[i],segment_permissions[i],next_segment_start);
            next_segment_start-= ((memory->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k suppérieur
            memory->seg[j].start._32 = next_segment_start;
//            print_segment_raw_content(&memory->seg[j]);
            j++;
        }
    }
	//print_mem(memory);
	WARNING_MSG("Relocation de la lib c");
    // on reloge libc
    for (i=0; i<j; i++) {
        reloc_segment(pf_libc, memory->seg[i], memory,endianness,&symtab_libc,NULL,NULL);
    }
	INFO_MSG("Relocation de la libc terminee");

//print_mem(memory);


    // on change le nom des differents segments de libc
    for (i=0; i<j; i++) {
        char seg_name [256]= {0};
        strcpy(seg_name,"libc");	
	DEBUG_MSG("Changement de nom de : %s", memory->seg[i].name);
        strcat(seg_name,memory->seg[i].name);
        free(memory->seg[i].name);
	//	memset(memory->seg[i].name, '\0', strlen(memory->seg[i].name));
	//	strcpy(memory->seg[i].name, seg_name);
       	memory->seg[i].name=strdup(seg_name);
    }
	//print_mem(memory);
	
//DEBUG_MSG("");

	//Adresse de départ de la mémoire virtuelle
	// Si on a specifie une valeur de depart
 	if (token && is_hexa(token) ) {
    sscanf(token, "%x", &next_segment_start);
    next_segment_start += (next_segment_start% 4);
    memory->start_mem = next_segment_start;
		
  }
	
    // On va chercher les sections du fichier
    int k =j;
    next_segment_start = memory->start_mem;
    for (i=0; i<NB_SECTIONS; i++) {
        if (is_in_symbols(section_names[i],symtab)) {
            elf_load_section_in_memory(pf_elf,memory, section_names[i],segment_permissions[i],next_segment_start);
            next_segment_start+= ((memory->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k suppérieur
            //print_segment_raw_content(&memory->seg[j]);
            j++;
        }
    }
	//print_mem(memory);
	WARNING_MSG("Relocation du programme");
    // on reloge chaque section du fichier
    for (i=k; i<j; i++) {
        reloc_segment(pf_elf, memory->seg[i], memory,endianness,&symtab,&symtab_libc,pf_libc);

    }
	INFO_MSG("Relocation du programme terminee");
   print_mem(memory);
	DEBUG_MSG("%d %d",memory->nseg, nsegments);
	memory->nseg = nsegments+1;
		WARNING_MSG("Chargement de la pile");
		if (!init_stack(memory, reg, memory->nseg))
		{
			ERROR_MSG("Erreur lors du chargement de la pile");
    		}
		INFO_MSG("Pile initialisée");
	
	print_mem(memory);

   // printf("\n------ Fichier ELF \"%s\" : sections lues lors du chargement ------\n", fichier) ;
    //print_mem(memory);
    //stab32_print( symtab);
	//DEBUG_MSG("");
    //stab32_print( symtab_libc);
	//stab32_print(symtab);
    // on fait le ménage avant de partir
   
   // del_stab(symtab_libc);
    //del_stab(symtab);
    fclose(pf_elf);
    fclose(pf_libc);
    puts("");
    return cmd_ok;
}

/*
  return cmd_ok;
}*/
