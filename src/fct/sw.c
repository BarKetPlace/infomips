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
	short offset = k.i.imm;
	int base = k.i.rs;

	uint32_t adresse = reg[base].val + offset;
	if (adresse<memory->start_mem) ERROR_MSG("La memoire commence en 0x%08x",memory->start_mem);
	if (adresse>STOP_MEM) ERROR_MSG("La memoire termine en 0x%08x",STOP_MEM);
	
	
	else {
		//DEBUG_MSG("base : %x\tstore word : %x\tat : %x",base,reg[k.i.rt].val, adresse);
		reg[PC].val+=4;
		return load_word(memory, adresse, reg[k.i.rt].val);
	}

}

