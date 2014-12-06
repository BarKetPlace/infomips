#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"

int fct_jal(inst k, mem memory, registre* reg, Liste dico)
{	int tmp;
	reg[31].val = reg[PC].val + 4; // On avance le PC et on le sauve dans le registre 31
	//DEBUG_MSG("%x",k.j.target);
	
	tmp = fct_exec(k.j.target, memory, reg, dico);
	//Après cette instruction ^  le PC retrouve sa valeur normale
	reg[PC].val = reg[31].val;
	// Et le programme continu
	return tmp;
	//if (tmp != cmd_ok) return tmp;
	
}

