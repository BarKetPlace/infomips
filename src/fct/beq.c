#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"

// Fonction beq


int fct_beq(inst k, mem memory, registre* reg)
{
	int off=(k.i.imm)<<2;
	int c=reg[k.i.rs].val==reg[k.i.rt].val;
	if (c)
		{
		reg[PC].val+=4;
		reg[PC].val=reg[PC].val+off;
		return cmd_ok;
		}
	else {reg[PC].val+=4; return cmd_ok;}
}

