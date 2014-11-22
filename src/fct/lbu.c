
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction LBU


int fct_lbu(inst k, virtualmem vm)
{
	regs[k.i.rt].val=(regs[k.i.imm].val)<<16;
	return cmd_ok;
	
}



