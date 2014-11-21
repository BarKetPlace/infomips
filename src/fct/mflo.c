#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction MFLO


int fct_mflo(inst k, registre* regs)
{
	 
	regs[LO].val=regs[k.i.rs].val;
	return cmd_ok;
}

