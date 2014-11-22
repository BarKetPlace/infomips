#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




int fct_j(inst k, mem memory, registre* reg, Liste dico)
{
	int offset = (k.j.target<<2);
	reg[PC].val = reg[PC].val + offset;

}


