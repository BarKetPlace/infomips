#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction beq


int fct_beq(inst k, mem memory, registre* regs)
{
	int off=((short)regs[k.i.imm].val)<<2;
	int c=regs[k.i.rs].val==regs[k.i.rt].val;
	if (c)
		{
		PC=PC+off;
		return cmd_ok;
		}
	else {return cmd_unknown;}
}

