#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SLTI


int fct_slti(inst k, mem memory, registre* reg)
{
	 
	if ((signed int)reg[k.i.rs].val<(signed int)k.i.imm) {reg[k.i.rt].val=1;}
	else {reg[k.i.rt].val=0;}
	reg[PC].val+=4;
	return cmd_ok;
}

