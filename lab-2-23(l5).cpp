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
	bool exist=false;
public:
class iterator{
	private:
		int current,count;
		T** c_funcs;
	public:
		iterator* operator ++(int n){
			current++;
			return this;
		}
		iterator* operator +=(int n){
			if ((current+n<0) || (current+n>=count)){ Exeption err(0,n); throw(err);}//exeption
			else current+=n;
			return this;
		}
		bool end(){
			if (current==count) return true;
			else return false;
		}
		int number(){
			return current;
		}
		T*& element(){
			return c_funcs[current];
		}
		friend class CFuncs;
	};
	iterator begin(){
		iterator i;
		i.current=0;
		i.c_funcs=this->c_funcs;
		i.count=this->count;
		return i;
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
	/*CFuncs* insertion(int n){
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
	}*/
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
	CFuncs(const int func_cnt=0){
		count = func_cnt;
		if (count>0) exist = true;
		c_funcs = new CBaseFunc*[count];
		for (iterator i=this->begin(); !(i.end()); i++)
			i.element()=NULL;
	}
	~CFuncs(){
		for (int i=0; i<count; i++)
			if (c_funcs[i] != NULL) delete c_funcs[i];
		delete [] c_funcs;
	}
	
	void set_size(int size){
		count=size;
		c_funcs= new T*[count];
		exist=true;
	}
	void delete_arr(){
		for (int i=0; i<count; i++)
			if (c_funcs[i] != NULL) delete c_funcs[i];
		delete [] c_funcs;
		count=0;
		exist=false;
	}
	bool isitexist(){
		if (exist) return true;
		else return false;
	}
	CFuncs <T> insertion(int n){
		if ((n<0) || (n>=count+1)) { Exeption err(0,n); throw(err);}//exeption
		else{
			CFuncs <T> new_f(this->count+1);
			for (int i=0,j=0; i<new_f.count; i++){
				if (i == n+1) new_f.c_funcs[i]=NULL;
				else{
					new_f.c_funcs[i]=this->c_funcs[j];
					this->c_funcs[j]=NULL;
					j++;
				}
				delete(this);
				return new_f;
			}
		}
	}
	CBaseFunc*& operator [] (iterator n){
		return n.element();
	}
};

void delete_CBaseFunc(CBaseFunc **p){
	if (*p) delete *p;
	*p=NULL;
}

void output_ex(){
	printf("Написать программу, в которой описана иерархия классов: функция от одной переменной (арксинус,  арккосинус,  а также класс, необходимый для представления производных). Описать шаблонный класс  для хранения массива указателей на объекты произвольного класса, в котором перегрузить операцию  []. Описать класс-итератор для итерации по элементам коллекции.\n");
}

void main_menu(){
	bool exit=false;
	CFuncs <CBaseFunc> x;
	while (!exit){
		try{
			int i=0;
			printf("%d) Вывести задание.\n",i);
			i++;
			printf("%d) Создать пустую коллекцию.\n",i);
			i++;
			printf("%d) Перейти к работе с элементами коллекции.\n",i);
			i++;
			printf("%d) Выйти из программы.\n",i);
			scanf("%d",&i);
			system("clear");
			switch (i){
				case 0: output_ex();break;
				case 1:{
					if (x.isitexist()){
						printf("Хотите уничтожить существующую коллекцию и создать новую? (y/n):");
						char c;
						scanf("\n%c",&c);
						if (c=='n') break;
						else x.delete_arr();
					}
					printf("Введите размер коллекции:");
					int n;
					scanf("%d",&n);
					x.set_size(n);
				};break;
				case 2:{
					if (!x.isitexist()){
						Exeption err(1);
						throw(err);
						}//exeption about no collection
					else{
						int k=0;
						printf("%d) Вывести существующие элементы коллекции.\n",k);
						k++;
						printf("%d) Задать элемент с номером.\n",k);
						k++;
						printf("%d) Удалить элементы после выбранного.\n",k);
						k++;
						printf("%d) Вставить пустой элемент на заданное место.\n",k);
						k++;
						printf("%d) Вставить пустой элемент в конец.\n",k);
						k++;
						printf("%d) Удалить элемент коллекции.\n",k);
						k++;
						printf("%d) Вычислить элемент коллекции для заданного значения переменной.\n",k);
						scanf("%d",&k);
						system("clear");
						switch(k){
							case 0:{
								for (CFuncs<CBaseFunc>::iterator it=x.begin(); !(it.end()); it++)
									if (x[it]){
										printf("%d)",it.number());
										x[it]->Print();
										printf("\n");
									}
							};break;
							case 1:{
								printf("Введите номер элемента коллекции, которых хотите задать или переопределить:");
								int n;
								scanf("%d",&n);
								CFuncs <CBaseFunc>::iterator it=x.begin();
								it+=n;
								system("clear");
								printf("Введите номер функции и нажмите Return.\n");
								n=0;
								printf("%d) k*arcsin(a*x).\n",n);
								n++;
								printf("%d) k*arccos(a*x).\n",n);
								n++;
								printf("%d) Производная текущей функции.\n",n);
								scanf("%d",&n);
								switch (n){
									case 0:{
										if (x[it]) delete_CBaseFunc(&x[it]);
										printf("Введите коэффициенты k и a через пробел.\n");
										double k,a;
										scanf("%lf %lf",&k,&a);
										x[it]=new CAsin(k,a);
									};break;
									case 1:{
										if (x[it]) delete_CBaseFunc(&x[it]);
										printf("Введите коэффициенты k и a через пробел.\n");
										double k,a;
										scanf("%lf %lf",&k,&a);
										x[it]=new CAcos(k,a);
									};break;
									case 2:{
										if (x[it]){
											if (x[it]->have_Der()){
												CBaseFunc *der;
												der=x[it]->Der();
												delete_CBaseFunc(&x[it]);
												x[it]=der;
												der=NULL;
											}
											else{
												Exeption err(2);
												throw(err);
												}//exeption no der
										}
										else{
											Exeption err(3);
											throw(err);
											}//exeption no func
									};break;
								}
							};break;
							case 2:break;
							case 3:{
								printf("Введите номер элемента, после которого нужно вставить пустой элемент:");
								int n;
								scanf("%d",&n);
								x=x.insertion(n);
							}
						}
					}
				};break;
				case 3: exit=true;break;
			}
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

