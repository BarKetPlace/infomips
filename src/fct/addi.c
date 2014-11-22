#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction ADDI
// Definir max_inst

int fct_addi(inst k, mem memory, registre* reg, Liste dico)
{
	long long temp=reg[k.i.rs].val+reg[k.i.imm].val;
	if (temp<=max_inst) {reg[k.i.rt].val=temp; return cmd_ok;}
	else {return cmd_unknown;}
}


