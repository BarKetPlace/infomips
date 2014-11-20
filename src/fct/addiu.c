#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDIU
// Definir max_inst

int fct_addiu(inst k, registre* regs)
{
	long long temp=regs[k.i.rs]+regs[k.i.imm];
	reg.i.rt=temp; 
	return cmd_ok;
}

