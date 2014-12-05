#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "is_.h"
#include "notify.h"


int is_hexa(char* chaine) {
	//DEBUG_MSG("%s",chaine);
    uint i=2;
	if (chaine!=NULL && strlen(chaine)>2&& chaine[0]=='0' && chaine[1]=='x' && sscanf(chaine,"%x",&i)==1)
	{		
		for (i=2; i<strlen(chaine);i++)
		{ 	
			if ( isxdigit(chaine[i]) == 0 ) return 0;
		}
		return 1;
	}
	return 0;
}

