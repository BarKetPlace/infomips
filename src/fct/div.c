#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction DIV
// Attention definition de LO et HI

int div(inst i, registre regs)
{
	execute_next_inst(PC);
	long long q=regs[inst.r.rs]/regs[inst.r.rt];
	regs[LO]=q;
	long long r=regs[inst.r.rs]%regs[inst.r.rt];
	regs[HI]=r;
	reuturn OK_CMD_RETURN_VALUE;
}
