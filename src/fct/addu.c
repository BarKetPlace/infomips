#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDU
// Definir max_inst

int fct_addu(inst k, virtualmem vm)
{
	long long temp=regs[k.r.rs].val+regs[k.r.rt].val;
	regs[reg.r.rd].val=temp; 
	return cmd_ok;
}

