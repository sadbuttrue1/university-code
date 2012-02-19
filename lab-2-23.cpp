#include <stdio.h>
#include <stdlib.h>

void matrix_input(float *a, int n, int m)
{
	int i,j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<m; j++)
		{
			scanf("%f",&a[i*m+j]);
		}
	}
}

void s_points(float *a, int n, int m)
{
	float imin[n],imax[n],jmax[m],jmin[m];
	int i,j;
	for (i=0; i<n; i++)
	{
		imax[i]=imin[i]=a[i*m];
	}
	for (j=0; j<m; j++)
	{
		jmin[j]=jmax[j]=a[j];
	}
	for (i=0; i<n; i++)
	{
		for (j=0; j<m; j++)
		{
			if (a[i*m+j]<imin[i]) imin[i]=a[i*m+j];
			if (a[i*m+j]>imax[i]) imax[i]=a[i*m+j];
			if (a[i*m+j]>jmax[j]) jmax[j]=a[i*m+j];
			if (a[i*m+j]<jmin[j]) jmin[j]=a[i*m+j];			
		}
	}
	for (i=0; i<n; i++)
	{
		for (j=0; j<m; j++)
		{
			if (((a[i*m+j]==imin[i])&&(a[i*m+j]==jmax[j])) || ((a[i*m+j]==imax[i])&&(a[i*m+j]==jmin[j])))
			printf("%f (%d,%d)\n",a[i*m+j],i,j);
		}
	}
}

void ex1()
{
	printf("Введите размерность массива в формате NxM:");
	int n,m;
	scanf("\n%dx%d",&n,&m);
	float array[n*m];
	printf("Введите элементы массива:\n");
	matrix_input(array,n,m);
	s_points(array,n,m);
}

void hex(int x)
{
	int dig[40],i=0;
	while (x/16>0)
	{
		dig[i]=x%16;
		x/=16;
		i++;
	}
	dig[i]=x;
	char str[20];
	int n;
	for (n=0; n<i+1; n++)
	{
		switch (dig[n])
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			str[n]=(char)(dig[n]+48);break;
			case 10: str[n]='A';break;
			case 11: str[n]='B';break;
			case 12: str[n]='C';break;
			case 13: str[n]='D';break;
			case 14: str[n]='E';break;
			case 15: str[n]='F';break;
			default : break;
		}
	}
	for (n=i; n>-1; n--)
	{
		printf("%c",str[n]);
	}
}

void ex2()
{
	printf("Введите число, которое нужно представить в шестнадцетиричном виде\n");
	int x;
	scanf("%d",&x);
	hex(x);
}

void ex()
{
	printf("Введите номер задания (1 или 2 или q для выхода):\n");
	char c;
	scanf("\n%c",&c);
	switch (c)
	{
		case '1': ex1();break;
		case '2': ex2();break;
		case 'q': exit;break;
		default : break;
	}
}

int main()
{
	printf("Написать программу, которая вводит с клавиатуры массив NxM вещественных чисел,\nещет седловые точки в массиве и выводит их и их позиции пользователю;\nзатем вводит с клавиатуры число, преобразовывает его в строку в шестнадцатеричном представлении и выводит результат пользователю.\n");
	ex();
	printf("\nПерезапустить? (y/n)\n");
	char start;
	scanf("\n%c",&start);
	if (start=='y')
	{
		main();
	}
	return 0;
}
