#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction ANDI


int fct_andi(inst k, mem memory, registre* reg)
{
	long long temp=(reg[k.i.rs].val)&((long) k.i.imm);
	reg[k.i.rt].val=temp;
	reg[PC].val+=4;
	return cmd_ok;
}

