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
	int tmp;
	uint val;
	if (token == NULL) //disp (null)
	{
		WARNING_MSG("Missing arguments");
		return CMD_EXIT_RETURN_VALUE;
	}
	
	if (!strcmp(token,"mem")) { //disp mem
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return CMD_EXIT_RETURN_VALUE;
		}
		token = get_next_token(inter);
			
		if (token == NULL) //disp mem (null)
		{
			WARNING_MSG("Missing argument \"map\" or <plage>+");
			return CMD_EXIT_RETURN_VALUE;
		}
		
		else if (strcmp(token,"map")==0)//disp mem map
		{
			print_mem(memory);
			return CMD_OK_RETURN_VALUE;
		}
			
			
		else if (is_hexa(token)) //disp mem HEXA
		{	sscanf(token, "%x", &debut);
			token = get_next_token(inter);
			//DEBUG_MSG("");
			if (debut>STOP_MEM) //L'adresse est trop haute (voir mem.h)
			{
				WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
				return CMD_EXIT_RETURN_VALUE;
			}
			//DEBUG_MSG("sfsg token : %s", token);	


			
			if (token && !strcmp(token,":") )//disp mem HEXA:
			{	//DEBUG_MSG("sfsg");
				token = get_next_token(inter);
				if (token && is_hexa(token) ) //disp mem HEXA:HEXA
				{	sscanf(token, "%x", &fin);		
					if (fin>STOP_MEM) //L'adresse est trop haute (voir mem.h)
					{
						WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
						return CMD_EXIT_RETURN_VALUE;
					}
					//disp mem HEXA:HEXA			avec 0<= HEXA,HEXA <= 0xfffff000
					if (!(fin<debut)) print_case_mem(memory, debut, fin);
					else print_case_mem(memory,fin,debut);
					return CMD_OK_RETURN_VALUE;
				}
				else { WARNING_MSG("Usage : disp mem HEXA:HEXA ");
						return CMD_EXIT_RETURN_VALUE; 
						}
			}		
			else if ( token && !strcmp(token,"+") )//disp mem HEXA+
			{	//DEBUG_MSG("sfsg");
				token = get_next_token(inter);
				if (token && is_valeur(token) ) //disp mem HEXA+val
				{	sscanf(token, "%x", &decalage);		
					if (debut+decalage>STOP_MEM) //HEXA+val est trop haute (voir mem.h)
					{
						WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
						return CMD_EXIT_RETURN_VALUE;
					}
				return print_case_mem(memory, debut, debut+decalage); 	

				}
			}
			
			else if ( token && is_hexa(token) ) //disp mem HEXA HEXA ...
			{	
				do {	
					sscanf(token, "%x", &adr);
					tmp = find_val(memory, adr, &val);
					if (tmp==CMD_UNKOWN_RETURN_VALUE)
					{	printf("\n");
						ERROR_MSG("L'adresse 0x%08x n'est pas allouee", adr);
						return tmp;
					}
					else {
						printf("0x%08x : ",adr);
						print_byte_mem(memory, adr, val);
					}
	
					printf("\n");	
					
					token = get_next_token(inter);
				} while (token && is_hexa(token));
			}
			else if (!token)
			{	tmp = find_val(memory, adr, &val);
					if (tmp==CMD_UNKOWN_RETURN_VALUE)
					{	printf("\n");
						ERROR_MSG("L'adresse 0x%08x n'est pas allouee", adr);
						return tmp;
					}
					else {
						printf("0x%08x : ",adr);
						print_byte_mem(memory, adr, val);
					}
			}

			else {
			WARNING_MSG("USAGE: disp mem \"map\" or <plage>+");
			return CMD_EXIT_RETURN_VALUE;
			}
			return CMD_OK_RETURN_VALUE;
		}
	}

	else if (!strcmp(token,"reg"))//disp reg
	{	//DEBUG_MSG("");
		if (reg == NULL) WARNING_MSG("Registres non-chargés");
			
		token = get_next_token(inter);
		if (!token) {WARNING_MSG("Missing arguments"); return CMD_EXIT_RETURN_VALUE;}
		if(!strcmp(token,"all")) { //disp reg all

			print_tab_reg(reg); 
			return CMD_OK_RETURN_VALUE; 
		}
		else //disp reg $.. $....
		{		
			do {
				if(!( print_reg(reg, is_registre(token) + 1))) WARNING_MSG("'%s' n'est pas un registre", token);
				token = get_next_token(inter); //printf("%s\n",token);
				}
			while (token != NULL);
					
		}
	
	}
	else //disp "autre chose que reg ou mem"  
	{
		WARNING_MSG("Usage: disp \"mem\" | disp \"reg\"");
		return CMD_EXIT_RETURN_VALUE;
	}
	return CMD_OK_RETURN_VALUE;
	}

