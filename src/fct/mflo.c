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


int fct_mflo(inst k, mem memory, registre* reg, Liste dico)
{
	 
	reg[LO].val=reg[k.i.rs].val;
	return cmd_ok;
}

