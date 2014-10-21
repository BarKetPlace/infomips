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


int assertcmd(interpreteur inter, mem memory, registre *reg, uint adresse)
{
	char *token=get_next_token(inter);
	int valf;

	if (token == NULL) //set (null)
	{
		WARNING_MSG("Missing arguments");
		return CMD_UNKOWN_RETURN_VALUE;
	}
	
		
	if (!strcmp(token,"reg")) { //assert reg
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return CMD_UNKOWN_RETURN_VALUE;
		}
		token = get_next_token(inter);
		
		if (token == NULL) //assert reg (null)
		{
			WARNING_MSG("Missing arguments <registre>");
			return CMD_UNKOWN_RETURN_VALUE;
		}

		else if ((is_registre(token))) //assert reg registre
		{	
			token = get_next_token(inter);

			if (token == NULL) //assert reg registre (null)
			{
				WARNING_MSG("Missing arguments <registre>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
			token=get_next_token(inter);

			else if (is_valeur(token)) //assert reg registre valeur
			{
			//...


			

			find_val(memory, adresse);



			}

			else 
			{	
				WARNING_MSG("Wrong argument: must be <valeur>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
		else
		{
			WARNING_MSG("Wrong argument: must be <registre>");
			return CMD_UNKOWN_RETURN_VALUE;
		}

	else if ((is_type(token)) { //assert word or byte
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return CMD_UNKOWN_RETURN_VALUE;
		}
		token = get_next_token(inter);
		
		if (token == NULL) //assert word or byte (null)
		{
			WARNING_MSG("Missing arguments <adresse>");
			return CMD_UNKOWN_RETURN_VALUE;
		}

		else if ((is_adresse(token))) //assert word or byte adresse
		{	
			token = get_next_token(inter);

			if (token == NULL) //assert word or byte adresse (null)
			{
				WARNING_MSG("Missing arguments <valeur>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
			token = get_next_token(inter);
			truc
			else if (is_valeur(token)) //assert word or byte adresse valeur
			{
			


			
			valf=find_val(memory, adresse);
			

			}

			else 

			{	
				WARNING_MSG("Wrong argument: must be <valeur>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
		else
		{
			WARNING_MSG("Wrong argument: must be <adresse>");
			return CMD_UNKOWN_RETURN_VALUE;
		}

	else //assert "autre chose que reg ou word ou byte"  
	{
		WARNING_MSG("Usage: assert \"word\" | assert \"reg\" | assert \"byte\"");
		return CMD_UNKOWN_RETURN_VALUE;
	}
	return CMD_OK_RETURN_VALUE;
	}
