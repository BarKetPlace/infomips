#include <stdio.h>
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "fct.h"
#include "dico.h"

#include "typesmem.h"


// Fonction add
// Definir max_inst


int fct_add(inst k, mem memory, registre* reg)

{
	 
	long long temp=reg[k.r.rs].val+reg[k.r.rt].val;
	if (temp<=max_inst) {reg[k.r.rd].val=temp;reg[PC].val+=4; return cmd_ok;}
	else {WARNING_MSG("Erreur"); return cmd_unknown;}
}


/*int main()
{
	inst l;
	Liste dico=NULL;
	l.r.rs=2;
	l.r.rt=6;
	//scanf("l.r.rs = %d",&(l.r.rs));
	//scanf("l.r.rt = %d",&(l.r.rt));
	mem memory;
	registre* reg;
	int u=fct_add(l,memory,reg, dico);
	printf("rd = 0x%08x", reg[l.r.rd].val);
	return 1;
}*/

