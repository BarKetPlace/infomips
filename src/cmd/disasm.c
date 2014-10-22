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



int disasm(mem memory, int adrr, int val, Liste dico)
{	//int val_swapped = swap_mot(val);
	//printf("swap(0x%08x) = 0x%08x\n",val, val_swapped );
	
	printf("0x%08x: 0x%08x ",adrr, val);
	instruc mot;
	mot.code=val;	
	//DEBUG_MSG("");
	definition def =NULL;
	def = find_def(dico, mot);
	//detail_def(def);
	//DEBUG_MSG("");
	if (!def)  {printf("\n"); return CMD_UNKOWN_RETURN_VALUE;}//Si def == NULL
	//detail_def(def);
	print_disasm(def, mot);

	return CMD_OK_RETURN_VALUE;
}


int disasm_(mem memory, registre* reg, int debut, int fin, Liste dico)
{	int i;
	char res[MAX_STR];
	int val = find_val(memory, debut);
	int tmp=10;
	//DEBUG_MSG("");
	if (fin-debut<4)
	{	tmp = disasm(memory, debut ,val , dico);
		if (tmp != CMD_OK_RETURN_VALUE) //Si il y a eu un probleme
		{ 	
			WARNING_MSG("Erreur de desassemblage � l'adresse : 0x%08x",debut);
			return CMD_UNKOWN_RETURN_VALUE;
		}
			
		//printf("0x%08x: 0x%08x %s\n",debut, val, res);
		return CMD_OK_RETURN_VALUE;
	}

	
	for (i=debut;i<fin;i+=4)
	{	val = find_val(memory, i );
		//DEBUG_MSG("0x%08x: 0x%08x",i, val);
		tmp = disasm(memory, i ,val , dico);
		//DEBUG_MSG(" %d ",tmp);
		if ( tmp != CMD_OK_RETURN_VALUE ){
			WARNING_MSG("Erreur de desassemblage a l'adresse : 0x%08x",i);
			return CMD_UNKOWN_RETURN_VALUE;
		}
		//DEBUG_MSG(" ");
		//printf("0x%08x: 0x%08x %s\n",i, val, res);
	}
	
	
	return CMD_OK_RETURN_VALUE;
}

int disasmcmd(interpreteur inter, mem memory, registre* reg, Liste dico)
{	
	char* token;
	char* res[MAX_STR];
	uint32_t debut,fin,decalage;
	token = get_next_token(inter);
	if (token && is_hexa(token)){ //disasm HEXA
		sscanf(token, "%x", &debut); //DEBUG_MSG(" sfsg ");
		if (debut%4 != 0) debut = debut - (debut%4);
		if (debut>STOP_MEM) //L'adresse est trop haute (voir mem.h)
			{
				WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
				return CMD_UNKOWN_RETURN_VALUE;
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
					return CMD_UNKOWN_RETURN_VALUE;
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
					return CMD_UNKOWN_RETURN_VALUE;
				}
				//DEBUG_MSG("");
				return disasm_(memory, reg, debut, debut+decalage, dico);
			}
			WARNING_MSG(" Usage disasm HEXA+val ");
		}
		else { //DEBUG_MSG("");
			//printf("0x%08x",debut);
			if (!disasm(memory,debut , find_val(memory, debut), dico)) return CMD_UNKOWN_RETURN_VALUE;
			
			return CMD_OK_RETURN_VALUE ;
		}
		
	
	
	}
	else {
		WARNING_MSG(" Usage disasm <plage>+ ");
	}
	
	return CMD_UNKOWN_RETURN_VALUE;
}
