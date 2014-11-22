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
	reg[31].val = reg[PC].val + 8;
	tmp = fct_exec(k.j.target<<2, memory, reg, dico);

	if (tmp != cmd_ok) return tmp;
	
}

