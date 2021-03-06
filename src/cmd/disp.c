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
	char* token; // sep; addr_fin;
	uint debut,fin, decalage,adr;
	token = get_next_token(inter);
	//int tmp;
	//uint val;
	int num_reg; //résultat de is_registre
	//byte valb = 0;
	if (token == NULL) //disp (null)
	{
		WARNING_MSG("Missing arguments");
		return cmd_exit;
	}
	
	if (!strcmp(token,"mem")) { //disp mem
		token = get_next_token(inter);
			
		if (token == NULL) //disp mem (null)
		{
			WARNING_MSG("Missing argument \"map\" or <plage>+");
			return cmd_exit;
		}
		
		else if (strcmp(token,"map")==0)//disp mem map
		{
			print_mem(memory);
			return cmd_ok;
		}

		else if (is_hexa(token)) //disp mem HEXA
		{	sscanf(token, "%x", &adr);
			token = get_next_token(inter);
			//DEBUG_MSG("");
			if (adr>STOP_MEM) //L'adresse est trop haute (voir mem.h)
			{
				WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
				return cmd_exit;
			}
			//DEBUG_MSG("sfsg token : %s", token);	


			
			if (token && !strcmp(token,":") )//disp mem HEXA:
			{	//DEBUG_MSG("sfsg");
			  debut = adr;
				token = get_next_token(inter);
				if (token && is_hexa(token) ) //disp mem HEXA:HEXA
				{	sscanf(token, "%x", &fin);		
					if (fin>STOP_MEM) //L'adresse est trop haute (voir mem.h)
					{
						WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
						return cmd_exit;
					}
					//disp mem HEXA:HEXA			avec 0<= HEXA,HEXA <= 0xfffff000
					if (fin>=debut) print_case_mem(memory, debut, fin-1);
					else print_case_mem(memory,fin,debut-1);
					return cmd_ok;
				}
				else { WARNING_MSG("Usage : disp mem HEXA:HEXA ");
						return cmd_exit; 
						}
			}
		
			else if ( token && !strcmp(token,"+") )//disp mem HEXA+
			{	//DEBUG_MSG("sfsg");
			  debut = adr;
				token = get_next_token(inter);
				if (token && is_valeur(token) ) //disp mem HEXA+val
				{	sscanf(token, "%d", &decalage);		
					if (debut+decalage>STOP_MEM) //HEXA+val est trop haute (voir mem.h)
					{
						WARNING_MSG("Highest adress: 0x%08x",STOP_MEM);
						return cmd_exit;
					}
				return print_case_mem(memory, debut, debut+decalage-1); 	

				}
			}
			
			else if ( token && is_hexa(token) ) //disp mem HEXA HEXA ...
			  { printf("0x%08x :: ", adr);
			    if(print_byte_mem(memory, adr)==cmd_unknown) return cmd_unknown;
			    printf("\n");
			    do {
			      
			      sscanf(token, "%x", &adr);
			      printf("0x%08x :: ", adr);
			      if(print_byte_mem(memory, adr)==cmd_unknown) return cmd_unknown;
			      printf("\n");
			      token = get_next_token(inter);
				  
			    } while (token && is_hexa(token));
			}

			else if (!token)//disp mem HEXA
			{       
			 printf("0x%08x :: ", adr);
			 print_byte_mem(memory, adr);
			 printf("\n");		
			}
			
			else {
			WARNING_MSG("USAGE: disp mem \"map\" or <plage>+");
			return cmd_unknown;
			}
			
		}
		else
		{
			WARNING_MSG("USAGE: disp mem \"map\" or <plage>+");
			return cmd_unknown;
		}
		return cmd_ok;	
			
	}

	else if (!strcmp(token,"reg"))//disp reg
	{	//DEBUG_MSG("");
		if (reg == NULL) WARNING_MSG("Registres non-chargés");
			
		token = get_next_token(inter);
		if (!token) {WARNING_MSG("Missing arguments"); return cmd_unknown;}
		if(!strcmp(token,"all")) { //disp reg all

			print_tab_reg(reg); 
			return cmd_ok; 
		}
		else if (token)//disp reg $.. $....
		{		
			while (token) {
				if (token[0] == '$' && is_valeur(token+1) ) {
					sscanf(token+1, "%d", &num_reg);
					print_reg(reg,num_reg);
				}
				else{
					num_reg = is_registre(token);
					if( !(num_reg) ) {
					WARNING_MSG("'%s' n'est pas un registre", token);
					}

				print_reg(reg,num_reg);
				}
				token = get_next_token(inter); //printf("%s\n",token);
				}
			
					
		}
	
	
		else
		{
			WARNING_MSG("Usage: disp \"reg\" \" all\"| $.. $..$..");
		}
	}

	else //disp "autre chose que reg ou mem"  
	{
		WARNING_MSG("Usage: disp \"mem\" | disp \"reg\"");
		return cmd_exit;
	}
	return cmd_ok;
}

