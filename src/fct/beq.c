#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"

// Fonction beq


int fct_beq(inst k, mem memory, registre* reg, Liste dico)
{
	int off=(k.i.imm)<<2;
	//DEBUG_MSG("%d",off);
	int c=reg[k.i.rs].val==reg[k.i.rt].val;
	if (c)
		{
		  reg[PC].val+=4;
		reg[PC].val=reg[PC].val+off;
		//	DEBUG_MSG("%x",reg[PC].val);
		return cmd_ok;
		}
	else {return cmd_unknown;}
}

