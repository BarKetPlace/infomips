#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLT


int fct_slt(inst k, mem memory, registre* regs)
{
	 
	if ((signed int)regs[k.r.rs].val<(signed int)regs[k.r.rt].val) 
		{regs[k.i.rd].val=1;}
	else {regs[k.i.rd].val=0;}
	return cmd_ok;
}

