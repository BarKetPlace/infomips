#include <stdio.h>
#include <stdlib.h>
#include "reg.h"
#include "cmd.h"
#include "emulateur.h"
#include "is_.h"
#include "notify.h"
#include "mem.h"

int dispcmd(interpreteur inter, mem memory, registre* reg)
{	
	char* token, sep, addr_fin;
	uint debut,fin, decalage,adr;
	token = get_next_token(inter);
	
	if (token == NULL) //disp (null)
	{
		WARNING_MSG("Missing arguments");
		return CMD_UNKOWN_RETURN_VALUE;
	}
	
	if (!strcmp(token,"mem")) { //disp mem
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return CMD_UNKOWN_RETURN_VALUE;
		}
		token = get_next_token(inter);
			
		if (token == NULL) //disp mem (null)
		{
			WARNING_MSG("Missing argument \"map\" or <plage>+");
			return CMD_UNKOWN_RETURN_VALUE;
		}
		
		else if (strcmp(token,"map")==0)//disp mem map
		{
			print_mem(memory);
			return CMD_OK_RETURN_VALUE;
		}
			
			
		else if (is_hexa(token)) //disp mem HEXA
		{	sscanf(token, "%x", &debut);
			token = get_next_token(inter);
			
			if (debut>STOP_MEM) //L'adresse est trop haute (voir mem.h)
			{
				WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
				return CMD_UNKOWN_RETURN_VALUE;
			}
			//DEBUG_MSG("sfsg token : %s", token);	


			
			if (token && !strcmp(token,":") )//disp mem HEXA:
			{	DEBUG_MSG("sfsg");
				token = get_next_token(inter);
				if (token && is_hexa(token) ) //disp mem HEXA:HEXA
				{	sscanf(token, "%x", &fin);		
					if (fin>STOP_MEM) //L'adresse est trop haute (voir mem.h)
					{
						WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
						return CMD_UNKOWN_RETURN_VALUE;
					}
					//disp mem HEXA:HEXA			avec 0<= HEXA,HEXA <= 0xfffff000
					if (!(fin<debut)) print_case_mem(memory, debut, fin);
					else print_case_mem(memory,fin,debut);
					return CMD_OK_RETURN_VALUE;
				}
				else { WARNING_MSG("Usage : disp mem HEXA:HEXA ");
						return CMD_UNKOWN_RETURN_VALUE; 
						}
			}		
			else if ( token && !strcmp(token,"+") )
			{	DEBUG_MSG("sfsg");
				token = get_next_token(inter);
				if (token && is_valeur(token) ) //disp mem HEXA+val
				{	sscanf(token, "%x", &decalage);		
					if (debut+decalage>STOP_MEM) //L'adresse est trop haute (voir mem.h)
					{
						WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
						return CMD_UNKOWN_RETURN_VALUE;
					}
				print_case_mem(memory, debut, debut+decalage);	
				
				return CMD_OK_RETURN_VALUE;
				}
			}
			print_case_mem(memory, debut, debut);
			if ( token && is_hexa(token) )
			{	
				
				do {	
					sscanf(token, "%x", &adr);
					print_case_mem(memory, adr, adr);
					token = get_next_token(inter);
				} while (token && is_hexa(token));
			}
			else{
			WARNING_MSG("USAGE: disp mem \"map\" or <plage>+");
			return CMD_UNKOWN_RETURN_VALUE;
			}
			return CMD_OK_RETURN_VALUE;
		}
	}

	else if (!strcmp(token,"reg"))//disp reg
	{	//DEBUG_MSG("");
		if (reg == NULL) WARNING_MSG("Registres non-chargés");
			
		token = get_next_token(inter);
		if (!token) {WARNING_MSG("Missing arguments"); return CMD_UNKOWN_RETURN_VALUE;}
		if(!strcmp(token,"all")) { //disp reg all
			//DEBUG_MSG("");
			print_tab_reg(reg); 
			return CMD_OK_RETURN_VALUE; 
		}
		else //disp reg $.. $....
		{		
			do {
				print_reg(reg, is_registre(token));
				token = get_next_token(inter); //printf("%s\n",token);
				}
			while (token != NULL);
					
		}
	
	}
	else //disp "autre chose que reg ou mem"  
	{
		WARNING_MSG("Usage: disp \"mem\" | disp \"reg\"");
		return CMD_UNKOWN_RETURN_VALUE;
	}
	return CMD_OK_RETURN_VALUE;
	}

