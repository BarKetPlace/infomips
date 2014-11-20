#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SUBU
// Definir max_inst

int fct_subu(inst k, registre regs)
{
	execute_next_inst(PC);
	long long temp=regs[k.r.rs]-regs[k.r.rt];
	regs[reg.r.rd]=temp; 
	return CMD_OK_RETURN_VALUE;
}

