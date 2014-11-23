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


int fct_slti(inst k, mem memory, registre* reg, Liste dico)
{
	 
	if ((signed int)reg[k.r.rs].val<(signed int)reg[k.i.imm].val) {reg[k.r.rd].val=1;}
	else {reg[k.r.rd].val=0;}
	return cmd_ok;
}

