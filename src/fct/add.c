
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction add
// Definir max_inst

int add(inst i, registre regs)
{
	execute_next_inst(PC);
	long long temp=regs[inst.r.rs]+regs[inst.r.rt];
	if (temp<=max_inst) {regs[reg.r.rd]=temp; return CMD_OK_RETURN_VALUE;}
	else {return CMD_UNKOWN_RETURN_VALUE;}
}



