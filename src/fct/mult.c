#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction MULT
// Attention definition de LO et HI

int fct_mult(inst k, mem memory, registre regs)
{
	long long q=regs[k.r.rs].val*regs[k.r.rt].val;
	regs[HI].val=q&Ox0000ffff;
	regs[LO].val=q&Oxffff0000;
	return cmd_ok;
}
