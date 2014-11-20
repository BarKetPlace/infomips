#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction bne
// Similaire a BEQ


int bne(inst i, registre regs)
{
	execute_next_inst(PC);
	int off=((short)inst.i.imm)<<2;
	int c=regs[inst.i.rs]==regs[inst.i.rt];
	if (!c)
		{
		PC=PC+off;
		return CMD_OK_RETURN_VALUE;
		}
	else {return CMD_UNKOWN_RETURN_VALUE;}
}

