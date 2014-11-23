
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"
#include "dico.h"

// Fonction add
// Definir max_inst


int fct_add(inst k, mem memory, registre* regs)
{
	 
	long long temp=regs[k.r.rs].val+regs[k.r.rt].val;
	if (temp<=max_inst) {regs[k.r.rd].val=temp; return cmd_ok;}
	else {WARNING_MSG("Erreur"); return cmd_unknown;}
}


int main()
{
	inst l;
	int l.r.rs=0;
	int l.r.rt=0;
	scanf("l.r.rs = %d",&(l.r.rs));
	scanf("l.r.rt = %d",&(l.r.rt));
	mem memory;
	registre* reg;
	int u=fct_add(l,memory,reg);
	printf("rd = 0x%08x", reg[l.r.rd].val);
	return 1;
}

