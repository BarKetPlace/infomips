#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction MFHI


int fct_mfhi(inst k, registre* regs)
{
	 
	regs[HI].val=regs[k.i.rs].val;
	return cmd_ok;
}

