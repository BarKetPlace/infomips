#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "emulateur.h"
#include "mem.h"
#include "reg.h"
#include "is_.h"
#include "pile.h"

/**
 * version de la commande test qui analyse la chaîne entrée à 
 * l'interpreteur. Si la commande est correcte elle est executée. 
 * Si la commande contient plusieurs parametres valides, elle 
 * est excutée plusieurs fois.
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en case de succes, un nombre positif sinon
 */

int testcmd(interpreteur inter) {


    DEBUG_MSG("Chaine : %s", inter->input);
    int return_value=0;
    
		int no_args=1;

	

    /* la commande test attend un argument hexa */
    int hexValue;
    char * token=NULL;
    
    /* la boucle permet d'executé la commande de manière recurrente*/ 
    /* i.e., tant qu'il y a un hexa on continue*/ 
    while((token = get_next_token(inter))!=NULL && return_value==0) {
    		no_args=0;
        switch(get_type(token)) {
        case HEXA:
            sscanf(token,"%x",&hexValue);
            return_value = _testcmd(hexValue);
            break;
        default :
            WARNING_MSG("value %s is not a valid argument of command %s\n",token,"testcmd");
            return 1;
        }
    }

	/*mem memory;
	registre* reg;
	uint32_t valeur=45;
	ajout_pile(memory, &reg, valeur);
	DEBUG_MSG("ok");
	visualiser_pile(memory, &reg);*/
	


    if(no_args){
            WARNING_MSG("no argument given to command %s\n","testcmd");
            return 1;
        }


    return return_value;
}
