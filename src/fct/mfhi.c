#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction MFHI


int mfhi(inst i, registre regs)
{
	execute_next_inst(PC);
	reg.i.rd=regs[HI];
	return CMD_OK_RETURN_VALUE;
}

