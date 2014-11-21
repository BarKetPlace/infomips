#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction JR


int fct_jr(inst k, mem memory, registre *regs)
{
	regs[PC].val=regs[k.r.rs].val;
	return cmd_ok;
}
