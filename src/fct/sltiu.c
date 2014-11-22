#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SLTIU
// def condition

int fct_sltiu(inst k, registre* reg)
{
	if ((unsigned int)reg[k.r.rs].val<(unsigned int)reg[k.i.imm].val) {reg[k.r.rd].val=1;}
	else {reg[k.r.rd].val=0;}
	return cmd_ok;
}

