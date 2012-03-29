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
	float Count(){
		return asin(carg)*180/PI;
	}
public:
	void Print(){
	printf("Значение arcsin(%f)=%f",carg,Count());
}
	void Read(){
		scanf("%f",&carg);
	}
	CAsin (){}
	CAsin(const float &arg){
		carg=arg;
	}
};

class CAcos: public CBaseFunc{
private:
	float carg;
	float Count(){
		return acos(carg)*180/PI;
	}
public:
	void Print(){
		printf("Значение arccos(%f)=%f",carg,Count());
	}
	void Read(){
		scanf("%f",&carg);
	}
	CAcos(){}
	CAcos(const float &arg){
		carg=arg;
	}
};

class CDer: public CBaseFunc{
private:
	bool ctype;
	float carg;
	float csum;
	float Count(){
		return csum/sqrt(1-carg*carg);
	}
public:
	void Print(){
		if (ctype) printf("Значение (arcsin(%f))'=%f/sqrt(1-%f^2)=%f",carg,csum,carg,Count());
		else printf("Значение (arccos(%f))'=%f/sqrt(1-%f^2)=%f",carg,csum,carg,Count());
	}
	void Read(){
		scanf("%f",&carg);
	}
	CDer(){}
	CDer(const bool &type){
		if (type) csum=1;
		else csum=-1;
	}//передаем true, если производная от arcsin, и false, если производная от arccos.
	CDer(const bool &type, const float &arg){
		if (type) csum=1;
		else csum=-1;
		carg=arg;
	}
};

void delete_CBaseFunc(CBaseFunc **p){
	if (*p!=NULL) delete *p;
	*p=NULL;
}

int main(){
	/*CAcos c;
	c.Read();
	c.Print();*/
	CBaseFunc *c=NULL;
	c=new CAsin();
	c->Read();
	c->Print();
	delete_CBaseFunc(&c);
	c=new CAcos();
	printf("\n");
	c->Read();
	c->Print();	
	delete_CBaseFunc(&c);
	c=new CDer(true);
	printf("\n");
	c->Read();
	c->Print();
	delete_CBaseFunc(&c);
	c=new CDer(false);
	printf("\n");
	c->Read();
	c->Print();
	delete_CBaseFunc(&c);
	return 0;
}
