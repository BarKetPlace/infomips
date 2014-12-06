#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction ORI
// Attention mettre les barres


int fct_ori(inst k, mem memory, registre* reg, Liste dico)
{
	 
	long long temp=(reg[k.i.rs].val)|(k.i.imm);
	reg[k.i.rt].val=temp;
	reg[PC].val+=4;
	return cmd_ok;
}
