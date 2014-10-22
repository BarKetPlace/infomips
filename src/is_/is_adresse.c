#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include "is_.h"

/*int is_hexa(char* chaine) {
	//DEBUG_MSG("%s",chaine);
    int i=2;
	if (chaine!=NULL && strlen(chaine)>2&& chaine[0]=='0' && chaine[1]=='x' && sscanf(chaine,"%x",&i)==1)
	{		
		for (i=2; i<strlen(chaine);i++)
		{ 	
			if ( isxdigit(chaine[i]) == 0 ) return 0;
		}
		return 1;
	}
	return 0;
}*/


int is_adresse(char *chaine)
{
	if (is_hexa(chaine)==1) {return 1;}
	else {return 0;}
}


/*int main()
{
	char *r;
	gets(r);
	printf("\n");
	int n=is_adresse(r);
	printf("%d",n);
	printf("\n");
}*/	
