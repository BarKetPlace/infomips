#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction AND


int fct_and(inst k, registre regs)
{
	long long temp=regs[k.r.rs]&regs[k.r.rt];
	reg.r.rd=temp; 
	return cmd_ok;
}

