#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ORI
// Attention mettre les barres


int ori(inst i, registre regs)
{
	execute_next_inst(PC);
	long long temp=regs[inst.i.rs]ORregs[inst.i.imm];
	regs[reg.i.rt]=temp; 
	return CMD_OK_RETURN_VALUE;
}
