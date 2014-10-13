#include <stdio.h>
#include <string.h>

int rec_hexa(char *inter)
{
	char chaine[1024];
	strcpy(chaine, inter);
	int i=2;
	int n=0;

	while(chaine[i] != '\0')
	{
		if(chaine[0] == '0' && chaine[1] == 'x' && (chaine[i] == '0' ||chaine[i] == '1' ||chaine[i] == '2' ||chaine[i] == '3' ||chaine[i] == '4' ||chaine[i] == '5' ||chaine[i] == '6' ||chaine[i] == '7' ||chaine[i] == '8' ||chaine[i] == '9' || chaine[i] == 'a' || chaine[i] == 'A'|| chaine[i] == 'b' || chaine[i] == 'B'|| chaine[i] == 'c' || chaine[i] == 'C'|| chaine[i] == 'd' || chaine[i] == 'D'|| chaine[i] == 'e' || chaine[i] == 'E'|| chaine[i] == 'f' || chaine[i] == 'F'))
		{				
			//if(chaine[i] == '0' ||chaine[i] == '1' ||chaine[i] == '2' ||chaine[i] == '3' ||chaine[i] == '4' ||chaine[i] == '5' ||chaine[i] == '6' ||chaine[i] == '7' ||chaine[i] == '8' ||chaine[i] == '9' || chaine[i] == 'a' || chaine[i] == 'A'|| chaine[i] == 'b' || chaine[i] == 'B'|| chaine[i] == 'c' || chaine[i] == 'C'|| chaine[i] == 'd' || chaine[i] == 'D'|| chaine[i] == 'e' || chaine[i] == 'E'|| chaine[i] == 'f' || chaine[i] == 'F')
			
		}
		
		else
		{
			n++;
		}
		
		i++;
	}

	if(n==0)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}



int is_plage(char *chaine)
{
	int i=0;
	char r[1024];
	
	while (chaine[i] != ':')
		{ 
			r[i]=chaine[i];
			i++;
		}
	r[i+1]='\0';
	if (rec_hexa(r)==1)
		{
			i=i+1;
			char g[1024];

				while (chaine[i] != '\0') 
			{
				g[i]=chaine[i];
				i++;
			}

				g[i+1]='\0';
				if (rec_hexa(g)==1) {return 1;}
		}

	else return 0;
}

/*
main()
{

	char *r;
	

	gets(r);
	printf("\n");
	int n=rec_hexa(r);
	//printf("%d\n",n);
	int m=is_plage(r);
	printf("%d\n",m);
	

}*/
