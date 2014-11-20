#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLTU
// def condtion

int fct_sltu(inst i, registre regs)
{
	execute_next_inst(PC);
	if (regs[inst.r.rs]<regs[inst.r.rt]) {reg.r.rd=1;}
	else {reg.r.rd=0;}
	return CMD_OK_RETURN_VALUE;
}

