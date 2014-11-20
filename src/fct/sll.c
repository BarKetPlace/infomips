#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLL


int fct_sll(inst i, registre regs)
{
	execute_next_inst(PC);
	regs[reg.r.rd]=(regs[inst.r.rt])<<regs[inst.i.imm]; 
	return CMD_OK_RETURN_VALUE;
}

