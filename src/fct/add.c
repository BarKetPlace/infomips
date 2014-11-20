
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction add
// Definir max_inst

int fct_add(inst k, registre regs)
{
	execute_next_inst(PC);
	long long temp=regs[k.r.rs]+regs[k.r.rt];
	if (temp<=max_inst) {regs[reg.r.rd]=temp; return cmd_ok;}
	else {return cmd_ok;}
}



