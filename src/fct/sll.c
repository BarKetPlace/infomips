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


int fct_sll(inst k, mem memory, registre* reg, Liste dico)
{
	 
	reg[k.r.rd].val=((long)reg[k.r.rt].val)<<reg[k.i.imm].val; 
	return cmd_ok;
}

