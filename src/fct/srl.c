#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SRL


int fct_srl(inst k, mem memory, registre* reg, Liste dico)
{
	 
	reg[k.r.rd].val= (reg[k.r.rt].val)>>( (k.code&0x000007c0)>>6); 
	return cmd_ok;
}

