#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "dico.h"

#include "notify.h"
#include "emulateur.h"

//Fonctions de base sur les listes
Liste creer_liste(void){return NULL;}

int est_vide(Liste l){ return (!l);}

void visualiser(Liste l)
{	while ( !est_vide(l) ) 
	{	//DEBUG_MSG("");
		detail_def(l->val);
		l=l->suiv;
	}

}

Liste ajout_tete(definition c, Liste l)
{	Liste p =(Liste) calloc(1, sizeof(*p));
	p->val=c;	
	p->suiv=l;
	return p;
}

Liste supp(Liste l)
{	if (est_vide(l)) return NULL;
	else
	{	Liste p;
		p=l->suiv;
		free(l);
		return p;
	}
}

Liste ajout_queue(definition c, Liste l)
{	if (l->suiv==NULL)
	{	Liste p=creer_liste();
		p->val=c;
		p->suiv=NULL;
		l->suiv=p;
		return l;
	}
	else ajout_queue(c,l->suiv);
}

Liste supprimen(int n, Liste l)
{	if (n==0) return (supp(l));
	else
	{
	int i;
	Liste q = l;
	for (i=1;i<n-1;i++) 
	{	l=l->suiv;
		q->suiv=l;
		q=q->suiv;
	}
	Liste p = l->suiv;
	l->suiv=(l->suiv)->suiv;
	free(p);
	return q;
	}
}

Liste concat(Liste l1, Liste l2)
{	Liste p = l1;
	while (l1->suiv != NULL) l1=l1->suiv;
	l1->suiv=l2;
	return p;	
}

Liste copie(Liste l)
{	Liste p=l;
	Liste q=p;
	while ( !est_vide(l) )
	{	p->val=l->val;
		p->suiv=l->suiv;
		l=l->suiv;
		p=p->suiv;
	}
	return q;
}

void detail_def(definition def)
{	printf("0x%08x\t0x%08x\t%s\t%c\t%d\t%s\n",def->sign, def->masq, def->nom, def->type, def->nb_op, def->nom_op);
}

void del_defs(Liste l)
{
	while (l)
	{	
		l=supp(l);
	}
}


Liste read_dico(char* fichier)
{
	Liste l = creer_liste();
	char chaine[MAXSTR];
	char* token;
	FILE* fp = fopen(fichier, "r");
	if (!fp) return CMD_UNKOWN_RETURN_VALUE;

	fgets(chaine, MAXSTR, fp);
	
	while(fgets(chaine, MAXSTR, fp))
	{	if (chaine[0] != '\n')
		{
		definition def = calloc(1, sizeof(*def));//On alloue une nouvelle définition
		//puts(chaine);
		token = strtok(strdup( chaine ), " \t\n");
		//puts(token);
		sscanf(token, "%x", &def->sign);//Lecture & ecriture de la signature
		
		token = strtok(NULL, " \t\n") ;
		//puts(token);
		sscanf(token, "%x", &def->masq);//Lecture & ecriture du masque
	
		token = strtok(NULL, " \t\n") ;
		//puts(token);
		strcpy(def->nom, token); //Lecture & ecriture du nom
		
		token = strtok(NULL, " \t\n") ;
		//puts(token);
		sscanf(token, "%c", &def->type);//Lecture & ecriture du type

		token = strtok(NULL, " \t\n") ;
		//puts(token);
		sscanf(token, "%d", &def->nb_op);//Lecture & ecriture du nb d'opérande

		token = strtok(NULL, "\n\0") ;
		
		strcpy(def->nom_op, token); //Lecture & ecriture de la syntaxe des opérande
		//puts(def->nom_op);
		
		l = ajout_tete(def, l);//On ajoute la définition au dictionnaire
		
		//DEBUG_MSG("");
		
		}
	}
	fclose(fp);
	return l;
}

definition find_def(Liste dico, instruc mot)
{
	int masque;
	int signature;
	
	while(dico)
	{	
		masque = dico->val->masq;
		signature = dico->val->sign;
		
		//DEBUG_MSG("0x%08x 0x%08x 0x%08x", signature, masque, mot.code&masque);

		if ( (mot.code&masque) == signature ) return dico->val;
		dico=dico->suiv;
	}
	return NULL;
}


int swap_mot(int mot)
{	int res=0;
	res = ((mot&0xff000000)>>24) + ((mot&0x00ff0000)>>8) + ((mot&0x0000ff00)<<8) + ((mot&0x000000ff)<<24);
	return res;
}



int main(int argc, char* argv[])
{	

DEBUG_MSG("");
	Liste dico = NULL;
	if (!(dico =  read_dico(argv[1]) ) ) return 1;
	/*int masque;
	int signature;

	union inst_poly mot;
	
	
	if(mot.r.op == 0) DEBUG_MSG(" Type R ");

	while(dico)
	{	
		masque = dico->val->masq;
		signature = dico->val->sign;
		
		//DEBUG_MSG("0x%08x 0x%08x 0x%08x", signature, masque, mot.code&masque);

		if ( (mot.code&masque) == signature ) DEBUG_MSG("ADD");
		
		dico=dico->suiv;
	}*/
	instruc mot;
	mot.code = 0x00641020;
	definition def = find_def(dico, mot);
	if (!def) return 1;
	detail_def(def);

	DEBUG_MSG("0x%08x", mot.code);
	if (def->type == 'R')
	{	
		DEBUG_MSG("0x%08x", mot.code);
		DEBUG_MSG(" 0x%08x 0x%08x 0x%08x ",mot.r.rd, mot.r.rt, mot.r.rs);
	}


	DEBUG_MSG("swap(0x%08x) = 0x%08x", mot.code,swap_mot(mot.code));
	
	//visualiser(dico);
	del_defs(dico);
	return 0;
}




