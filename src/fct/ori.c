#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ORI
// Attention mettre les barres


int fct_ori(inst k, registre* regs)
{
	 
	long long temp=regs[k.i.rs]ORregs[k.i.imm];
	reg.i.rt=temp; 
	return CMD_OK_RETURN_VALUE;
}
