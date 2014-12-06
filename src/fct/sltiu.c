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
	if ((unsigned int)reg[k.i.rs].val<(unsigned int)reg[k.i.imm].val) {reg[k.i.rt].val=1;}
	else {reg[k.i.rt].val=0;}
	reg[PC].val+=4;
	return cmd_ok;
}

