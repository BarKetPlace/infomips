#ifndef CMD_H
#define CMD_H

#include "mem.h"
#include "elf.h"
#include "emulateur.h"
#include "reg.h"
#include "dico.h"


////////////////////////////////
int testcmd(interpreteur inter);
int exitcmd(interpreteur inter, mem memory, registre* reg);


int loadcmd(char* fichier, mem memory, registre* reg);
int dispcmd(interpreteur inter, mem memory, registre* reg);

int disasm(mem memory, int adrr, int val, Liste dico);
int disasm_(mem memory, registre* reg, int debut, int fin, Liste dico);
int disasmcmd(interpreteur, mem memory, registre* reg, Liste dico);

int assertcmd(interpreteur inter, mem memory, registre *reg);
int setcmd(interpreteur inter, mem memory, registre *reg);


#endif
