#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct p_const
{
	float count;
	unsigned long long int num;
	p_const* next;
};

void p_output(p_const *head)
{
	p_const *p=head;
	while(p)
	{
		printf("%Ld) %f\n",p->num,p->count);
		p=p->next;
	}
}

p_const *p_init(p_const *head)
{
	int n;
	float x;
	printf("Введите желаемое количество коэффициентов:");
	scanf("%d",&n);
	printf("Введите коэффициенты (разделяя пробелом или переводом строки):\n");
	for (long long int i=0; i<n; i++)
	{
		scanf("%f",&x);
		if (x!=0)
		{
			p_const *p=new p_const;
			p->count=x;
			p->num=i;
			p->next=head;
			head=p;
		}
	}
	return head;
}

void p_delete(p_const *head)
{
	p_const *p;
	while (head != NULL)
	{
		p=head->next;
		delete head;
		head=p;
	}
}

p_const *p_search_num(p_const *head, unsigned long long int num)
{
	p_const *p=head,*q,*t;
	bool insert=false;
	while (p && (p->num!=num) && (!insert))
	{
		q=p;
		p=p->next;
		if ((p!=NULL) && (q->num>num) && (p->num<num))
			{
				t=new p_const;
				q->next=t;
				t->num=num;
				t->next=p;
				insert=true;
			}
	}
	if (insert)
	{
		p=t;
	}
	return p;
}

void p_delete_elem(p_const *head, unsigned long long int num)
{
	p_const *q,*p=head;
	while (p && (p->num!=num)) {q=p; p=p->next;}
	if (p->num == num)
	{
		q->next=p->next;
		delete p;
		p=NULL;
	}
}

p_const *p_replace(p_const *head)
{
	p_output(head);
	float count;
	unsigned long long int num;
	p_const *p;
	printf("Введите номер коэффициента, который вы хотите изменить или создать (для удаления используйте номера существующих элементов):");
	scanf("%Ld",&num);
	printf("Введите новое значение коэффициента (введите 0, если хотите убрать этот коэффициент):");
	scanf("%f",&count);
	if (count == 0) p_delete_elem(head,num);
	else
	{
		p=p_search_num(head,num);
		if (p!=NULL) p->count=count;
		else 
		{
			p=new p_const;
			p->num=num;
			p->count=count;
			p->next=head;
			head=p;
		}
	}
	printf("Новые коэффициенты:\n");
	p_output(head);
	return head;
}

double p_calc(p_const *head)
{
	float x;
	scanf("%f",&x);
	p_const *p=head;
	double s=0;
	while (p) 
	{
		float c=p->count;
		int n=p->num;
		s+=c * pow(x,n);
		p=p->next;
	}
	return s;
}

double p_sum(p_const *head1, p_const *head2)
{
	printf("Введите значение X:");
	double s;
	s=p_calc(head1);
	printf("Введите значение Y:");
	s+=p_calc(head2);
	return s;
}

