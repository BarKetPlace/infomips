#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"




int fct_exec(uint32_t adresse, mem memory, registre* reg, Liste dico, int* ptemoin){
//DEBUG_MSG("");
		union inst_poly mot;
		definition def;	
		int tmp;
		//On va chercher le mot de l'instruction à l'adresse indiquée par le pc
		if ( find_word(memory, adresse, &(mot.code)) != cmd_ok ) { 
			WARNING_MSG("Impossible de trouver un mot en 0x%08x", adresse);	
			return cmd_unknown;
		}//DEBUG_MSG("");
		//DEBUG_MSG("");
		//On va ensuite chercher la definition correspondante
		if ( !(def = find_def(dico, mot) ) ){ 
			WARNING_MSG("Impossible de trouver une definition pour le mot 0x%08x en 0x%08x", mot.code ,adresse);	
			return cmd_unknown;
		}
		//DEBUG_MSG("%d",*ptemoin);
		if ( !strcmp(def->nom, "jr") || !strcmp(def->nom, "j") || !strcmp(def->nom, "jal") || !strcmp(def->nom, "jalr")) 
		 *ptemoin = 1; // Passage du temoin a un pour la fonction step
		
		//DEBUG_MSG("");
		//DEBUG_MSG("%s",def->nom);
		//On execute ensuite la fonction def->f sur le mot
		tmp = def->f(mot, memory, reg);//DEBUG_MSG("");
		if (tmp != cmd_ok) return tmp;
		
		
		printf("0x%08x :: ",adresse);
		print_disasm(def, mot);
		//DEBUG_MSG("");
		return cmd_ok;
}
