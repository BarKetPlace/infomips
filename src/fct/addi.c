#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

// Fonction ADDI
// Definir max_inst

int fct_addi(inst k, mem memory, registre* regs)
{
	long long temp=regs[k.i.rs].val+regs[k.i.imm].val;
	if (temp<=max_inst) {regs[k.i.rt].val=temp; return cmd_ok;}
	else {return cmd_unknown;}
}

int main()
{
	inst l;
	int l.i.rs=0;
	int l.i.imm=0;
	scanf("l.r.rs = %d",&(l.i.rs));
	scanf("l.r.rt = %d",&(l.i.imm));
	mem memory;
	registre* reg;
	int u=fct_add(l,memory,reg);
	printf("rd = 0x%08x", reg[l.i.rd].val);
	return 1;
}
