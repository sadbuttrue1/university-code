#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

class CBaseFunc{
public:
	virtual void Print() =0;
	virtual CBaseFunc *Der() =0;
	virtual double Calc(double x) =0;
	virtual double Count_a() =0;
	virtual double Count_k() =0;
	~CBaseFunc(){}
};

class CDer:public CBaseFunc{
private:
	double k;
	double a;
public:
	double Count_k(){
		return k;
	}
	double Count_a(){
		return a;
	}
	void Print(){
		printf("%f*%f/sqrt(1-%f*x^2)\n",k,a,a*a);
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
	double Count_k(){
		return k;
	}
	double Count_a(){
		return a;
	}
	void Print(){
		printf("%f*arcsin(%f*x)\n",k,a);
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
	double Count_k(){
		return k;
	}
	double Count_a(){
		return a;
	}
	void Print(){
		printf("%f*arccos(%f*x)\n",k,a);
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
		if (!as){
			i++;
			printf("%d) Задать коэффициенты для выражения вида k*arcsin(a*x).\n",i);
		}
		else{
			i++;printf("%d) Вывести выражение вида k*arcsin(a*x).\n",i);
			i++;printf("%d) Изменить коэффициенты в выражении k*arcsin(a*x).\n",i);
			i++;printf("%d) Посчитать k*arcsin(a*x) для заданного X.\n",i);
			if (!das){
				i++;
				printf("%d) Определить производную для k*arcsin(a*x).\n",i);
			}
			else{
				i++;printf("%d) Вывести производную от k*arcsin(a*x).\n",i);
				i++;printf("%d) Вычислить производную от k*arcsin(a*x) для заданного X.\n",i);
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
			}
		}
		else{
			switch (i){
				case 0:output_ex();break;
				case 1:ac->Print();break;
				case 2:{
					double k,a;
					ac->Print();
					printf("Введите через пробел k и a.\n");
					scanf("%lf %lf",&k,&a);
					delete_CBaseFunc(&ac);
					ac=new CAcos(k,a);
				};break;
				case 3:{
					double x;
					printf("Введите X (|%lf * x| <=1).\n",ac->Count_a());
					scanf("%lf",&x);
					while ((ac->Count_a()*x>1) || (ac->Count_a()*x<-1)){
						printf("(|%lf * x| <=1) Введите верное значение.\n",ac->Count_a());
						scanf("%lf",&x);
					}
					printf("Выражение ");
					ac->Print();
					printf("\n равно %lf для %lf",ac->Calc(x),x);
				};break;
				case 4:{
					if (!dac) dac=ac->Der();
					else dac->Print();
				};break;
				if (dac){
					case 5:{
						double x;
						printf("Введите X (|%lf * x^2| <1).\n",dac->Count_a()*dac->Count_a());
						scanf("%lf",&x);
						while ((dac->Count_a()*dac->Count_a()*x*x>=1) || (dac->Count_a()*dac->Count_a()*x*x<=-1)){
							printf("(|%lf * x| <1) Введите верное значение.\n",dac->Count_a());
							scanf("%lf",&x);
						}
						printf("Выражение ");
						dac->Print();
						printf("\n равно %lf для %lf",dac->Calc(x),x);
					};break;
				}
			}
		}
		int m=0;
		if (!ac) m=1;
		else if (!dac) m=4;
		else m=5;
		i-=m;
		if (!as){
			switch (i){
				case 1:{
					double k,a;
					printf("Введите через пробел k и a.\n");
					scanf("%lf %lf",&k,&a);
					as=new CAsin(k,a);
				};break;
			}
		}
		else{
			switch (i){
				case 1:as->Print();break;
				case 2:{
					double k,a;
					as->Print();
					printf("Введите через пробел k и a.\n");
					scanf("%lf %lf",&k,&a);
					delete_CBaseFunc(&as);
					as=new CAsin(k,a);
				};break;
				case 3:{
					double x;
					printf("Введите X (|%lf * x| <=1).\n",as->Count_a());
					scanf("%lf",&x);
					while ((as->Count_a()*x>1) || (as->Count_a()*x<-1)){
						printf("(|%lf * x| <=1) Введите верное значение.\n",as->Count_a());
						scanf("%lf",&x);
					}
					printf("Выражение ");
					as->Print();
					printf("равно %lf для %lf",as->Calc(x),x);
				};break;
				case 4:{
					if (!das) das=as->Der();
					else das->Print();
				};break;
				if (das){
					case 5:{
						double x;
						printf("Введите X (|%lf * x^2| <1).\n",das->Count_a()*das->Count_a());
						scanf("%lf",&x);
						while ((das->Count_a()*das->Count_a()*x*x>=1) || (das->Count_a()*das->Count_a()*x*x<=-1)){
							printf("(|%lf * x| <1) Введите верное значение.\n",das->Count_a());
							scanf("%lf",&x);
						}
						printf("Выражение ");
						das->Print();
						printf("равно %lf для %lf",das->Calc(x),x);
					};break;
				}
			}
		}
		if (!as) m=1;
		else if (!das) m=4;
		else m=5;
		if (i==m+1) exit=true;
	}
	delete_CBaseFunc(&ac);
	delete_CBaseFunc(&as);
	delete_CBaseFunc(&dac);
	delete_CBaseFunc(&das);
}

int main(){
	output_ex();
	main_menu();
	return 0;
}
