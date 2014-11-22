#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction ADDU
// Definir max_inst

int fct_addu(inst k, mem memory, registre* reg, Liste dico)
{
	long long temp=reg[k.r.rs].val+reg[k.r.rt].val;
	reg[k.r.rd].val=temp; 
	return cmd_ok;
}