void main_menu()
{
	p_const *head1=NULL,*head2=NULL;
	char choice='a';
	bool h1=false,h2=false,d=true;
	while (d)
	{
		printf("\nМеню программы (для выбора действия введите номер и нажмите Enter:\n");
		int i=0;
		printf("%d) Вывести задание\n",i);
		if ((!h1) && (!h2))
		{
			i++;
			printf("%d) Создать список коэффициентов многочлена\n",i);
		}
		else
		{
			if ((h1) && (!h2))
			{
				i++;
				printf("%d) Вывести коэффициенты первого многочлена\n",i);
				i++;
				printf("%d) Изменить, удалить или добавить коэффициент первого многочлена\n",i);
				i++;
				printf("%d) Вычислить первый многочлен для заданного X\n",i);
				i++;
				printf("%d) Создать список коэффициентов второго многочлена\n",i);
			}
			else
			{
				i++;
				printf("%d) Вывести коэффициенты первого многочлена\n",i);
				i++;
				printf("%d) Изменить, удалить или добавить коэффициент первого многочлена\n",i);
				i++;
				printf("%d) Вычислить первый многочлен для заданного X\n",i);
				i++;
				printf("%d) Вывести коэффициенты второго многочлена\n",i);
				i++;
				printf("%d) Изменить, удалить или добавить коэффициент второго многочлена\n",i);
				i++;
				printf("%d) Вычислить второй многочлен для заданного Y\n",i);
				i++;
				printf("%d) Вычислить сумму многочленов P(x) и G(y) для заданных x и y\n",i);
			}
		}
		i++;
		printf("%d) Выйти из программы\n",i);
		scanf("\n%c",&choice);				
		system("clear"); 
		if ((!h1) && (!h2))
		{
			switch (choice)
			{
				case '0': printf("Написать программу, реализующую в виде списка представление многочлена P(x)=a_0+a_1*x+...+a_i*x^i, где а_i - вещественные числа, i - целые положительные числа, причем, если a_i=0, то соответствующий элемент-слагаемое должен отсутствовать в списке. Пользователь должен иметь возможность произвольно добавлять элементы-слагаемые через меню. Реализовать функцию сложения двух многочленов.\n");break;
				case '1':
				{
					head1=p_init(head1);
					h1=true;
				}break;
				case '2': d=false;break;
			}
		}
		else
		{
			if ((h1) && (!h2))
			{
				switch (choice)
				{
					case '0': printf("Написать программу, реализующую в виде списка представление многочлена P(x)=a_0+a_1*x+...+a_i*x^i, где а_i - вещественные числа, i - целые положительные числа, причем, если a_i=0, то соответствующий элемент-слагаемое должен отсутствовать в списке. Пользователь должен иметь возможность произвольно добавлять элементы-слагаемые через меню. Реализовать функцию сложения двух многочленов\n");break;
					case '1': p_output(head1);break;
					case '2': head1=p_replace(head1);break;
					case '3':
					{
						printf("Введите значение X:");
						double s;
						s=p_calc(head1);
						printf("Значение P(x)=%f",s);
					}break;
					case '4':
					{
						head2=p_init(head2);
						h2=true;
					}break;
					case '5': d=false;break;
				}
			}
			else
			{
				switch (choice)
				{
					case '0': printf("Написать программу, реализующую в виде списка представление многочлена P(x)=a_0+a_1*x+...+a_i*x^i, где а_i - вещественные числа, i - целые положительные числа, причем, если a_i=0, то соответствующий элемент-слагаемое должен отсутствовать в списке. Пользователь должен иметь возможность произвольно добавлять элементы-слагаемые через меню. Реализовать функцию сложения двух многочленов.\n");break;
					case '1': p_output(head1);break;
					case '2': head1=p_replace(head1);break;
					case '3':
					{
						printf("Введите значение X:");
						double s;
						s=p_calc(head1);
						printf("P(x)=%f\n",s);
					}break;
					case '4': p_output(head2);break;
					case '5': head2=p_replace(head2);break;
					case '6':
					{
						printf("Введите значение Y:");
						double s;
						s=p_calc(head2);
						printf("G(y)=%f\n",s);
					}break;
					case '7': printf("P(x)+G(y)=%f\n",p_sum(head1,head2));break;
					case '8': d=false;break;
				}
			}
		}
	}
	p_delete(head1);
	p_delete(head2);
}

int main()
{
	printf("Написать программу, реализующую в виде списка представление многочлена P(x)=a_0+a_1*x+...+a_i*x^i, где а_i - вещественные числа, i - целые положительные числа, причем, если a_i=0, то соответствующий элемент-слагаемое должен отсутствовать в списке. Пользователь должен иметь возможность произвольно добавлять элементы-слагаемые через меню. Реализовать функцию сложения двух многочленов.\n");
	main_menu();
	return 0;
}
