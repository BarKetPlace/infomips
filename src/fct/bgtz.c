#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction BGTZ


int fct_bgtz(inst k, virtualmem vm)
{
	int off=((short)regs[k.i.imm].val)<<2;
	if (regs[k.i.rs].val>0)
		{
		PC=PC+off;
		return cmd_ok;
		}
	else {return cmd_unknown;}
}
