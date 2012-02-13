#include <stdio.h>
#include <stdlib.h>

void main()
{
	int n;
	scanf("%d",&n);
	srand(time(NULL));
	char c[n];
	int a,b,i;
	for (i=0; i<n; i++)
	{
		a=0+rand()%3;
		switch(a)
		{
			case 0 : {b=0+rand()%10; c[i]=(char)(b+48);}; break;
			case 1 : {b=0+rand()%26 + 97; c[i]=(char)b;}; break;
			case 2 : {b=0+rand()%26 + 65; c[i]=toupper((char)b);}; break;
			default : break;
		}
		printf("%c",c[i]);
	}
}
