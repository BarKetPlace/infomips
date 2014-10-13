#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "emulateur.h"
#include "mem.h"
#include "reg.h"
#include "is_.h"


/**
 * commande exit qui ne necessite pas d'analyse syntaxique
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en case de succes, un nombre positif sinon
 */
int exitcmd(interpreteur inter) {
    INFO_MSG("Bye bye !");
    return CMD_EXIT_RETURN_VALUE;
}

