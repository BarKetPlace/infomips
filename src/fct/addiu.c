#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction ADDIU
// Definir max_inst

int fct_addiu(inst k, mem memory, registre* reg)
{
	long long temp=reg[k.i.rs].val+k.i.imm;
	reg[k.i.rt].val=temp;
	reg[PC].val+=4;
	return cmd_ok;
}

