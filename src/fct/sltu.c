#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLTU
// def condtion

int fct_sltu(inst k, mem memory, registre* regs)
{
	 
	if (regs[k.r.rs].val<regs[k.r.rt].val) {regs[k.r.rd].val=1;}
	else {regs[k.r.rd].val=0;}
	return cmd_ok;
}

