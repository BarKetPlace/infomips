#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction OR
// Attention mettre les barres


int fct_or(inst k, registre* regs)
{
	 
	long long temp=(regs[k.r.rs].val)¦(Rregs[k.r.rt]);
	regs[k.r.rs].val=temp; 
	return cmd_ok;
}

