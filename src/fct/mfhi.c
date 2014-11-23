#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction MFHI


int fct_mfhi(inst k, mem memory, registre* reg, Liste dico)
{
	 
	reg[HI].val=reg[k.i.rs].val;
	return cmd_ok;
}

