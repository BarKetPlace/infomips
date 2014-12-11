#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction XOR



int fct_xor(inst k, mem memory, registre* reg)
{
	 
	long long temp=(reg[k.r.rs].val)^(reg[k.r.rt].val);
	reg[k.r.rd].val=temp;
	reg[PC].val+=4;
	return cmd_ok;
}

