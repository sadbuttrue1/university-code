#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

class CBaseFunc{
public:
	virtual void Print() =0;
	virtual CBaseFunc *Der() =0;
	virtual double Calc(double x) =0;
	~CBaseFunc(){}
};

class CDer:public CBaseFunc{
private:
	double k;
	double a;
public:
	void Print(){
		printf("%f*%f/sqrt(1-%f*x^2)",k,a,a*a);
	}
	double Calc(double x){
		return k*a/sqrt(1-a*a*x);
	}
	CBaseFunc *Der(){
		CBaseFunc *res=new CDer(k,a);
		return res;
	}
	CDer(const double &k,const double &a){
		this->k=k;
		this->a=a;
	}
	~CDer(){
		delete this;
	}
};

class CAsin: public CBaseFunc{
private:
	double k;
	double a;
public:
	CBaseFunc *Der(){
		CBaseFunc *res=new CDer(k,a);
		return res;
	}
	void Print(){
		printf("%f*arcsin(%f*x)",k,a);
	}
	double Calc(double x){
		return k*asin(a*x)*180/PI;
	}
	CAsin(const double &k, const double &a){
		this->k=k;
		this->a=a;
	}
	CAsin(const CAsin &copy){
		k=copy.k;
		a=copy.a;
	}
	~CAsin();
};

class CAcos:public CBaseFunc{
private:
	double k;
	double a;
public:
	CBaseFunc *Der(){
		CBaseFunc *res=new CDer(k,a);
		return res;
	}
	void Print(){
		printf("%f*arccos(%f*x)",k,a);
	}
	double Calc(double x){
		return k*acos(a*x)*180/PI;
	}
	CAcos(const double &k, const double &a){
		this->k=k;
		this->a=a;
	}
	CAcos(const CAcos &copy){
		k=copy.k;
		a=copy.a;
	}
	~CAcos();
};

void delete_CBaseFunc(CBaseFunc **p){
	if (*p) delete *p;
	*p=NULL;
}

void output_ex(){
	printf("тут у нас типа задание\n");
}

void main_menu(){
	CBaseFunc *ac=NULL,*as=NULL,*dac=NULL,*das=NULL;
	bool exit=false;
	while (!exit){
		printf("\nМеню программы (для выбора действия введите номер и нажмите Enter:\n");
		int i=0;
		printf("%d) Вывести задание.\n",i);
		if (!ac){
			i++;
			printf("%d) Задать коэффициенты для выражения вида k*arccos(a*x).\n",i);
		}
		else{
			i++;printf("%d) Вывести выражение вида k*arccos(a*x).\n",i);
			i++;printf("%d) Изменить коэффициенты в выражении k*arccos(a*x).\n",i);
			i++;printf("%d) Посчитать k*arccos(a*x) для заданного X.\n",i);
			if (!dac){
				i++;
				printf("%d) Определить производную для k*arccos(a*x).\n",i);
			}
			else{
				i++;printf("%d) Вывести производную от k*arccos(a*x).\n",i);
				i++;printf("%d) Вычислить производную от k*arccos(a*x) для заданного X.\n",i);
			}
		}
		i++;printf("%d) Выйти из программы.\n",i);
		scanf("%d",&i);
		system("clear");
		if (!ac){
			switch (i){
				case 0:output_ex();break;
				case 1:{
					double k,a;
					printf("Введите через пробел k и a.\n");
					scanf("%lf %lf",&k,&a);
					ac=new CAcos(k,a);
				};break;
				case 2:exit=true;break;
			}
		}
		else{
			
		}
	}
	delete_CBaseFunc(&ac);
	delete_CBaseFunc(&as);
	delete_CBaseFunc(&dac);
	delete_CBaseFunc(&das);
}

int main(){
	output_ex();
	main_menu();
	/*CBaseFunc *p=NULL;
	p=new CAcos(1,1);
	p->Print();
	CBaseFunc *c=p->Der();
	c->Print();
	delete_CBaseFunc(&p);*/
	return 0;
}
