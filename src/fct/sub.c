
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SUB
// Definir max_inst

int fct_sub(inst k, registre* regs)
{
	 
	long long temp=regs[k.r.rs].val-regs[k.r.rt].val;
	if (temp<=max_inst) {k.r.rd=temp; return cmd_ok;}
	else {return cmd_ok;}
}


