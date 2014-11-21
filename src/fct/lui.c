#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction LUI


int fct_lui(inst k, registre* regs)
{
	 
	long long r=(regs[k.i.imm].val)<<16;
	regs[k.i.rt].val=r&0xffff0000;
	return cmd_ok;
}

