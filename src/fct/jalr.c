#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction JALR


int fct_jalr(inst k, mem memory, registre *reg, Liste dico)
{
	reg[PC].val=reg[k.r.rs].val;
	//execute_next_fct(PC);
	
	//reg[]=
	return cmd_ok;
}
