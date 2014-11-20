#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction LW


int lw(inst i, registre regs)
{
	execute_next_inst(PC);
	reg.i.rt=mem[regs[inst.i.rs]+regs[inst.i.imm]];
	return CMD_OK_RETURN_VALUE;
}

