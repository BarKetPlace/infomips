#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDIU
// Definir max_inst

int fct_addiu(inst i, registre regs)
{
	execute_next_inst(PC);
	long long temp=regs[inst.i.rs]+regs[inst.i.imm];
	reg.i.rt=temp; 
	return CMD_OK_RETURN_VALUE;
}

