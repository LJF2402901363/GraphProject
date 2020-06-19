#pragma once
class PathList
{
public:
	PathList();
	~PathList();
	//保存一条路径
	int vexs[20];
	//下一条路径
	PathList* next;

};

