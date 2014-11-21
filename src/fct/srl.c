#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SRL


int fct_srl(inst k, mem memory, registre* regs)
{
	 
	regs[k.i.rd].val=(regs[k.i.rt].val)>>regs[k.i.imm]; 
	return CMD_OK_RETURN_VALUE;
}

