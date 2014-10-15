#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "dico.h"

#include "notify.h"


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


int main(int argc, char* argv[])
{	
	Liste l = creer_liste();
	char chaine[MAXSTR];
	char* token;
	FILE* fp = fopen(argv[1], "r");
	if (!fp) return 1;
	int i=0;
	fgets(chaine, MAXSTR, fp);
	
	while(fgets(chaine, MAXSTR, fp))
	{	if (chaine[0] != '\n')
		{
		definition def = calloc(1, sizeof(*def));
		//puts(chaine);
		token = strtok(strdup( chaine ), " \t\n");
		//puts(token);
		sscanf(token, "%x", &def->sign);
		
		token = strtok(NULL, " \t\n") ;
		//puts(token);
		sscanf(token, "%x", &def->masq);
	
		token = strtok(NULL, " \t\n") ;
		//puts(token);
		strcpy(def->nom, token);
		
		
		token = strtok(NULL, " \t\n") ;
		//puts(token);
		sscanf(token, "%c", &def->type);
		

		token = strtok(NULL, " \t\n") ;
		//puts(token);
		sscanf(token, "%d", &def->nb_op);

		token = strtok(NULL, "\n\0") ;
		
		strcpy(def->nom_op, token);
		//puts(def->nom_op);
		
		l = ajout_tete(def, l);
		//DEBUG_MSG("");
		
		}
	}
	visualiser(l);
	return 0;
}




