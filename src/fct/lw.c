#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction LW
// Mettre erreur adresse ...

int fct_lw(inst k, registre* regs)
{
	int tmp;
	int l=regs[k.i.rs]+regs[k.i.imm];
	tmp = find_val(memory, l, &regs[k.i.rt].val);

	if (l<START_MEM) ERROR_MSG("La memoire commence en 0x%08x",START_MEM);
	if (l>STOP_MEM) ERROR_MSG("La memoire termine en 0x%08x",STOP_MEM);

	if (tmp==cmd_unknown)
	{	printf("\n");
		ERROR_MSG("L'adresse 0x%08x n'est pas allouee", l);
		return cmd_unknown;
	}
	else {
		return cmd_ok;
	}
}

