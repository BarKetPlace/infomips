#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"


int fct_exec(uint32_t adresse, mem memory, registre* reg, Liste dico){

		union inst_poly mot;
		definition def;	
		int tmp;
		//On va chercher le mot de l'instruction à l'adresse indiquée par le pc
		if ( find_val(memory, adresse, &(mot.code)) != cmd_ok ) { 
			WARNING_MSG("Impossible de trouver un mot en 0x%08x", reg[PC].val);	
			return cmd_unknown;
		}
		
		//On va ensuite chercher la definition correspondante
		if ( !(def = find_def(dico, mot) ) ){ 
			WARNING_MSG("Impossible de trouver une definition pour le mot 0x%08x en 0x%08x", mot.code ,reg[PC].val);	
			return cmd_unknown;
		}
		
		//On execute ensuite la fonction def->f sur le mot
		tmp = def->f(mot, memory, reg, dico);
		if (tmp != cmd_ok) return tmp;
		printf("0x%08x :: ",reg[PC].val);
		print_disasm(def, mot);
		return cmd_ok;
}
