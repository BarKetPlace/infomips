#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "is_.h"

int is_valeur(char* chaine) 
{
	int i=0;
	while (chaine[i]!='\0')
	{
		if (isdigit(chaine[i])==0) {return 0;}
		i++;
	}
	return 1;
}
	
/*int main()
{
	char r[1024];
	gets(r);
	printf("\n");
	int n=is_valeur(r);
	printf("%d",n);
	printf("\n");
}*/

