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


int disasm(mem memory, int val, char* res)
{	
	//printf("\t0x%08x\t%s\n", val, res);
	return CMD_OK_RETURN_VALUE;
}


int disasm_(interpreteur inter, mem memory, registre* reg, int debut, int fin)
{	int i;
	char res[MAX_STR];
	int val;
	if (fin-debut<4 && !disasm(memory, find_val(memory, debut), res ) ){
		WARNING_MSG("Erreur de desassemblage a l'adresse : 0x%08x",i);
		return CMD_UNKOWN_RETURN_VALUE;
	}
	
	for (i=debut;i<fin;i+=4)
	{	val = find_val(memory, i );
		
		if (disasm(memory, val, res) != CMD_OK_RETURN_VALUE){
			WARNING_MSG("Erreur de desassemblage a l'adresse : 0x%08x",i);
			return CMD_UNKOWN_RETURN_VALUE;
		}
		
		printf("0x%08x: 0x%08x %s\n",i, val, res);
		
		
	}
	
	
	return CMD_OK_RETURN_VALUE;
}




int disasmcmd(interpreteur inter, mem memory, registre* reg)
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
				return disasm_(inter, memory, reg, debut, fin);
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
				
				return disasm_(inter, memory, reg, debut, debut+decalage);
			}
			WARNING_MSG(" Usage disasm HEXA+val ");
		}
		else { //disasm HEXA
			DEBUG_MSG("");
			printf("0x%08x",debut);
			if (!disasm(memory, find_val(memory, debut),res)) return CMD_UNKOWN_RETURN_VALUE;
			
			return CMD_OK_RETURN_VALUE ;
		}
		
	
	
	}
	else {
		WARNING_MSG(" Usage disasm <plage>+ ");
	}
	
	return CMD_UNKOWN_RETURN_VALUE;
}
