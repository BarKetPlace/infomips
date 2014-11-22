
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

int fct_add(inst k, mem memory, registre* reg, Liste dico)
{
	 
	long long temp=reg[k.r.rs].val+reg[k.r.rt].val;
	if (temp<=max_inst) {reg[k.r.rd].val=temp; return cmd_ok;}
	else {WARNING_MSG("Erreur"); return cmd_unknown;}
}

/*
int main()
{
	inst l;
	int l.r.rs;
	int l.r.rt;
	scanf("l.r.rs = %d",&(l.r.rs));
	scanf("l.r.rt = %d",&(l.r.rt));
	mem memory;
	registre* reg;
	int u=fct_add(l,memory,reg);
	printf("rd = 0x08%x", reg[k.r.rd].val);
	return 1;
}*/

