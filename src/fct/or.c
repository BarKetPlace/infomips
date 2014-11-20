#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction OR
// Attention mettre les barres


int or(inst i, registre regs)
{
	execute_next_inst(PC);
	long long temp=regs[inst.r.rs]ORregs[inst.r.rt];
	regs[reg.r.rd]=temp; 
	return CMD_OK_RETURN_VALUE;
}

