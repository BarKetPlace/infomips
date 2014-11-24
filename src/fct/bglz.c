#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction BGLZ


int fct_bglz(inst k, mem memory, registre* reg, Liste dico)
{
	int off=((short)k.i.imm)<<2;
	if (reg[k.i.rs].val<=0)
		{
		reg[PC].val=reg[PC].val+off;
		return cmd_ok;
		}
	else {return cmd_unknown;}
}
