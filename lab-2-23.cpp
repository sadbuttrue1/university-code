#include <stdio.h>
#include <stdlib.h>

void matrix_input(float *a, int n, int m)
{
	printf("Введите элементы массива (построчно через пробел):\n");
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			scanf("%f",&a[i*m+j]);
		}
	}
}

void matrix_output(float *a, int n, int m)
{
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			printf("%f ",a[i*m+j]);
		}
		printf("\n");
	}
	printf("\n");
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
	matrix_input(array,n,m);
	printf("\nВведенная вами матрица:\n");
	matrix_output(array,n,m);
	s_points(array,n,m);
}

static const char hex_const[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void hex(int x, char *res)
{
	int i=0;
	while (x>0)
	{
		res[7-i]=hex_const[x%16];
		x/=16;
		i++;
	}
	for (; i<8; i++)
	{
		res[7-i]='0';
	}
	res[8]=0;
}

void ex2()
{
	printf("Введите число, которое нужно представить в шестнадцетиричном виде\n");
	int x;
	scanf("%d",&x);
	char res[9];
	hex(x,res);
	printf("%s",res);
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
		case 'q': return;break;
		default : break;
	}
}

int main()
{
	printf("Написать программу, которая вводит с клавиатуры массив NxM вещественных чисел,\nещет седловые точки в массиве и выводит их и их позиции пользователю;\nзатем вводит с клавиатуры число, преобразовывает его в строку в шестнадцатеричном представлении и выводит результат пользователю.\n");
	char start='y';
	while (start=='y')
	{
		ex();
		printf("\nПерезапустить? (y/n)\n");
		scanf("\n%c",&start);
	}
	return 0;
}
