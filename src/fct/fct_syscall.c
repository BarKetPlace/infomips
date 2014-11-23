#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SYSCALL


int fct_syscall(inst k, mem memory, registre* reg, Liste dico)
{
	switch(reg[2].val){
		case 1: 
			/*reg[]=affiche_entier();*/ break;
		case 4:break;
			//reg[]
		case 5:break;

		case 8:break;
		
		case 10:break;
	}
	//int off=((short)inst.i.imm)<<2;
	//if (reg[inst.i.rs]>=0)
		
}
