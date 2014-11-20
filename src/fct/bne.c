#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction bne
// Similaire a BEQ


int fct_bne(inst k, registre regs)
{
	int off=((short)k.i.imm)<<2;
	int c=regs[k.i.rs]==regs[k.i.rt];
	if (!c)
		{
		PC=PC+off;
		return cmd_ok;
		}
	else {return cmd_ok;}
}

