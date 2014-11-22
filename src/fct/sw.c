#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SW


int fct_sw(inst k, mem memory, registre* reg, Liste dico)
{
	uint32_t vale=reg[k.i.rt].val;
	int tmp;
	uint32_t m;
	signed int l=reg[k.i.rs].val+(signed long)reg[k.i.imm].val;
	tmp = find_val(memory, l, &m);

	if (l<START_MEM) ERROR_MSG("La memoire commence en 0x%08x",START_MEM);
	if (l>STOP_MEM) ERROR_MSG("La memoire termine en 0x%08x",STOP_MEM);

	if (tmp==cmd_unknown)
	{	printf("\n");
		ERROR_MSG("L'adresse 0x%08x n'est pas allouee", l);
		return cmd_unknown;
	}
	else {
		m=reg[k.i.rt].val;
		return cmd_ok;
	}
	return cmd_ok;
}

