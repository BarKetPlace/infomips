#ifndef CMD_H
#define CMD_H

#include "mem.h"
#include "elf.h"
#include "emulateur.h"
#include "reg.h"
#include "dico.h"


#define PATH_TO_LIBC "./libc/libc.so"
#define LIBC_MEM_END 0xff7ff000u



//Définition des listes de nombres (breakpoint)
typedef struct _liste_int {
uint32_t val; 
struct _liste_int * suiv; }* Liste_int;

////////////////////////////////
int testcmd(interpreteur inter);
int exitcmd(interpreteur inter, mem memory, registre* reg, Liste dico, Liste_int l);

int loadcmd(interpreteur inter, mem memory, registre* reg);
int dispcmd(interpreteur inter, mem memory, registre* reg);

int disasm(mem memory, int adrr, int val, Liste dico);
int disasm_(mem memory, registre* reg, int debut, int fin, Liste dico);
int disasmcmd(interpreteur, mem memory, registre* reg, Liste dico);
void print_disasm(definition def, union inst_poly mot);

int assertcmd(interpreteur inter, mem memory, registre *reg);
int setcmd(interpreteur inter, mem memory, registre *reg);

int debugcmd(interpreteur inter, mem memory, registre *reg);
int resumecmd(interpreteur inter, mem memory, registre *reg);

int runcmd(interpreteur inter,mem memory, registre* reg, Liste dico, Liste_int breakliste);

int stepcmd(mem memory,registre* reg, Liste dico);
////////////////////////////
//break
//fonction sur les listes de nombres
Liste_int ajout_tete_int(uint32_t c, Liste_int l);
Liste_int supp_int(Liste_int l);
void visualiser_int(Liste_int l);
Liste_int supp_elt(uint32_t elt, Liste_int l);
void supp_Liste_int(Liste_int l);
int breakcmd(interpreteur inter,mem memory, Liste_int* pbreaklist);
int break_addcmd(interpreteur inter, mem memory , Liste_int* pbreaklist);
int break_delcmd(interpreteur inter, Liste_int* pbreaklist);
int break_listcmd(Liste_int breaklist);





#endif
