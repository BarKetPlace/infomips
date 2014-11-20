#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SLTU
// def condtion

int fct_sltu(inst k, registre* regs)
{
	 
	if (regs[k.r.rs]<regs[k.r.rt]) {reg.r.rd=1;}
	else {reg.r.rd=0;}
	return cmd_ok;
}

