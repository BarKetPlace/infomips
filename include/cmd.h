#ifndef CMD_H
#define CMD_H

#include "mem.h"
#include "elf.h"
#include "emulateur.h"
#include "reg.h"
int testcmd(interpreteur inter);
int exitcmd(interpreteur inter);


int loadcmd(char* fichier, mem memory, registre* reg);
int dispcmd(interpreteur inter, mem memory, registre* reg);


#endif
