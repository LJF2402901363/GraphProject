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
	//起点编号
	int vexFrom;
	//结束点编号
	int vexTo;
	//边的权值
	int weight;
};

