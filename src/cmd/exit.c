#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "emulateur.h"
#include "mem.h"
#include "reg.h"
#include "is_.h"
#include "dico.h"

/**
 * commande exit qui ne necessite pas d'analyse syntaxique
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en case de succes, un nombre positif sinon
 h */
int exitcmd(interpreteur inter, mem memory, registre* reg, Liste dico) {
	del_inter(inter);
	del_mem(memory);INFO_MSG("Liberation memoire");	
	del_reg(reg);INFO_MSG("Liberation des registres");
	del_dico(dico);INFO_MSG("Liberation du dictionnaire d'instructions");
	return cmd_exit;
}

