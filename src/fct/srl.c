#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SRL


int fct_srl(inst k, registre* regs)
{
	 
	reg.r.rd=(regs[k.i.rt])>>regs[k.i.imm]; 
	return CMD_OK_RETURN_VALUE;
}

