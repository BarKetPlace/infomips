#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ANDI


int fct_andi(inst k, registre* regs)
{
	long long temp=regs[k.i.rs].val+regs[k.i.imm].val;
	regs[k.i.rt].val=temp; 
	return cmd_ok;
}

