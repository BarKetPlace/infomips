#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SLTU
// def condtion

int fct_sltu(inst k, mem memory, registre* reg, Liste dico)
{
	 
	if ((unsigned int)reg[k.r.rs].val<(unsigned int)reg[k.r.rt].val) {reg[k.r.rd].val=1;}
	else {reg[k.r.rd].val=0;}
	reg[PC].val+=4;
	return cmd_ok;
}

