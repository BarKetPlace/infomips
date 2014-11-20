#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLTI


int fct_slti(inst k, registre regs)
{
	execute_next_inst(PC);
	if (regs[k.i.rs]<regs[k.i.imm]) {reg.r.rd=1;}
	else {reg.r.rd=0;}
	return CMD_OK_RETURN_VALUE;
}

