#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction LUI


int fct_lui(inst k, mem memory, registre* reg, Liste dico)
{
	 uint32_t value = (k.i.imm)<<16;
	
	//reg[k.i.rt].val = (value&0xffff0000) + (reg[k.i.rt].val)&0x0000ffff;
	reg[k.i.rt].val = value;

	return cmd_ok;
}

