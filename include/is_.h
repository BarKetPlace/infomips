#ifndef is__
#define is__
#include <stdlib.h>
#include <stdio.h>
#include "syms.h"
#include "emulateur.h"


int is_in_symbols(char* name, stab symtab);
int is_elf(char* fichier, FILE* felf);
int is_conform_line(interpreteur inter);
int is_in_symbols(char* name, stab symtab);
int is_adresse(char *chaine);
int is_hexa(char* chaine);
int is_valeur(char* chaine);
int is_type(char *chaine);
int is_registre(char* chaine);


#endif
