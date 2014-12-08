
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction LB


int fct_lb(inst k, mem memory, registre* reg)
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
		value = (signed) value;
		value = FLIP_ENDIANNESS(value);
		if (addr%4==0) 		reg[k.i.rt].val = value&0x000000ff;
		else if (addr%4==1) 	reg[k.i.rt].val=(value&0x0000ff00)>>8;
		else if (addr%4==2)	reg[k.i.rt].val=(value&0x00ff0000)>>16;
		else if (addr%4==3)	reg[k.i.rt].val=(value&0xff000000)>>24;
		
	}
	reg[PC].val+=4;
	return cmd_ok;
}



