#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"


//Renvoie cmd_ok si adresse est un breakpoint, cmd_unknown sinon
int is_breakpoint(uint32_t adresse, Liste breakliste){
	Liste l;
	while (l){
		if (adresse == breakliste->val) return cmd_ok;
		l = l->suiv;
	}

	return cmd_unknown;
}
