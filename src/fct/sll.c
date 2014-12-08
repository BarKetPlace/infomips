#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SLL


int fct_sll(inst k, mem memory, registre* reg)
{
	 
	reg[k.r.rd].val=((long)reg[k.r.rt].val)<<k.i.imm; 
	reg[PC].val+=4;
	return cmd_ok;
}

