#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction DIV


int fct_div(inst k, mem memory, registre* reg)
{
	long long q=reg[k.r.rs].val/reg[k.r.rt].val;
	reg[LO].val=q;
	long long r=(reg[k.r.rs].val)%(reg[k.r.rt].val);
	reg[HI].val=r;
	reg[PC].val+=4;
	return cmd_ok;
}
