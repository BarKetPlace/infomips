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

int fct_sra(inst k, mem memory, registre* reg)
{
	 
	int signe = (reg[k.r.rt].val)&0x80000000;

	uint32_t shifted = (reg[k.r.rt].val)>>(k.r.sa);

	 
	reg[k.r.rd].val = signe + shifted;
	reg[PC].val+=4;
	return cmd_ok;
}

