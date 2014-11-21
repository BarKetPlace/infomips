#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLTIU
// def condition

int fct_sltiu(inst k, registre* regs)
{
	if ((unsigned int)regs[k.i.rs].val<(unsigned int)regs[k.i.imm].val) {regs[k.i.rd].val=1;}
	else {regs[k.i.rd].val=0;}
	return cmd_ok;
}

