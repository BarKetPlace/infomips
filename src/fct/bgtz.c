#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction BGTZ


int fct_bgtz(inst k, mem memory, registre* reg)
{
	int off=((short)k.i.imm)<<2;
	if (reg[k.i.rs].val>0)
		{
		reg[PC].val=reg[PC].val+off;
		return cmd_ok;
		}
	else {return cmd_unknown;}
}

/*int main()
{
	inst l;
	Liste dico=NULL;
	l.i.rs=2;
	l.i.imm=2c;
	//scanf("l.i.rs = %d",&(l.i.rs));
	//scanf("l.i.imm = %d",&(l.i.imm));
	//printf("reg[%d] : Ox%08x", l.i.rs, reg[l.i.rs].val);
	mem memory;
	registre* reg;
	printf("reg(PC) : 0x%08x", reg[PC].val);
	int u=fct_bgtz(l,memory,reg, dico);
	printf("0x%08x=PC+0x%08x", reg[PC].val,(l.i.imm)<<2);
	return 1;
}*/
