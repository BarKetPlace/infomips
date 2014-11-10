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
	instruction res;


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
	

	//Si tout est bon, on initialise le pc
	
	reg[pc].val = start;
	

	while(1) {	
	//DEBUG_MSG("%08x",reg[pc].val);

		if (reg[pc].val>text_start+text_taille) { //On verifie qu'on a pas atteint la fin de la zone text
			printf("******Fin du programme******\n");
			break;
		}

		//tmp = disasm_(memory, reg, reg[pc].val, reg[pc].val, dico);
		//if (tmp != cmd_ok) return cmd_unknown;
		
		res = calloc(1,sizeof(*res));
		tmp = adresse_to_instruc(memory, reg[pc].val, dico, res);
		if (tmp != cmd_ok) {
			free(res);
			return cmd_unknown;
		}
		detail_def(res->def);
		free(res);
		reg[pc].val+=4;
	}

	return cmd_ok;
}

int adresse_to_instruc(mem memory, int adrr, Liste dico, instruction res)
{	int i;
	uint32_t val;
	definition tmp;

	union inst_poly mot;
	if ( find_val(memory, adrr, &(res->inst.code)) != cmd_ok ) { 
		WARNING_MSG("Impossible de trouver un mot en 0x%08x", adrr);	
		return cmd_unknown;
	}
	//DEBUG_MSG("%08x",val);

	//mot.code = val;
	
	
	//union inst_poly mot;

	//definition def = NULL;
	res->def = find_def(dico,res->inst);
	//DEBUG_MSG("");

	if (!res->def)  {//Si def == NULL
		printf("\n");
		WARNING_MSG(" Instruction inconnue ");
		return cmd_exit;
	}
	//detail_def(tmp);
	
	
	/*
	res->def->sign = tmp->sign;DEBUG_MSG("");
	res->def->masq = tmp->masq;
	strcpy(res->def->nom, tmp->nom);

	res->def->type = tmp->type;
	res->def->nb_op = tmp->nb_op;
	for(i=0;i<tmp->nb_op;i++)
		{	
			res->def->nom_op[i] = strdup(tmp->nom_op[i]);//DEBUG_MSG("");
		}*/
	
	
	return cmd_ok;
}
