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

int setcmd(interpreteur inter, mem memory, registre *reg, int adresse)

{
	char *token=get_next_token(inter);
	char *r;
	int j;
	if (token == NULL) //set (null)
	{
		WARNING_MSG("Missing arguments");
		return CMD_UNKOWN_RETURN_VALUE;
	}
	
	if (!strcmp(token,"mem"))  //set mem
	{
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return CMD_UNKOWN_RETURN_VALUE;
		}
		token = get_next_token(inter);
			
		if (token == NULL) //set mem (null)
		{
			WARNING_MSG("Missing arguments <type> <adresse> <valeur>");
			return CMD_UNKOWN_RETURN_VALUE;
		}

		else if ((is_type(token))) //set mem <type>
		{	
			token = get_next_token(inter);

			if (token == NULL) //set mem <type> (null)
			{
				WARNING_MSG("Missing arguments <adresse> <valeur>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
			token=get_next_token(inter);

			if (is_adresse(token)) //set mem <type> <adresse>
			{
				token=get_next_token(inter);

				if (token == NULL) //set mem <type> <adresse> (null)
				{
					WARNING_MSG("Missing argument <valeur>");
					return CMD_UNKOWN_RETURN_VALUE;
				}
			
				else if (is_valeur(token)) //set mem <type> <adresse> <valeur>
				{
				
					sscanf(token, "%x", &adresse);
					return CMD_OK_RETURN_VALUE;
				}

				else
				{	
					WARNING_MSG("Wrong argument: must be <valeur>");
					return CMD_UNKOWN_RETURN_VALUE;
				}
			}
			else 
			{	
				WARNING_MSG("Wrong argument: must be <adresse>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
		}
		else
		{
			WARNING_MSG("Wrong argument: must be <type>");
			return CMD_UNKOWN_RETURN_VALUE;
		}
		
	}
	else if (!strcmp(token,"reg"))  //set reg
	{
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return CMD_UNKOWN_RETURN_VALUE;
		}
		token = get_next_token(inter);
		
		if (token == NULL) //set reg (null)
		{
			WARNING_MSG("Missing arguments <registre>");
			return CMD_UNKOWN_RETURN_VALUE;
		}

		else if ((is_registre(token))==-1) //set reg <registre>
		{	
			sscanf(token, "%s", &r);
			token = get_next_token(inter);

			if (token == NULL) //set mem <registre> (null)
			{
				WARNING_MSG("Missing arguments <registre>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
			token=get_next_token(inter);

			if (is_valeur(token)) //set reg <registre> <valeur>
			{
			
				j=transf_reg(reg, r);
				sscanf(token, "%x", &reg[j].val);
				return CMD_OK_RETURN_VALUE;
			}

			else 
			{	
				WARNING_MSG("Wrong argument: must be <valeur>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
		}
		else
		{
			WARNING_MSG("Wrong argument: must be <registre>");
			return CMD_UNKOWN_RETURN_VALUE;
		}
	}
	else //set "autre chose que reg ou mem"  
	{
		WARNING_MSG("Usage: set \"mem\" | set \"reg\"");
		return CMD_UNKOWN_RETURN_VALUE;
	}
	return CMD_OK_RETURN_VALUE;
<<<<<<< HEAD
	}
		*/

}
		
>>>>>>> 9b5713b6191d23620af3961e8b9d7914804da1ab
