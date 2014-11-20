#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "is_.h"
#include "emulateur.h"

int is_conform_line(interpreteur inter)
{	DEBUG_MSG("ok");
	char *token = get_next_token(inter);
	switch (strcmp(token, "load"))
	{
		case 0:
			token = get_next_token(inter);
			
			if (token[strlen(token)-2] == '.' && token[strlen(token)-1] == 'o') 
				{DEBUG_MSG("ok"); return cmd_ok;}
			else {return cmd_unknown;}
		break;
	}DEBUG_MSG("ok");
	switch (strcmp(token, "set"))
	{
		case 0:
			token = get_next_token(inter);
			switch(strcmp(token, "mem"))
			{
				case 0:
					token = get_next_token(inter);
					if (is_type(token)==0) 
						{
						token = get_next_token(inter);
						if (is_adresse(token)==0) 
							{
							token = get_next_token(inter);
							if (is_valeur(token)==0) {return cmd_ok;}
							else {return 0;}
							}
						else {return 0;}
						}
					else {return 0;}
				break;
			}
			switch(strcmp(token, "reg"))
			{
				case 0:
					token = get_next_token(inter);
					if (is_registre(token)==0) 
						{
						token = get_next_token(inter);
						if (is_valeur(token)==0) {return cmd_ok;}
						else {return 0;}
						}
					else {return 0;}
				break;
			}
		break;
	}DEBUG_MSG("ok");
	
	switch (strcmp(token, "assert"))
	{
		case 0:
			token = get_next_token(inter);
			switch (strcmp(token, "reg"))
			{
				case 0:
					if (is_registre(token)==0) 
						{
						token = get_next_token(inter);
						if (is_valeur(token)==0) {return cmd_ok;}
						else {return 0;}
						}
					else {return 0;}
				break; 
			}
			switch (is_type(token))
			{
				case 1:
				
					if (is_adresse(token)==0) 
						{
						token = get_next_token(inter);
						if (is_valeur(token)==0) {return cmd_ok;}
						else {return 0;}
						}
					else {return 0;}
				break; 
			}
		break;
	}DEBUG_MSG("ok");
	switch (strcmp(token, "test"))
	{
		case 0: return cmd_ok;
		break;
	}DEBUG_MSG("ok");
	switch (strcmp(token, "disp"))
	{ 
		case 0:
			
			token = get_next_token(inter);
			DEBUG_MSG("ok");
			
			if (token && !strcmp(token, "mem"))				
			{
				token = get_next_token(inter);
				if (token && (is_plage(token)==0)) {return cmd_ok;}
				else if (token && (strcmp(token,"map")==0) ) {return cmd_ok;}
				else {return 0;}  
			}
			else if (token && strcmp(token,"reg"))
			{
				if (token && is_registre(token)==0) {return cmd_ok;}
				else {return 0;}
			}
			else {return 0;} 
			
			break;
	}
	switch (strcmp(token, "resume"))
	{
		case 0: return cmd_ok;
		break;
	}
	switch (strcmp(token, "debug"))
	{
		case 0: return cmd_ok;
		break;
	}
	switch (strcmp(token, "exit"))
	{
		case 0: return cmd_ok;
		break;
	}
	return 0;
			
}	

	

