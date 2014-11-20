#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction MFLO


int fct_mflo(inst k, registre regs)
{
	execute_next_inst(PC);
	regs[LO]=regs[k.i.rs];
	return CMD_OK_RETURN_VALUE;
}

