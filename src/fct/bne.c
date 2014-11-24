#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction bne
// Similaire a BEQ


int fct_bne(inst k, mem memory, registre* reg, Liste dico)
{
	int off=((short)k.i.imm)<<2;
	int c=reg[k.i.rs].val==reg[k.i.rt].val;
	if (!c)
		{
		reg[PC].val=reg[PC].val+off;
		return cmd_ok;
		}
	else {return cmd_unknown;}
}

