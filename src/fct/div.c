#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction DIV


int fct_div(inst k, mem memory, registre* regs)
{
	long long q=regs[k.r.rs].val/regs[k.r.rt].val;
	regs[LO].val=q;
	long long r=(regs[k.r.rs].val)%(regs[k.r.rt].val);
	regs[HI].val=r;
	return cmd_ok;
}
