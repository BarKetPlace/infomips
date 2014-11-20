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
	 
	long long z = (regs[k.i.rt]&0x80000000)>>31;
	long long t = (regs[k.i.rt])>>regs[k.i.imm]; 
	reg.r.rd = (regs[k.i.imm]*z)
	return cmd_ok;
}

