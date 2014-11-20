#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDU
// Definir max_inst

int fct_addu(inst k, registre regs)
{
	long long temp=regs[k.r.rs]+regs[k.r.rt];
	regs[reg.r.rd]=temp; 
	return cmd_ok;
}

