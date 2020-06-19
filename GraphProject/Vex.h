#pragma once
#define NAME_SIZE 20
#define DESC_SIZE 1024
#include<string>
class Vex
{
public:
	Vex();
	Vex(int num,const char * name,const char * desc);
	void setNum(int num);
	int getNum() const;
	void setName(const char* name);
	char* getName();
	void setDesc(const char *desc);
	char* getDesc();
	~Vex();
private:
	//���������
	char name[20];
	//�������
	char desc[1024];
	//������
	int num;
};

