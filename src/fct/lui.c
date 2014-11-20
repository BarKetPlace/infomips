#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction LUI


int fct_lui(inst i, registre regs)
{
	execute_next_inst(PC);
	reg.i.rt=(regs[inst.i.imm])<<16;
	return CMD_OK_RETURN_VALUE;
}

