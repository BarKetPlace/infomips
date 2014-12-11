#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"

// Fonction blez

int fct_blez(inst k, mem memory, registre *reg){
	int off=((short)k.i.imm)<<2;
	if ((signed)reg[k.i.rs].val<=0)
		{
		reg[PC].val+=4;
		reg[PC].val=reg[PC].val+off;
		return cmd_ok;
		}
	else {reg[PC].val+=4; return cmd_ok;}
}
