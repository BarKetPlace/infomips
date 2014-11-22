#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDI
// Definir max_inst

int fct_addi(inst k, virtualmem vm)
{
	long long temp=regs[k.i.rs].val+regs[k.i.imm].val;
	if (temp<=max_inst) {regs[k.i.rt].val=temp; return cmd_ok;}
	else {return cmd_unknown;}
}


