#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLL


int fct_sll(inst k, virtualmem vm)
{
	 
	regs[reg.i.rd].val=((long)regs[k.i.rt].val)<<regs[k.i.imm].val; 
	return cmd_ok;
}

