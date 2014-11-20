#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ANDI


int fct_andi(inst k, registre* regs)
{
	long long temp=regs[k.i.rs]+regs[k.i.imm];
	reg.i.rt=temp; 
	return cmd_ok;
}

