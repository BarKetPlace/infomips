#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"


// Fonction JALR


int fct_jalr(inst k, mem memory, registre *reg)
{	int tmp;
	reg[k.r.rd].val=reg[PC].val + 8; 
	reg[PC].val = reg[k.r.rs].val;
	
	//tmp = fct_exec(reg[PC].val, memory, reg, dico);
	//Après cette instruction ^  le PC retrouve sa valeur normale
	//reg[PC].val = reg[k.r.rd].val;
	// Et le programme continu
	//if (tmp != cmd_ok) return tmp;
		
	return cmd_ok;
}
