#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDIU
// Definir max_inst

int fct_addiu(inst k, mem memory, registre* regs)
{
	long long temp=regs[k.i.rs].val+regs[k.i.imm].val;
	regs[k.i.rt]=temp; 
	return cmd_ok;
}

