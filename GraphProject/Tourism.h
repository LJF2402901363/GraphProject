#pragma once
#include"Graph.h"
#include<iostream>
using namespace std;

class Tourism
{
public:
	Tourism();
	void showGrapMenu();
	void createGrap();
	void findVex();
	void DFSTraverse(int nVex, PathList &pList);
	void findShortPath(int nVexStart,int nVexEnd);
	void desigPath(int start);
	~Tourism();
private :
	Graph g;
	//是否遍历过的数组
	int bVisited[MAX];
};

