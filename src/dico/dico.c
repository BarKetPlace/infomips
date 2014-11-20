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
{	if (!l) printf("Liste Vide	\n");
	while ( !est_vide(l) ) 
	{
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
{	int i;	
	printf("0x%08x\t0x%08x\t%s\t%c\t%d\t",def->sign, def->masq, def->nom, def->type, def->nb_op);
	for(i=0;i<def->nb_op;i++) printf("%s ",def->nom_op[i]);
	printf("\n");
}

void del_dico(Liste l)
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
	char* token, token2;
	int i;
	FILE* fp = fopen(fichier, "r");
	if (!fp) return cmd_unknown;

	fgets(chaine, MAXSTR, fp);
	
	while(fgets(chaine, MAXSTR, fp))
	{	//DEBUG_MSG("%s",chaine);
		if (chaine[0] != '\n' && chaine[0] != '\0' && chaine[0] != '\t' && chaine[0] != ' ')
		{
		definition def = calloc(1, sizeof(*def));//On alloue une nouvelle définition
		token = strtok(strdup( chaine ), " \t\n");
		sscanf(token, "%x", &def->sign);//Lecture & ecriture de la signature
		
		token = strtok(NULL, " \t\n") ;
		sscanf(token, "%x", &def->masq);//Lecture & ecriture du masque
	
		token = strtok(NULL, " \t\n") ;
		strcpy(def->nom, token); //Lecture & ecriture du nom
		
		token = strtok(NULL, " \t\n") ;
		sscanf(token, "%c", &def->type);//Lecture & ecriture du type

		token = strtok(NULL, " \t\n") ;
		//puts(token);
		sscanf(token, "%d", &def->nb_op);//Lecture & ecriture du nb d'opérande

		token = strtok(NULL, "\n\0") ;
		//puts(token);
		
		//strcpy(def->nom_op, token); 
		//puts(def->nom_op);

		//Lecture & ecriture de la syntaxe des opérandes
		// pour i < nb_op, token = strtok(token)
		// def->nom_op[i] = strdup(token);

		token = strtok(token, " \n");

		for(i=0;i<def->nb_op;i++)
		{	

			
			def->nom_op[i] = strdup(token);

			token = strtok(NULL, " \n");
		}
		if ( affectation_fct(def) != cmd_ok) ERROR_MSG("Problème d'affectation du nom de la fonction -> sortie du programme");

		
		l = ajout_tete(def, l);//On ajoute la définition au dictionnaire
		

		
		}
	}
	fclose(fp);
	return l;
}

int affectation_fct(definition def)
{
	//if (!strcmp(def->nom, "add") ) def->f = fct_add;
	//else if (!strcmp(def->nom, "addi") ) def->f = fct_addi;
	return cmd_ok;
}


//On va trouver l'instruction qui correspond au mot code stocke en memoire
//Cette fonction repose sur la comparaison entre le code masqué et la signature
definition find_def(Liste dico, union inst_poly mot)
{	definition res =NULL;
	Liste dico_1 = NULL;
	dico_1 = dico;
	//visualiser(dico);
	
	int masque;
	int signature;
	//DEBUG_MSG("%08x", mot.code);
	//if (!dico_1) DEBUG_MSG("");
	//visualiser(dico);
	while (dico)

	{	//DEBUG_MSG("");visualiser(dico);printf("\n");
		masque = dico->val->masq;//DEBUG_MSG("");
		signature = dico->val->sign;//DEBUG_MSG("");

		
		//DEBUG_MSG("0x%08x 0x%08x 0x%08x", signature, masque, mot.code&masque);

		if ( (mot.code&masque) == signature )  {	//DEBUG_MSG("");
			//detail_def(dico->val);
			res = dico->val;
			break;
		}

		dico=dico->suiv;
	}
	dico = dico_1;
	//visualiser(dico);
	//if(res) detail_def(res);
	return res;
}




/*
int main(int argc, char* argv[])
{	

	Liste dico = NULL;
	if (!(dico =  read_dico("./src/dico/dico.txt") ) ) return 1;

	char* token;
	char* delim = " ";
	union inst_poly mot;
	int i;
	mot.code = 0x00641020;
	//On va trouver l'instruction qui correspond au mot code stocke en memoire
	definition def = find_def(dico, mot);
	if (!def) return 1;
	//detail_def(def);

	DEBUG_MSG("0x%08x", mot.code);
	//print_disasm(def, mot);


	//DEBUG_MSG("swap(0x%08x) = 0x%08x", mot.code,swap_mot(mot.code));
	
	visualiser(dico);
	del_defs(dico);
	return 0;

}*/




