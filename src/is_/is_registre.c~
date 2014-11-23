#include <stdio.h>
#include <string.h>
#include "is_.h"

int is_registre(char* chaine)
{	int i;
	if (chaine[0]=='$')
	{
	char * reg_str[]={"zero","at","v0","v1","v1","a0","a1","a2","a3","t0","t1",
			"t2","t3","t4","t5","t6","t7","s0","s1","s2","s3","s4","s5",
			"s6","s7","t8","t9","k0","k1","gp","sp","fp","ra","pc","HI","LO"};
	
	for (i=0;i<NBREG;i++)
	{
		if ( !(strcmp(chaine+1,reg_str[i])) ) return i;
	}
	}
	return -1;
}
	/*while(chaine[i] != '\0')
{
		switch (chaine[i])
		{
		case "O:

    	if (chaine!=NULL && strlen(chaine)>2&& chaine[0]=='0' && chaine[1]=='x'  && ( isdigit(i)==1 || chaine[i] == 'a' || chaine[i] == 'A'|| chaine[i] == 'b' || chaine[i] == 'B'|| chaine[i] == 'c' || chaine[i] == 'C'|| chaine[i] == 'd' || chaine[i] == 'D'|| chaine[i] == 'e' || chaine[i] == 'E'|| chaine[i] == 'f' || chaine[i] == 'F'))
//&& sscanf(chaine,"%x",&i)==1
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
}
*/
/*
int main()
{
	char *r;
	gets(r);
	printf("\n");
	int n=is_hexa(r);
	printf("%d",n);
	printf("\n");
	
}
*/
