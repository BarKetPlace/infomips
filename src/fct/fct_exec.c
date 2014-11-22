#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"
#include "typesmem.h"
#include "fct.h"

int fct_exec(uint32_t adresse, virtualmem vm){
		mem memory = vm->memory;
		Liste dico = vm->dico;
		registre* reg = vm->reg;

		union inst_poly mot;
		definition def;	
		
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
		def->f(mot, memory, reg);
		
}
