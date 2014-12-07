
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SUB
// Definir max_inst

int fct_sub(inst k, mem memory, registre* reg, Liste dico)
{
	 
	long long temp=reg[k.r.rs].val-reg[k.r.rt].val;
	if (temp<=max_inst) {reg[k.r.rd].val=temp; reg[PC].val+=4;return cmd_ok;}
	else {return cmd_ok;}
}


