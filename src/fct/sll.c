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
	 
	regs[reg.r.rd]=(regs[k.r.rt])<<regs[k.i.imm]; 
	return CMD_OK_RETURN_VALUE;
}

