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


int assertcmd(interpreteur inter, mem memory, registre *reg)
{
	char *token=get_next_token(inter);
	char r[128];
	int j, adresse;
	int val_f_r, val_f_a;
	int val_t_a, val_t_r=0;

	if (token == NULL) //assert (null)
	{
		WARNING_MSG("Missing arguments");
		return CMD_UNKOWN_RETURN_VALUE;
	}
	
		
	if (!strcmp(token,"reg")) //assert reg
	{
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return CMD_UNKOWN_RETURN_VALUE;
		}
		token = get_next_token(inter);
		DEBUG_MSG("ok");
		
		if (token == NULL) //assert reg (null)
		{
			WARNING_MSG("Missing arguments <registre>");
			return CMD_UNKOWN_RETURN_VALUE;
		}

		else if ((is_registre(token))!=-1) //assert reg <registre>
		{	
			DEBUG_MSG("ok");
			strcpy(r,token);
			token = get_next_token(inter);
			puts(token);

			if (token == NULL) //assert reg <registre> (null)
			{
				WARNING_MSG("Missing arguments <registre>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
			
			
			else if (is_valeur(token) || is_hexa(token)) //assert reg registre valeur
			{
				
				DEBUG_MSG("ok");		
				j=transf_reg(reg, r);
				DEBUG_MSG("%d",j);

					if (is_valeur(token)) // valeur entiere
					{
						sscanf(token, "%d", &val_t_r); 	DEBUG_MSG("%d",val_t_r);
						if (val_t_r==reg[j].val) {DEBUG_MSG("bon"); return CMD_OK_RETURN_VALUE;}
						else {DEBUG_MSG("pas bon"); return CMD_UNKOWN_RETURN_VALUE;}
					}
					else if (is_hexa(token)) // valeur hexadecimale
					{
						sscanf(token, "%x", &val_t_r); 	DEBUG_MSG("%d",val_t_r);
						if (val_t_r==reg[j].val) {DEBUG_MSG("bon"); return CMD_OK_RETURN_VALUE;}
						else {DEBUG_MSG("pas bon"); return CMD_UNKOWN_RETURN_VALUE;}
					}
					else {return CMD_UNKOWN_RETURN_VALUE;}
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
	else if (is_type(token)) //assert word or byte
	{
		 // La mémoire
		if (memory == NULL) //Probleme avec le chargement de la mémoire
		{
			WARNING_MSG("Memoire non-chargée");
			return CMD_UNKOWN_RETURN_VALUE;
		}
		token = get_next_token(inter);
		DEBUG_MSG("ok");
		
		if (token == NULL) //assert word or byte (null)
		{
			WARNING_MSG("Missing arguments <adresse>");
			return CMD_UNKOWN_RETURN_VALUE;
		}

		else if (is_adresse(token)) //assert word or byte <adresse>
		{	
			DEBUG_MSG("ok");
			sscanf(token, "%x", &adresse);
			token = get_next_token(inter);

			if (token == NULL) //assert word or byte <adresse> (null)
			{
				WARNING_MSG("Missing arguments <valeur>");
				return CMD_UNKOWN_RETURN_VALUE;
			}
			
			DEBUG_MSG("ok");

			//token = get_next_token(inter);
	
			if (is_valeur(token)|| is_hexa(token)) //assert word or byte <adresse> <valeur>
			{
				val_f_a=find_val(memory, adresse);

					if (is_valeur(token)) // valeur entiere
					{
						sscanf(token, "%d", &val_t_a);
						if (val_t_a==val_f_a) {DEBUG_MSG("bon"); return CMD_OK_RETURN_VALUE;}
						else {DEBUG_MSG("pas bon"); return CMD_UNKOWN_RETURN_VALUE;}
					}
					else if (is_hexa(token)) // valeur hexadecimale
					{
						sscanf(token, "%x", &val_t_a);
						if (val_t_a==val_f_a) {DEBUG_MSG("bon"); return CMD_OK_RETURN_VALUE;}
						else {DEBUG_MSG("pas bon"); return CMD_UNKOWN_RETURN_VALUE;}
					}
					else {return CMD_UNKOWN_RETURN_VALUE;}
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
	else //assert "autre chose que reg ou word ou byte"  
	{
		WARNING_MSG("Usage: assert \"word\" | assert \"reg\" | assert \"byte\"");
		return CMD_UNKOWN_RETURN_VALUE;
	}
	DEBUG_MSG("ok");
	return CMD_OK_RETURN_VALUE;

}

