#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction LUI


int fct_lui(inst k, registre* regs)
{
	 
	long long r=(regs[k.i.imm])<<16;
	reg.i.rt=r&0xffff0000;
	return CMD_OK_RETURN_VALUE;
}

