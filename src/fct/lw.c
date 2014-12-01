#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction LW


int fct_lw(inst k, mem memory, registre* reg, Liste dico)
{
		int tmp;	

	uint32_t base = k.i.rs;
	uint32_t offset = k.i.imm;
	uint32_t addr = reg[base].val + (signed) offset;
	uint32_t value;
	
	

	if (addr<memory->start_mem) ERROR_MSG("La memoire commence en 0x%08x",memory->start_mem);
	if (addr>STOP_MEM) ERROR_MSG("La memoire termine en 0x%08x",STOP_MEM);
	tmp = find_word(memory, addr, &value);

	if (tmp==cmd_unknown)
	{	printf("\n");
		ERROR_MSG("L'adresse 0x%08x n'est pas allouee", addr);
		return cmd_unknown;
	}
	else {
		reg[k.i.rt].val=value;
		return cmd_ok;
	}
}

