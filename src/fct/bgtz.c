#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction BGTZ


int fct_bgtz(inst k, registre regs)
{
	int off=((short)k.i.imm)<<2;
	if (regs[k.i.rs]>0)
		{
		PC=PC+off;
		return cmd_ok;
		}
	else {return cmd_ok;}
}
