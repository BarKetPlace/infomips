#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"

int fct_seb(inst k, mem memory, registre *reg, Liste dico){
	reg[k.r.rd].val = (signed) reg[k.r.rt].val;	
	
	return cmd_ok;
}
