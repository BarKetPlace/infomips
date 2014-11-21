#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SRA
// Demander comment copier le 1er bit


int fct_sra(inst k, registre* regs)
{
	 
	long long z = ((regs[k.i.rt].val)&0x80000000)>>31;
	long long t = (regs[k.i.rt].val)>>(regs[k.i.imm].val); 
	regs[k.i.rd].val = ((regs[k.i.imm].val)*z)
	return cmd_ok;
}

