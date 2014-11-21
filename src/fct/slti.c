#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLTI


int fct_slti(inst k, mem memory, registre* regs)
{
	 
	if (regs[k.i.rs].val<regs[k.i.imm].val) {regs[k.i.rd].val=1;}
	else {regs[k.i.rd].val=0;}
	return cmd_ok;
}

