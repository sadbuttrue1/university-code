/* using: to get password enter length of it.
 * also it save pass to entered location
 */
 
#include <stdio.h>
#include <stdlib.h>

struct str_const
{
	char c;
	str_const *next;
};

void menu();

void string_read(char *c)
{
	int i=0;
	getchar();
	while((c[i]=getchar())!='\n' && (c[i]!=EOF)) i++;
	c[i]=0;
}

void restart()
{
	printf("Do you want to generate another one?(y/n)");
	char start;
	scanf("\n%c",&start);
	if (start=='y')	menu();
}

void save(int n, char *c)
{
	printf("\nDo you want to save it?(y/n) ");
	char s;
	scanf("\n%c",&s);
	if (s=='y')
	{
		printf("Enter file name: ");
		char name[200];
		string_read(name);
		FILE *f;
		f=fopen(name,"w");
		fprintf(f,"%s",c);
		fclose(f);
	}
	restart();
}

void generator(char *c, int n)
{
	srand(time(NULL));
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
	}
	c[i]=0;
}

void menu()
{
	printf("Enter length of pass: ");
	int n;
	scanf("%d",&n);
	char c[n];
	generator(c,n);
	printf("Here it is:\n%s",c);
	save(n,c);
}

int main()
{
	menu();
	return 0;
}
