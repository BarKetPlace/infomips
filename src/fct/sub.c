
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SUB
// Definir max_inst

int fct_sub(inst k, mem memory, registre* reg)
{
	DEBUG_MSG("%x",reg[k.r.rs].val);
	DEBUG_MSG("%x",reg[k.r.rt].val);
	signed long long temp = reg[k.r.rs].val-reg[k.r.rt].val;
	DEBUG_MSG("");
	if (temp>0xffffffff) { reg[PC].val+=4;return cmd_ok;}
	else {
	reg[PC].val+=4;	
	reg[k.r.rd].val=temp;	
	return cmd_ok;
	}
}


