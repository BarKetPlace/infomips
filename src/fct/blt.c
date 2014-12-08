#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"

int fct_blt(inst k, mem memory, registre *reg){
	reg[PC].val+=4;
	return cmd_ok;
}
