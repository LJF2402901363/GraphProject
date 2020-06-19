#pragma once
#include<string>

class Edge
{
public:
	Edge();
	Edge(int vexFrom,int vexTo,int weight);
	void setVexFrom(int vexFrom);
	void setVexTo(int vexTo);
	void setWeight(int weight);
	int getVetFrom() const;
	int getVexTo() const;
	int getWeight() const;
	~Edge();
private:
	//�����
	int vexFrom;
	//��������
	int vexTo;
	//�ߵ�Ȩֵ
	int weight;
};

