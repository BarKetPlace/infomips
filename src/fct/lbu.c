
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction LBU


int fct_lbu(inst k, mem memory, registre* reg, Liste dico)
{
	reg[k.i.rt].val=(reg[k.i.imm].val)<<16;
	return cmd_ok;
	
}



