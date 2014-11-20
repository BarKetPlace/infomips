#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDU
// Definir max_inst

int addu(inst i, registre regs)
{
	execute_next_inst(PC);
	long long temp=regs[inst.r.rs]+regs[inst.r.rt];
	regs[reg.r.rd]=temp; 
	return CMD_OK_RETURN_VALUE;
}
