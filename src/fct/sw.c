#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SW


int sw(inst i, registre regs)
{
	execute_next_inst(PC);
	mem[reg.i.rs+regs[inst.i.imm]]=regs[inst.i.rt];
	return CMD_OK_RETURN_VALUE;
}

