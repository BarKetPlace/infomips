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

int setcmd(interpreteur inter, mem memory, registre *reg)

{
	char *token=get_next_token(inter);
	char r[128], s[128];
	int j, adr;
	uint32_t byte_;
	uint32_t word_t;
	if (token == NULL) //set (null)
	{
		WARNING_MSG("Missing arguments");
		return cmd_unknown;
	}
	
	if (!strcmp(token,"mem"))  //set mem
	{
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return cmd_unknown;
		}
		
		token = get_next_token(inter);
		//DEBUG_MSG("ok");
			
		if (token == NULL) //set mem (null)
		{
			WARNING_MSG("Missing arguments <type> <adresse> <valeur>");
			return cmd_unknown;
		}

		else if (!strcmp(token,"byte")) //set mem byte
		{
			token = get_next_token(inter);
			//DEBUG_MSG("ok");

			if (token == NULL) //set mem <type> (null)
			{
				WARNING_MSG("Missing arguments <adresse> <valeur>");
				return cmd_unknown;
			}
		
			//DEBUG_MSG("ok");

			if (is_adresse(token)) //set mem byte <adresse>
			{
				//&adresse=token;
				sscanf(token,"%x",&adr);
				DEBUG_MSG("0x%08x",adr);
				token=get_next_token(inter);
				//DEBUG_MSG("ok");

				if (token == NULL) //set mem byte <adresse> (null)
				{
					
					WARNING_MSG("Missing argument <valeur>");
					return cmd_unknown;
				}
			
				//probleme is_valeur pour les hexas

				else if (is_hexa(token) || is_valeur(token)) //set mem byte <adresse> <valeur>
				{
					//DEBUG_MSG("ok");
					if (is_valeur(token)) // valeur entiere
					{      
						sscanf(token, "%d", &byte_);
						
						if ( (byte_)>256) {
						  DEBUG_MSG("");
						  WARNING_MSG("%d ne tient pas sur 1 octet",byte_);
						  return cmd_unknown;
						}
						
						else {
						  load_byte(memory,adr,byte_);
						  DEBUG_MSG("L'adresse 0x%08x (0x%08x) contient la valeur %d", adr, &byte_, byte_);
						  return cmd_ok;
						  }
					}
					else if (is_hexa(token)) // valeur hexadecimale
					{
						sscanf(token, "%x", &byte_);
						if ( (byte_)>256) {
						  DEBUG_MSG("");
						  WARNING_MSG("%x ne tient pas sur 1 octet",byte_);
						  return cmd_unknown;
						}
						
						load_byte(memory,adr,byte_);
						DEBUG_MSG("L'adresse 0x%08x (0x%08x) contient la valeur 0x%02x", adr, &byte_, byte_);
						return cmd_ok;
					}
					else {return cmd_unknown;}
				}

				else
				{      
					WARNING_MSG("Wrong argument: must be <valeur>");
					return cmd_unknown;
				}
				
			}
			else 
			{	
				WARNING_MSG("Wrong argument: must be <adresse>");
				return cmd_unknown;
			}
		}
			
		else if (!strcmp(token,"word")) //set mem word
		{
			token = get_next_token(inter);
			//DEBUG_MSG("ok");

			if (token == NULL) //set mem word (null)
			{
				WARNING_MSG("Missing arguments <adresse> <valeur>");
				return cmd_unknown;
			}
		
			//DEBUG_MSG("ok");

			if (is_adresse(token)) //set mem word <adresse>
			{
				//&adresse=token;
				sscanf(token,"%x",&adr);
				DEBUG_MSG("0x%08x",adr);
				token=get_next_token(inter);
				//DEBUG_MSG("ok");

				if (token == NULL) //set mem word <adresse> (null)
				{
					
					WARNING_MSG("Missing argument <valeur>");
					return cmd_unknown;
				}
			
				//probleme is_valeur pour les hexas

				else if (is_hexa(token) || is_valeur(token)) //set mem word <adresse> <valeur>
				{
					//DEBUG_MSG("ok");
					if (is_valeur(token)) // valeur entiere
					{
						sscanf(token, "%d", &word_t);
						load_word(memory,adr,word_t);
						DEBUG_MSG("L'adresse 0x%08x (0x%08x) contient la valeur %d", adr, &word_t, word_t);
						return cmd_ok;
					}
					else if (is_hexa(token)) // valeur hexadecimale
					{
						sscanf(token, "%x", &word_t);
						load_word(memory,adr,word_t);
						DEBUG_MSG("L'adresse 0x%08x (0x%08x) contient la valeur 0x%08x", adr, &word_t, word_t);
						return cmd_ok;
					}
					else {return cmd_unknown;}
				}

				else
				{	
					WARNING_MSG("Wrong argument: must be <valeur>");
					return cmd_unknown;
				}
				
			}
			else 
			{	
				WARNING_MSG("Wrong argument: must be <adresse>");
				return cmd_unknown;
			}
		}
		else
		{
			WARNING_MSG("Wrong argument: must be <type>");
			return cmd_unknown;
		}
		
	}
	else if (!strcmp(token,"reg"))  //set reg
	{
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return cmd_unknown;
		}
		token = get_next_token(inter);
		//DEBUG_MSG("ok");
		
		if (token == NULL) //set reg (null)
		{
			WARNING_MSG("Missing argument <registre>");
			return cmd_unknown;
		}

		else if ((is_registre(token))!=-1) //set reg <registre>
		{	
			//DEBUG_MSG("ok");
			strcpy(r, token);
			//DEBUG_MSG("ok");
			token = get_next_token(inter);
			//DEBUG_MSG("ok");

			if (token == NULL) //set reg <registre> (null)
			{
				WARNING_MSG("Missing argument <valeur>");
				return cmd_unknown;
			}
		

			if (is_valeur(token)||is_hexa(token)) //set reg <registre> <valeur>
			{
				
				j=transf_reg(reg, r);
				//DEBUG_MSG("%d",j);
				if (is_valeur(token)) // valeur entiere
				{
					sscanf(token, "%d", &reg[j].val);
					return cmd_ok;
				}
				else if (is_hexa(token)) // valeur hexadecimale
				{
					sscanf(token, "%x", &reg[j].val);
					return cmd_ok;
				}
				else {return cmd_unknown;}
			}

			else 
			{	
				WARNING_MSG("Wrong argument: must be <valeur>");
				return cmd_unknown;
			}
		}
		else
		{
			WARNING_MSG("Wrong argument: must be <registre>");
			return cmd_unknown;
		}
	}
	else //set "autre chose que reg ou mem"  
	{
		WARNING_MSG("Usage: set \"mem\" | set \"reg\"");
		return cmd_unknown;
	}
	return cmd_ok;

}
		



