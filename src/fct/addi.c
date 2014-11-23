#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction ADDI
// Definir max_inst

int fct_addi(inst k, mem memory, registre* reg, Liste dico)
{	//DEBUG_MSG("%d",k.i.imm);
	long long temp=reg[k.i.rs].val + k.i.imm;//DEBUG_MSG("%d",temp);
	if (temp<=max_inst) {reg[k.i.rt].val=temp; return cmd_ok;}
	else {return cmd_unknown;}
}

/*int main()
{
	inst l;
	Liste dico=NULL;
	l.i.rs=2;
	l.i.imm=12;
	//scanf("l.i.rs = %d",&(l.i.rs));
	//scanf("l.i.imm = %d",&(l.i.imm));
	mem memory;
	registre* reg;
	int u=fct_addi(l,memory,reg, dico);
	printf("rd = 0x%08x", reg[l.i.rt].val);
	return 1;
}*/
