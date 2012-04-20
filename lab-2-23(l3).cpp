#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class CBaseFunc{
public:
	virtual void Print() =0;
	virtual CBaseFunc *Der() =0;
	virtual double Calc(double x) =0;
	virtual bool have_Der() =0;
	virtual bool correct_variable(double x) =0;
	virtual void variable_range() =0;
	virtual ~CBaseFunc(){}
};

class CDer:public CBaseFunc{
private:
	double k;
	double a;
	char type;
public:
	void Print(){
		if (type=='c') printf("-");
		printf("%lf/sqrt(1-%lf*x^2)",k*a,a*a);
	}
	double Calc(double x){
		int s=1;
		if (type=='c') s=-1;
		return s*k*a/sqrt(1-a*a*x);
	}
	CBaseFunc *Der(){
		return NULL;
	}
	CDer(const double &k,const double &a, const char &type){
		this->k=k;
		this->a=a;
		this->type=type;
	}
	bool have_Der(){
		return false;
	}
	CDer(const CDer &copy){
		k=copy.k;
		a=copy.a;
		type=copy.type;
	}
	bool correct_variable(double x){
		if ((a*a*x*x>-1) && (a*a*x*x<1)) return true;
		else return false;
	}
	void variable_range(){
		printf("|%lf * x^2|<1",a*a);
	}
};

class CAsin: public CBaseFunc{
private:
	double k;
	double a;
public:
	CBaseFunc *Der(){
		CBaseFunc *res=new CDer(k,a,'s');
		return res;
	}
	void Print(){
		printf("%lf*arcsin(%lf*x)",k,a);
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
	bool have_Der(){
		return true;
	}
	bool correct_variable(double x){
		if ((a*x>=-1) && (a*x<=1)) return true;
		else return false;
	}
	void variable_range(){
		printf("|%lf * x|<=1",a);
	}
};

class CAcos:public CBaseFunc{
private:
	double k;
	double a;
public:
	CBaseFunc *Der(){
		CBaseFunc *res=new CDer(k,a,'c');
		return res;
	}
	void Print(){
		printf("%lf*arccos(%lf*x)",k,a);
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
	bool have_Der(){
		return true;
	}
	bool correct_variable(double x){
		if ((a*x>-1) && (a*x<1)) return true;
		else return false;
	}
	void variable_range(){
		printf("|%lf * x|<=1",a);
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
	bool exit=false;
	int i=0;
	while (!exit){
		i=0;
		printf("\nМеню программы (для выбора действия введите номер и нажмите Return:\n");
		printf("%d) Вывести задание.\n",i);
		i++;
		printf("%d) Выбрать функцию.\n",i);
		i++;
		printf("%d) Вывести текущую функцию.\n",i);
		i++;
		printf("%d) Вычислить текущую функцию для заданного X.\n",i);
		i++;
		printf("%d) Выйти из программы.\n",i);
		scanf("%d",&i);
		system("clear");
		switch (i){
			case 0: output_ex();break;
			case 1: {
				printf("Введите номер функции и нажмите Return.\n");
				int n=0;
				printf("%d) k*arcsin(a*x).\n",n);
				n++;
				printf("%d) k*arccos(a*x).\n",n);
				n++;
				printf("%d) производная текущей функции.\n",n);
				scanf("%d",&n);
				switch (n){
					case 0:{
						if (foo) delete_CBaseFunc(&foo);
						printf("Введите коэффициенты k и a через пробел.\n");
						double k,a;
						scanf("%lf %lf",&k,&a);
						foo=new CAsin(k,a);
					};break;
					case 1:{
						if (foo) delete_CBaseFunc(&foo);
						printf("Введите коэффициенты k и a через пробел.\n");
						double k,a;
						scanf("%lf %lf",&k,&a);
						foo=new CAcos(k,a);
					};break;
					case 2:{
						if (foo){
							if (foo->have_Der()){
								CBaseFunc *der;
								der=foo->Der();
								delete_CBaseFunc(&foo);
								foo=der;
								der=NULL;
							}
							else printf("Для функции не определена производная.\n");
						}
						else printf("Не выбрана функция.\n");
					};break;
				}
			};break;
			case 2:{
				if (foo){
					foo->Print();
					printf("\n");
				}
				else printf("Не выбрана функция.\n");
			};break;
			case 3:{
				if (foo){
					printf("Введите X.\n");
					double x;
					scanf("%lf",&x);
					while(!foo->correct_variable(x)){
						foo->variable_range();
						printf("\nВведите корректное значение.\n");
						scanf("%lf",&x);
					}
					foo->Print();
					printf("=%lf\n",foo->Calc(x));
				}
				else printf("Не выбрана функция.\n");
			};break;
			case 4: exit=true;break;
		}
	}
	delete_CBaseFunc(&foo);
}

int main(){
	output_ex();
	main_menu();
	return 0;
}
