#ifndef CMD_H
#define CMD_H

#include "mem.h"
#include "elf.h"
#include "emulateur.h"
#include "reg.h"

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

//représente une instruction type sortie du dictionnaire
typedef struct {
	uint32_t signature;
	uint32_t masque;
	char* nom;
	char type;
	int nb_op;
	char* nom_op;
} definition;


////////////////////////////////
int testcmd(interpreteur inter);
int exitcmd(interpreteur inter);


int loadcmd(char* fichier, mem memory, registre* reg);
int dispcmd(interpreteur inter, mem memory, registre* reg);

int disasm(mem memory, int val, char* res);
int disasm_(interpreteur inter, mem memory, registre* reg, int debut, int fin);
int disasmcmd(interpreteur inter, mem memory, registre* reg);



#endif
