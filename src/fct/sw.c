#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SW


int fct_sw(inst k, registre* regs)
{
	mem[k.i.rs+regs[k.i.imm].val]=regs[k.i.rt];
	return cmd_ok;
}

