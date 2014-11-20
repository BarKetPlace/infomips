#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction LW
// Mettre erreur adresse ...

int fct_lw(inst k, registre* regs)
{
	 
	reg.i.rt=mem[regs[k.i.rs]+regs[k.i.imm]];
	return CMD_OK_RETURN_VALUE;
}

