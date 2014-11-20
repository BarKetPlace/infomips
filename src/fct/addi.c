#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDI
// Definir max_inst

int fct_addi(inst k, registre* regs)
{
	long long temp=regs[k.i.rs]+regs[k.i.imm];
	if (temp<=max_inst) {reg.i.rt=temp; return cmd_ok;}
	else {return cmd_ok;}
}


