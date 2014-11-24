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
	int j, adr, val;
	int* valeur;
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

		else if ((is_type(token))) //set mem <type>
		{	
			strcpy(s,token);
			token = get_next_token(inter);
			//DEBUG_MSG("ok");

			if (token == NULL) //set mem <type> (null)
			{
				WARNING_MSG("Missing arguments <adresse> <valeur>");
				return cmd_unknown;
			}
		
			//DEBUG_MSG("ok");

			if (is_adresse(token)) //set mem <type> <adresse>
			{
				//&adresse=token;
				sscanf(token,"%x",&adr);
				DEBUG_MSG("0x%08x",adr);
				token=get_next_token(inter);
				//DEBUG_MSG("ok");

				if (token == NULL) //set mem <type> <adresse> (null)
				{
					
					WARNING_MSG("Missing argument <valeur>");
					return cmd_unknown;
				}
			
				//probleme is_valeur pour les hexas

				else if (is_registre(token) || is_valeur(token)) //set mem <type> <adresse> <valeur>
				{
					//DEBUG_MSG("ok");
					find_val(memory, adr, &valeur);
					DEBUG_MSG("0x%08x",&valeur);
					if (is_valeur(token)) // valeur entiere
					{
						sscanf(token, "%d", &val);
						DEBUG_MSG("%d", valeur);
						valeur=val;
						DEBUG_MSG("L'adresse 0x%08x (0x%08x) contient la valeur %d", adr, &valeur, valeur);
						return cmd_ok;
					}
					else if (is_hexa(token)) // valeur hexadecimale
					{
						sscanf(token, "%x", &val);
						DEBUG_MSG("%08x", valeur);
						valeur=val;
						DEBUG_MSG("L'adresse 0x%08x (0x%08x) contient la valeur 0x%08x", adr, &valeur, valeur);
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
		DEBUG_MSG("ok");
		
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
		



