#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLL


int fct_sll(inst k, registre* regs)
{
	 
	regs[reg.i.rd].val=(regs[k.i.rt].val)<<regs[k.i.imm].val; 
	return cmd_ok;
}

