#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDI
// Definir max_inst

int addi(inst i, registre regs)
{
	execute_next_inst(PC);
	long long temp=regs[inst.i.rs]+regs[inst.i.imm];
	if (temp<=max_inst) {reg.i.rt=temp; return CMD_OK_RETURN_VALUE;}
	else {return CMD_UNKOWN_RETURN_VALUE;}
}


