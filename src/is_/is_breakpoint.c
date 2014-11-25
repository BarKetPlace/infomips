#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "emulateur.h"

//Renvoie cmd_ok si adresse est un breakpoint, cmd_unknown sinon
int is_breakpoint(uint32_t adresse, Liste_int breaklist){
	Liste_int l = breaklist;
	while (l){//DEBUG_MSG("");
		if (adresse == l->val) return cmd_ok;
		l = l->suiv;
	}

	return cmd_unknown;
}
