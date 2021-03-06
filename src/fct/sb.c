#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SB


int fct_sb(inst k, mem memory, registre* reg)
{
	uint32_t vale=reg[k.i.rt].val;
	int tmp;
	uint32_t m;
	uint32_t vals;
	vale=reg[k.i.rt].val;
	signed int l=reg[k.i.rs].val+(signed long)k.i.imm;
	tmp = find_word(memory, l, &m);

	if (l<memory->start_mem) ERROR_MSG("La memoire commence en 0x%08x",memory->start_mem);
	if (l>STOP_MEM) ERROR_MSG("La memoire termine en 0x%08x",STOP_MEM);

	if (tmp==cmd_unknown)
	{	printf("\n");
		ERROR_MSG("L'adresse 0x%08x n'est pas allouee", l);
		return cmd_unknown;
	}
	else {
		m=vale;
		vals = swap_mot(vale);
		if (l%4==0) 		reg[k.i.rt].val=vals&0x000000ff;
		else if (l%4==1) 	reg[k.i.rt].val=(vals&0x0000ff00)>>8;
		else if (l%4==2)	reg[k.i.rt].val=(vals&0x00ff0000)>>16;
		else if (l%4==3)	reg[k.i.rt].val=(vals&0xff000000)>>24;
		reg[PC].val+=4;
		return cmd_ok;
	}
	reg[PC].val+=4;
	return cmd_ok;
}

