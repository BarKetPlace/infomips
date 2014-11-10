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
#include "dico.h"

int runcmd(interpreteur inter, mem memory, registre* reg, Liste dico)
{
	char* token;
	int start = START_MEM, reste;
	uint32_t courante, tmp, text_start, text_taille, val;
	token = get_next_token(inter);

	union inst_poly mot;
	definition def;




	//Si on a specifie une adresse de depart
	if (token && is_hexa(token)) { sscanf(token, "%x", &start); }
	reste = start%4;
	if(reste) { //Si l'adresse de départ n'est pas multiple de 4
		WARNING_MSG("0x%x n'est pas multiple de 4 :::: Les plus proches: 0x%x ou 0x%x", start, start-reste, start+4-reste);
		return cmd_unknown;
	}



	//On verifie que l'adresse a laquelle on commence est bien dans la zone text, 
	//On en profite pour recuperer l'adresse de start et la taille de la zone text
	
	if ( is_text_adresse(memory, start, &text_start, &text_taille) == cmd_unknown ) {
		WARNING_MSG("/!\\ Text seg: 0x%08x -> 0x%08x",text_start,text_taille);
		return cmd_unknown;
	}
	

	//Si tout est bon, on initialise le pc au début de la zone text
	
	reg[pc].val = start;
	

	while(! (reg[pc].val>text_start+text_taille)) {	

		//tmp = disasm_(memory, reg, reg[pc].val, reg[pc].val, dico);
		//if (tmp != cmd_ok) return cmd_unknown;
		
		//On va chercher le mot de l'instruction à l'adresse indiquée par le pc
		if ( find_val(memory, reg[pc].val, &(mot.code)) != cmd_ok ) { 
			WARNING_MSG("Impossible de trouver un mot en 0x%08x", reg[pc].val);	
			return cmd_unknown;
		}
		
		//On va ensuite chercher la definition correspondante
		if ( !(def = find_def(dico, mot) ) ){ 
			WARNING_MSG("Impossible de trouver une definition pour le mot 0x%08x en 0x%08x", mot.code ,reg[pc].val);	
			return cmd_unknown;
		}
		
		//On execute ensuite la fonction def->f sur le mot
		//def->f();
		

		print_disasm(def, mot);
	
		reg[pc].val+=4;
	}
	printf("******Fin du programme******\n");
	return cmd_ok;
}
