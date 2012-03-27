/* using: to get password enter length of it.
 * also it save pass to entered location
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct str_const
{
	char c;
	str_const *next;
};

void str_delete(str_const *&head)
{
	str_const *p;
	while (head != NULL)
	{
		p=head->next;
		delete head;
		head=p;
	}
}

void str_output(str_const *str)
{
	str_const *p=str;
	while(p)
	{
		printf("%c",p->c);
		p=p->next;
	}
	printf("\n");
}

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
	printf("Do you want to generate another one?(y/n):");
	char start;
	scanf("\n%c",&start);
	if (start=='y')	menu();
}

void save(str_const *str)
{
	printf("\nDo you want to save it?(y/n):");
	char s;
	scanf("\n%c",&s);
	if (s=='y')
	{
		printf("Enter file name: ");
		char name[200];
		string_read(name);
		FILE *f;
		f=fopen(name,"w");
		str_const *p=str;
		while(p)
		{
			fprintf(f,"%c",p->c);
			p=p->next;
		}
		fprintf(f,"%c",0);
		fclose(f);
	}
	restart();
}

void generator(unsigned long long n, str_const *&str)
{
	srand(time(NULL));
	int a,b;
	for (unsigned long long i=0; i<n; i++)
	{
		a=0+rand()%3;
		str_const *p=new str_const;
		switch(a)
		{
			case 0 : {b=0+rand()%10; p->c=(char)(b+48);}; break;
			case 1 : {b=0+rand()%26 + 97; p->c=(char)b;}; break;
			case 2 : {b=0+rand()%26 + 65; p->c=(char)b;}; break;
			default : break;
		}
		p->next=str;
		str=p;
	}
}

void menu()
{
	printf("Enter length of pass: ");
	unsigned long long n;
	scanf("%Ld",&n);
	str_const *str=NULL;
	generator(n,str);
	printf("Here it is:\n");
	str_output(str);
	save(str);
	str_delete(str);
}

int main()
{
	menu();
	return 0;
}
