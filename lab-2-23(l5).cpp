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
	bool operator == (const CDer &src){
		if ((this) && (&src)){
			if ((k==(&src)->k) && (a==(&src)->a) && (type==(&src)->type)) return true;
			else return false;
		}
	}
	bool operator != (const CDer &src){
		return !( this == (&src));
	}
	CDer& operator = (const CDer &src){
		if (!(this == (&src))){
			k=(&src)->k;
			a=(&src)->a;
			type=(&src)->type;
		}
		return *this;
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
	bool operator == (const CAsin &src){
		if ((this) && (&src)){
			if ((k==(&src)->k) && (a==(&src)->a)) return true;
			else return false;
		}
	}
	bool operator != (const CAsin &src){
		return !( this == (&src));
	}
	CAsin& operator = (const CAsin &src){
		if (!(this == (&src))){
			k=(&src)->k;
			a=(&src)->a;
		}
		return *this;
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
	bool operator == (const CAcos &src){
		if ((this) && (&src)){
			if ((k==(&src)->k) && (a==(&src)->a)) return true;
			else return false;
		}
	}
	bool operator != (const CAcos &src){
		return !( this == (&src));
	}
	CAcos& operator = (const CAcos &src){
		if (!(this == (&src))){
			k=(&src)->k;
			a=(&src)->a;
		}
		return *this;
	}
};

class Exeption{
private:
	int type;
	double count;
public:
	Exeption(const int type, const double count=0){
		this->type=type;
		this->count=count;
	}
	void Print(){
		switch(type){
			case 0:{
				printf("Введенный индекс %lf приводит к выходу за границы коллекции.\n",count);
			};break;
			case 1:{
				printf("Не создана коллекция.\n");
			};break;
			case 2:{
				printf("Для функции не определена производная.\n");
			};break;
			case 3:{
				printf("Не определена функция.\n");
			};break;
			case 4:{
				printf("Не существует значения функции для %lf.\n",count);
			};break;
		}
	}
};

template <class T>
class CFuncs{
private:
	T** c_funcs;
	int count;
public:
	class iterator{
		private:
			int current;
			CFuncs *collection;
		public:
			iterator* operator ++(int n){
				current++;
				return this;
			}
			iterator* operator +=(int n){
				if ((current+n<0) || (current+n>=collection->count)){ Exeption err(0,n); throw(err);}//exeption
				else current+=n;
				return this;
			}
			bool end(){
				if (current==collection->count) return true;
				else return false;
			}
			int number(){
				return current;
			}
			T*& element(){
				return collection->c_funcs[current];
			}
			friend class CFuncs;
		};
	iterator begin(){
		iterator i;
		i.current=0;
		i.collection=this;
		return i;
	}
	CFuncs(const int func_cnt=0){
		count = func_cnt;
		c_funcs = new T*[count];
		for (iterator i=this->begin(); !(i.end()); i++)
			i.element()=NULL;
	}
	~CFuncs(){
		for (int i=0; i<count; i++)
			if (c_funcs[i] != NULL) delete c_funcs[i];
		delete [] c_funcs;
	}
	CFuncs* truncation(int n){
		if ((n<0) || (n>=count)) { Exeption err(0,n); throw(err); return this;}//exeption
		else{
			CFuncs *new_f = new CFuncs(n+1);
			for (iterator it1=new_f->begin(), it2=this->begin(); !(it1.end()); it1++, it2++){
				it1.element()=it2.element();
				it2.element()=NULL;
			}
			delete(this);
			return new_f;
		}
	}
	CFuncs* insertion(int n){
		if ((n<0) || (n>=count+1)) { Exeption err(0,n); throw(err); return this;}//exeption
		else{
			CFuncs *new_f = new CFuncs(count+1);
			for (iterator it1=new_f->begin(), it2=this->begin(); !(it1.end()); it1++){
				if (it1.number()==n+1){
					it1.element()=NULL;
				}
				else{
					it1.element()=it2.element();
					it2.element()=NULL;
					it2++;
				}
			}
			delete(this);
			return new_f;
		}
	}
	CFuncs* deletion(int n){
		if ((n<0) || (n>=count)) { Exeption err(0,n); throw(err); return this;}//exeption
		else{
			CFuncs *new_f = new CFuncs(count-1);
			for (iterator it1=new_f->begin(), it2=this->begin(); !(it1.end());it1++){
				if (it2.number()==n) it2++;
				it1.element()=it2.element();
				it2.element()=NULL;
				it2++;
			}
			delete(this);
			return new_f;
		}
	}
	/*T* operator[] (const CFuncs::iterator n) const{
		CFuncs::iterator res=n;
		return res.element();
	}*/
	/*T*& operator[] (iterator n){
		//CFuncs::iterator res=n;
		return n.element();
	}*/
//	T*& operator [] (iterator n);
};

void output_ex(){
	printf("Написать программу, в которой описана иерархия классов: функция от одной переменной (арксинус,  арккосинус,  а также класс, необходимый для представления производных). Описать шаблонный класс  для хранения массива указателей на объекты произвольного класса, в котором перегрузить операцию  []. Описать класс-итератор для итерации по элементам коллекции.\n");
}

void main_menu(){
	bool exit=false;
	
	while (!exit){
		try{
			
		}
		catch (Exeption &e){
			e.Print();
		}
	}
}

int main(){
	output_ex();
	main_menu();
	return 0;
}

