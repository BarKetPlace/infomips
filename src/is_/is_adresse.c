#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "is_.h"


int is_adresse(char *chaine)
{
	if (is_hexa(chaine)==1) {return 1;}
	else {return 0;}
}

/*
int main()
{
	char *r;
	gets(r);
	printf("\n");
	int n=is_adresse(r);
	printf("%d",n);
	printf("\n");
}
*/	
