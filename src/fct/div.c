#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction DIV
// Attention definition de LO et HI

int fct_div(inst k, registre regs)
{
	long long q=regs[k.r.rs]/regs[k.r.rt];
	regs[LO]=q;
	long long r=regs[k.r.rs]%regs[k.r.rt];
	regs[HI]=r;
	return cmd_ok;
}
