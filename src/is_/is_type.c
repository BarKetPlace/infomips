#include <stdio.h>
#include <string.h>
#include "is_.h"
int is_type(char *chaine)
{
	if (strcmp(chaine,"byte")==0 || strcmp(chaine,"word")==0 )
	{
		return 1;
	}
	else {return 0;}
}
/*
int main ()
{
	char *r;
	gets(r);
	printf("\n");
	int n=is_type(r);
	printf("%d",n);
	printf("\n");
}*/
