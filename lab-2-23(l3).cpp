#include <stdio.h>
#include <math.h>

#define PI 3.14159265

class CBaseFunc{
public:
	virtual void Print() =0;
	virtual void Read() =0;
};

class CAsin: public CBaseFunc{
private:
	float carg;
public:
	void Print();
	void Read();
	CAsin(const float &arg);
};

CAsin::CAsin(const float &arg){
	carg=arg;
}

void CAsin::Print(){
	printf("Значение arcsin(%f)=%f",carg,asin(carg)*180/PI);
}

void CAsin::Read(){}

void delete_CBaseFunc(CBaseFunc **p){
	if (*p!=NULL) delete *p;
	*p=NULL;
}

class CAcos: public CBaseFunc{
private:
	float carg;
public:
	void Print();
	void Read();
	CAcos(const float &arg);
};

CAcos::CAcos(const float &arg){
	carg=arg;
}

void CAcos::Print(){
	printf("Значение arcsin(%f)=%f",carg,acos(carg)*180/PI);
}

void CAcos::Read(){}

int main(){
	float x;
	scanf("%f",&x);
	CBaseFunc *c=NULL;
	c=new CAsin(x);
	c->Print();
	delete_CBaseFunc(&c);
	c=new CAcos(x);
	c->Print();	
	delete_CBaseFunc(&c);
	return 0;
}
