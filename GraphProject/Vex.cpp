#include "Vex.h"



Vex::Vex()
{
}

Vex::Vex(int num, const char * name, const char * desc)
{
	this->num = num;
	strcpy_s(this->name,name);
	strcpy_s(this->desc, desc);
}

void Vex::setNum(int num)
{
	this->num = num;
}

int Vex::getNum() const
{
	return this->num;
}

void Vex::setName(const char * name)
{
	strcpy_s(this->name, name);
}

char * Vex::getName()
{
	return this->name;
}

void Vex::setDesc(const char * desc)
{
	strcpy_s(this->desc, desc);
}

char * Vex::getDesc()
{
	return this->desc;
}


Vex::~Vex()
{
}
