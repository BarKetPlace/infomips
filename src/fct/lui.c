#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction LUI


int fct_lui(inst k, mem memory, registre* reg, Liste dico)
{
	 
	long long r=((long long)reg[k.i.imm].val)<<16;
	reg[k.i.rt].val=r&0xffff0000;
	return cmd_ok;
}

