#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "dico.h"
#include "is_.h"

int breakcmd(interpreteur inter,mem memory, Liste_int* pbreaklist)
{
	char* token;
	token = get_next_token(inter);
	if (token && !strcmp(token, "add")){
		return break_addcmd(inter,memory, pbreaklist);
	}
	else if (token && !strcmp(token, "del")){
		return break_delcmd(inter, pbreaklist);
	}
	else if (token && !strcmp(token, "list")){
		if (*pbreaklist) printf("%d\n",(*pbreaklist)->val);
		else DEBUG_MSG("null");
		return break_listcmd(*pbreaklist);
	}
	else {
		WARNING_MSG("Syntax error break (add ou del) + HEXAs | list");
		return cmd_unknown;
	}

}

int break_delcmd(interpreteur inter, Liste_int* pbreaklist){
	return cmd_ok;
}

int break_listcmd(Liste_int breaklist){
	printf("%d\n",breaklist->val);
	//visualiser_int(breaklist);
	return cmd_ok;
}
int break_addcmd(interpreteur inter, mem memory , Liste_int* pbreaklist)
{ 
	char* token;
	uint32_t adresse;
	uint32_t text_start, text_taille;
	token = get_next_token(inter); 
	if (!token)	{
		WARNING_MSG("Missing argument HEXA");
		return cmd_unknown;
	}
	while (token){
		if (is_hexa(token)){
			sscanf(token,"%x", &adresse);
			DEBUG_MSG("%x",adresse);
			if (is_text_adresse(memory,adresse,&text_start,&text_taille) == cmd_ok){
				DEBUG_MSG("");
				*pbreaklist = ajout_tete_int(adresse, *pbreaklist); DEBUG_MSG("");
			}
			else{
				WARNING_MSG("0x%08x n'est pas dans la zone texte (%x->%x)", adresse,text_start,text_start + text_taille-1);
				return cmd_unknown;
			}
		}
		else {
			WARNING_MSG("%s doit etre un hexa",token);
			return cmd_unknown;
		}
		
		token = get_next_token(inter);	
	}
	//DEBUG_MSG("");
	DEBUG_MSG("%x",(*pbreaklist)->val);
	return cmd_ok;
}

//fonction agissant sur des listes de nombre
Liste_int ajout_tete_int(uint32_t c, Liste_int l)
{	DEBUG_MSG("");
	Liste_int p =(Liste_int) calloc(1, sizeof(*p)); DEBUG_MSG("");
	p->val=c;	
	p->suiv=l; DEBUG_MSG("%x",c);
	return p;
}

Liste_int supp_int(Liste_int l)
{	if (est_vide(l)) return NULL;
	else
	{	Liste p;
		p=l->suiv;
		free(l);
		return p;
	}
}

void visualiser_int(Liste_int l)
{	if (!l) printf("Liste Vide\n");
	else{
		while ( l ) 
		{
			printf("\t0x%08x\n", l->val);
			l=l->suiv;
		}
	}
}



