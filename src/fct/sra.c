#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SRA
// Demander comment copier le 1er bit


int fct_sra(inst k, mem memory, registre* reg, Liste dico)
{
	 
	long long z = ((reg[k.r.rt].val)&0x80000000)>>31;
	long long t = (reg[k.r.rt].val)>>(reg[k.i.imm].val); 
	reg[k.r.rd].val = ((reg[k.i.imm].val)*z);
	return cmd_ok;
}

