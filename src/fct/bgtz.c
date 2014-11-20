#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction BGTZ


int bgtz(inst i, registre regs)
{
	execute_next_inst(PC);
	int off=((short)inst.i.imm)<<2;
	if (regs[inst.i.rs]>0)
		{
		PC=PC+off;
		return CMD_OK_RETURN_VALUE;
		}
	else {return CMD_UNKOWN_RETURN_VALUE;}
}
