#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction MFLO


int fct_mflo(inst k, mem memory, registre* reg)
{
	 
	reg[k.r.rd].val=reg[LO].val;
	reg[PC].val+=4;
	return cmd_ok;
}

