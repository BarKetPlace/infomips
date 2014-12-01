#include <ctype.h>
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

//Affichage de l'instruction desassemblée
void print_disasm(definition def, union inst_poly mot)
{
	char* token=NULL;
	char* delim = " ";
	int i;
	char tempo[MAXSTR];
	tempo[0]='\0';
	
	//detail_def(def);
	//DEBUG_MSG("");
	if (def->type == 'R')
	{	//DEBUG_MSG("");
		printf("%s ",def->nom);
		strcpy(tempo,def->nom_op);
		token = strtok(tempo, delim) ;
		for (i=0;i<def->nb_op;i++)
		{
			//DEBUG_MSG("0x%08x", mot.code);
			//DEBUG_MSG(" 0x%08x 0x%08x 0x%08x ",mot.r.rd, mot.r.rt, mot.r.rs);
			
			//DEBUG_MSG("%s",token);
			if ( !strcmp(def->nom_op[i], "rd") ) printf("$%d ",mot.r.rd);
			if ( !strcmp(def->nom_op[i], "rt") ) printf("$%d ",mot.r.rt);
			if ( !strcmp(def->nom_op[i], "rs") ) printf("$%d ",mot.r.rs);
			//if ( !strcmp(token, "rt") ) printf("$%d ",mot.r.rt);
			token = strtok(NULL, delim);
		}
	}
	else if (def->type == 'I')
	{
		printf("%s ",def->nom);
		
		//token = strtok(def->nom_op, delim);
		for (i=0;i<def->nb_op;i++)
		{
			//DEBUG_MSG("0x%08x", mot.code);
			//DEBUG_MSG(" 0x%08x 0x%08x 0x%08x ",mot.r.rd, mot.r.rt, mot.r.rs);
			
			//DEBUG_MSG("%s",token);
			if ( !strcmp(def->nom_op[i], "rt") ) printf("$%d ",mot.i.rt);
			else if ( !strcmp(def->nom_op[i], "rs") ) printf("$%d ",mot.i.rs);
			else if ( !strcmp(def->nom_op[i], "imm") ) printf("%d ",mot.i.imm);
			//token = strtok(NULL, delim);
		}
		//DEBUG_MSG("");
		//DEBUG_MSG("%s",token);
	}
	else if (def->type == 'J')
	{	//puts(token);
		//DEBUG_MSG("");
		//puts(def->nom);
		printf("%s ",def->nom);
		//DEBUG_MSG("");
		//token = strtok(def->nom_op, delim);
		for (i=0;i<def->nb_op;i++)
		{
			if ( !strcmp(def->nom_op[i], "target") ) printf("0x%08x ",mot.j.target);
		}
		//else ERROR_MSG("Erreur dictionnaire: type J -> op=target");
		
	}
	printf("\n");
}

int disasm(mem memory, int adrr, int val, Liste dico)
{	//int val = swap_mot(val_);
	//printf("swap(0x%08x) = 0x%08x\n",val, val_swapped );
	//DEBUG_MSG(" 0x%08x: 0x%08x ",adrr, val);
	printf("0x%08x: 0x%08x ",adrr, val);
	union inst_poly mot;
	mot.code=val;	
	//DEBUG_MSG("");
	definition def =NULL;
	def = find_def(dico, mot);
	//DEBUG_MSG("");
	if (!def)  {//Si def == NULL
		printf("\n");
		WARNING_MSG(" Instruction inconnue ");
		return cmd_exit;
		}
	//detail_def(def);
	
	//printf("0x%08x: 0x%08x ",adrr, val);
	print_disasm(def, mot);
	return cmd_ok;
}


int disasm_(mem memory, registre* reg, int debut, int fin, Liste dico)
{	int i;
	char res[MAX_STR];
	int val, tmp;
	tmp =find_word(memory, debut, &val);
	uint32_t found_word;
	if ( tmp == cmd_unknown ) return tmp;
	
	
	//DEBUG_MSG("0x%08x", val);
	if (fin-debut<4)
	{	tmp = disasm(memory, debut ,val , dico);
		if (tmp != cmd_ok) //Si il y a eu un probleme
		{ 	
			WARNING_MSG("Erreur de desassemblage à l'adresse : 0x%08x",debut);
			return cmd_exit;
		}
			
		//printf("0x%08x: 0x%08x %s\n",debut, val, res);
		return cmd_ok;
	}

	
	for (i=debut;i<fin;i+=4)
	{	if ( find_word(memory, i, &val) == cmd_unknown ) return cmd_unknown;
		//DEBUG_MSG("0x%08x: 0x%08x",i, val);
		tmp = disasm(memory, i , val , dico);
		//DEBUG_MSG("0x%08x: 0x%08x",i, val);
		if ( tmp != cmd_ok ){
			WARNING_MSG("Erreur de desassemblage a l'adresse : 0x%08x",i);
			return cmd_exit;
		}
		//DEBUG_MSG(" ");
		//printf("0x%08x: 0x%08x %s\n",i, val, res);
	}
	
	
	return cmd_ok;
}

int disasmcmd(interpreteur inter, mem memory, registre* reg, Liste dico)
{	
	char* token;
	char* res[MAX_STR];
	uint32_t debut,fin,decalage,courant;
	token = get_next_token(inter);
	uint32_t found_word;

	if (token && is_hexa(token)){ //disasm HEXA
		sscanf(token, "%x", &debut); //DEBUG_MSG(" sfsg ");
		if (debut%4 != 0) debut = debut - (debut%4);
		if (debut>STOP_MEM) //L'adresse est trop haute (voir mem.h)
			{
				WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
				return cmd_exit;
			}
		token = get_next_token(inter);
			
		if (token && !strcmp(token, ":") ){ //disasm HEXA:
			
			token = get_next_token(inter);
			if ( token && is_hexa(token) ){//disasm HEXA:HEXA
				sscanf(token, "%x", &fin);
				if (fin%4 != 0) fin = fin -(fin%4);
				if (debut>STOP_MEM) //L'adresse est trop haute (voir mem.h)
				{
					WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
					return cmd_exit;
				}
				return disasm_(memory, reg, debut, fin, dico);
			}
			WARNING_MSG(" Usage disasm HEXA:HEXA ");
		}
		else if (token && !strcmp(token, "+")){//disasm HEXA+
			token = get_next_token(inter);
			if (token && is_valeur(token)){ //disasm HEXA+decalage
				sscanf(token, "%x", &decalage);
				if (decalage%4 != 0) decalage = decalage -(decalage%4);
				
				
				if (debut+decalage>STOP_MEM) //L'adresse est trop haute (voir mem.h)
				{
					WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
					return cmd_exit;
				}
				//DEBUG_MSG("");
				return disasm_(memory, reg, debut, debut+decalage, dico);
			}
			WARNING_MSG(" Usage disasm HEXA+val ");
		}
		else { //disasm HEXA (HEXA HEXA HEXA ...)
			
			if( find_word(memory, debut, &found_word) == cmd_unknown) return cmd_unknown;
			else disasm(memory,debut , found_word, dico);

			while(token && is_hexa(token))
			{	sscanf(token, "%x", &courant);
				if( find_word(memory, courant, &found_word) == cmd_unknown) return cmd_unknown;
				else disasm(memory,courant , found_word, dico);
				token = get_next_token(inter);
			}

			return cmd_ok ;
		}
		
	
	
	}
	else {
		WARNING_MSG(" Usage disasm <plage>+ ");
	}
	
	return cmd_exit;
}
