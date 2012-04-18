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
	virtual bool have_Der() =0;
	virtual bool correct_variable(double x) =0;
	virtual ~CBaseFunc(){}
};

class CDer:public CBaseFunc{
private:
	double k;
	double a;
public:
	void Print(){
		printf("%f*%f/sqrt(1-%f*x^2)\n",k,a,a*a);
	}
	double Calc(double x){
		return k*a/sqrt(1-a*a*x);
	}
	CBaseFunc *Der(){
		return NULL;
	}
	CDer(const double &k,const double &a){
		this->k=k;
		this->a=a;
	}
	double Count_k(){
		return k;
	}
	double Count_a(){
		return a;
	}
	bool have_Der(){
		return false;
	}
	CDer(const CDer &copy){
		k=copy.k;
		a=copy.a;
	}
	bool correct_variable(double x){
		if ((a*a*x*x>-1) && (a*a*x*x<1)) return true;
		else return false;
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
		printf("%f*arcsin(%f*x)\n",k,a);
	}
	double Calc(double x){
		return k*asin(a*x);
	}
	CAsin(const double &k, const double &a){
		this->k=k;
		this->a=a;
	}
	CAsin(const CAsin &copy){
		k=copy.k;
		a=copy.a;
	}
	double Count_k(){
		return k;
	}
	double Count_a(){
		return a;
	}
	bool have_Der(){
		return true;
	}
	bool correct_variable(double x){
		if ((a*x>-1) && (a*x<1)) return true;
		else return false;
	}
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
		printf("%f*arccos(%f*x)\n",k,a);
	}
	double Calc(double x){
		return k*acos(a*x);
	}
	CAcos(const double &k, const double &a){
		this->k=k;
		this->a=a;
	}
	CAcos(const CAcos &copy){
		k=copy.k;
		a=copy.a;
	}
	double Count_k(){
		return k;
	}
	double Count_a(){
		return a;
	}
	bool have_Der(){
		return true;
	}
	bool correct_variable(double x){
		if ((a*x>-1) && (a*x<1)) return true;
		else return false;
	}
};

void delete_CBaseFunc(CBaseFunc **p){
	if (*p) delete *p;
	*p=NULL;
}

void output_ex(){
	printf("Написать программу, в которой описана иерархия классов: функция от одной переменной (арксинус, арккосинус, а также класс, необходимый для представления производных). Базовый класс должен иметь методы получения значения функции для данного значения переменной, а также создания экземпляра класса, представляющего собой производную текущего экземпляра. Продемонстрировать работу всех методов классов всех классов.\n");
}

void main_menu(){
	CBaseFunc *foo=NULL;
	bool ex=false;
	bool ex_der,sin;
	int i=0;
	while (!ex){
		i=0;
		printf("\nМеню программы (для выбора действия введите номер и нажмите Enter:\n");
		printf("%d) Вывести задание.\n",i);
		if (!foo){
			i++;
			printf("%d) Выбрать функцию.\n",i);
		}
		else{
			i++;
			printf("%d) Переопределить функцию.\n",i);
			i++;
			printf("%d) Вывести текущую функцию.\n",i);
			i++;
			printf("%d) Посчитать текущую функцию для заданного X.\n",i);
		}
		i++;
		printf("%d) Выйти из программы.\n",i);
		scanf("%d",&i);
		system("clear");
		switch (i){
			case 0: output_ex();break;
			case 1:{
				printf("Введите номер функции.\n");
				int n=0;
				printf("%d) k*arcsin(a*x).\n",n);
				n++;
				printf("%d) k*arccos(a*x).\n",n);
				if ((foo) && (foo->have_Der())){
					n++;
					printf("%d) производная текущей функции.\n",n);
				}
				scanf("%d",&n);
				switch (n){
					case 0:{
						if (foo) delete_CBaseFunc(&foo);
							printf("Введите коэффициенты k и a через пробел.\n");
							double a,k;
							scanf("%lf %lf",&k,&a);
							foo=new CAsin(k,a);
							ex_der=false;
							sin=true;
						};break;
					case 1:{
						if (foo) delete_CBaseFunc(&foo);
							printf("Введите коэффициенты k и a через пробел.\n");
							double a,k;
							scanf("%lf %lf",&k,&a);
							foo=new CAcos(k,a);
							ex_der=false;
							sin=false;
						};break;
					if ((foo) && (foo->have_Der())){
						case 2:{
							CBaseFunc *der;
							der=foo->Der();
							delete_CBaseFunc(&foo);
							foo=der;
							der=NULL;
							ex_der=true;
						};break;
					}
				}
			};break;
			case 2:{
				if (foo){
					if ((ex_der) && (!sin)) printf("-");
					foo->Print();
				}
				else ex=true;
				};break;
			case 3:if (foo){
				if (!ex_der){
					double x;
					printf("Введите X (|%lf * x| <=1).\n",foo->Count_a());
					scanf("%lf",&x);
					while ((foo->Count_a()*x>1) || (foo->Count_a()*x<-1)){
						printf("(|%lf * x| <=1) Введите верное значение.\n",foo->Count_a());
						scanf("%lf",&x);
					}
					printf("Выражение ");
					foo->Print();
					printf("\n равно %lf для %lf",foo->Calc(x)*180/PI,x);
				}
				else{
					double x;
					printf("Введите X (|%lf * x^2| <1).\n",foo->Count_a()*foo->Count_a());
					scanf("%lf",&x);
					while ((foo->Count_a()*foo->Count_a()*x*x>=1) || (foo->Count_a()*foo->Count_a()*x*x<=-1)){
						printf("(|%lf * x| <1) Введите верное значение.\n",foo->Count_a());
						scanf("%lf",&x);
					}
					printf("Выражение ");
					int s=1;
					if (!sin){
						printf("-");
						s=-1;
					}
					foo->Print();
					printf("\n равно %lf для %lf",s*foo->Calc(x),x);
				}
			};break;
			case 4:if (foo) ex=true;break;
		}
	}
	delete_CBaseFunc(&foo);
}

int main(){
	output_ex();
	main_menu();
	return 0;
}
