#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction MULT
// Attention definition de LO et HI

int fct_mult(inst k, mem memory, registre* reg)
{
	long long q=reg[k.r.rs].val*reg[k.r.rt].val;
	reg[HI].val=q&0x0000ffff;
	reg[LO].val=q&0xffff0000;
	reg[PC].val+=4;
	return cmd_ok;
}
