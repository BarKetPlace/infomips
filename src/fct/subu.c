#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction SUBU
// Definir max_inst

int fct_subu(inst k, virtualmem vm)
{
	 
	long long temp=regs[k.r.rs].val-regs[k.r.rt].val;
	regs[k.r.rd].val=temp; 
	return cmd_ok;
}

