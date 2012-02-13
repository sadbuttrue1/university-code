/* using: to get password enter length of it.
 * also it save pass to entered location
 */
 
#include <stdio.h>
#include <stdlib.h>

void restart()
{
	printf("Do you want to generate another one?(y/n)");
	char start;
	scanf("\n%c",&start);
	if (start=='y')
	{
		main();
	}
	else
	{
		exit;
	}
}

void save(int n, char c[n])
{
	printf("\nDo you want to save it?(y/n) ");
	char s,name[200];
	int i;
	scanf("\n%c",&s);
	if (s=='y')
	{
		printf("Enter file name: ");
		scanf("\n%c",&name);
		freopen(name,"w",stdout);
		for (i=0; i<n; i++) {printf("%c",c[i]);}
		fclose(stdout);
	}
	restart();
}

int main()
{
	int n;
	printf("Enter length of pass: ");
	scanf("%d",&n);
	srand(time(NULL));
	char c[n];
	int a,b,i;
	printf("Here it is: ");
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
	save(n,c);
	return 0;
}
