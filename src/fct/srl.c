#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SRL


int fct_srl(inst i, registre regs)
{
	execute_next_inst(PC);
	reg.r.rd=(regs[inst.i.rt])>>regs[inst.i.imm]; 
	return CMD_OK_RETURN_VALUE;
}

