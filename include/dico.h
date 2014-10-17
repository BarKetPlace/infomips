#ifndef DICO_
#define DICO_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAXSTR 256
/* TYPES POUR DISASM */

//Selon son type, un bit d'un code ne signifie pas la même chose
struct R {unsigned int func:6, si:5, rd:5, rt:5, rs:5, op:6;};
struct I {unsigned int imm:16, rt:5, rs:5, func:6;};
struct J {unsigned int target:26, func:6;};

//Un code 32 bits peut être vu soit comme un simple usigned int, soit comme un code de type R, J ou I
union inst_poly {
	unsigned int code;
	struct R r;
	struct I i;
	struct J j;
};
typedef union inst_poly instruc;

//représente une instruction type, sortie du dictionnaire
typedef struct {
	uint32_t sign;
	uint32_t masq;
	char nom[6];
	char type;
	int nb_op;
	char nom_op[MAXSTR];
}* definition;


//Définition des listes
typedef struct _liste {
definition val; 
struct _liste * suiv; }* Liste;


Liste creer_liste(void);
int est_vide(Liste l);
void visualiser(Liste l);
Liste ajout_tete(definition c, Liste l);
Liste supp(Liste l);
Liste ajout_queue(definition c, Liste l);
Liste supprimen(int n, Liste l);
Liste concat(Liste l1, Liste l2);
Liste copie(Liste l);



int lecture_dico(char* fichier, Liste l);
void detail_def(definition def);
void del_defs(Liste l);
Liste read_dico(char* fichier);



#endif
