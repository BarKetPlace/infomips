#include <stdio.h>
#include <stdlib.h>



#include "cmd.h"
#include "mem.h"
#include "notify.h"
#include "bits.h"
#include "formats.h"
#include "types.h"
#include "syms.h"
#include "section.h"
#include "reg.h"
#include "is_.h"

// Fonction qui ajoute une valeur dans le stack et se déplace à la prochaine adresse

int ajout_pile( mem memory, registre *reg, uint32_t ajout )
{
		load_word( memory, reg[29].val, ajout );
		DEBUG_MSG( "0x%08x a été ajouté à la pile à l'adresse 0x%08x \n", ajout, reg[29].val );
		reg[29].val += 4;
		return cmd_ok;
}


// Fonction qui enlève la dernière valeur ajoutée dans le stack

int enleve_pile( mem memory, registre *reg, uint32_t* res )
{
		reg[29].val += -4;
		find_word( memory, reg[29].val, &res );
		load_word( memory, reg[29].val, 0 );
		DEBUG_MSG("0x%08x a été enlevé de la pile à l'adresse 0x%08x \n", *res, reg[29].val );
		return cmd_ok;
}


// Fonction qui permet de visualiser l'adresse que pointe le pointeur stack

int visualiser_pile( mem memory, registre *reg )
{
		uint32_t debut = 0xfffff000 ;
		uint32_t fin = 0xffffffff ;
		print_case_mem ( mem, debut, fin );
		return cmd_ok;
}
