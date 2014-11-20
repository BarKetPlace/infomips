
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SUB
// Definir max_inst

int fct_sub(inst k, registre regs)
{
	execute_next_inst(PC);
	long long temp=regs[k.r.rs]-regs[k.r.rt];
	if (temp<=max_inst) {reg.r.rd=temp; return CMD_OK_RETURN_VALUE;}
	else {return CMD_UNKOWN_RETURN_VALUE;}
}


