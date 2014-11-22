#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction JR


int fct_jr(inst k, mem memory, registre *reg, Liste dico)
{
	reg[PC].val=reg[k.r.rs].val;
	return cmd_ok;
}
