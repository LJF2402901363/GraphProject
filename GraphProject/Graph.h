#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"Edge.h"
#include"Vex.h"
#include<strstream>
#include"PathList.h"
#include<stack>
#define MAX 20
#define INF  100000

using namespace std;
class Graph
{
public:
	Graph();
	//读取边文件数据
	void initEdgeData(const char* dataFilePath);
	//读取点文件数据
	void initVexData(const char* dataFilePath);
	//创建图
	void createGraph();
	//插入顶点
	void insertVex(const Vex *vex);
	//插入边
	void insertEdge(const Edge& edge);
	//查询指定顶点信息
	Vex* GetVex(int nVex);
	//查询与指定顶点相连的边。
	int FindEdge(int nVex, Edge *edge);
	//获取当前顶点数
	int getVexSize();
	int getEdgeSize();
	/*展示所有边的信息*/
	void showEdges();
	/*展示所有节点的信息*/
	void showVexs();
	/*深度遍历*/
	void DNF(int nVex, int bVisted[], int nIndex, PathList &pList);
	/*查找两点间最短路径*/
	int findShortPath(int nVexStart,int nVexEnd);
	/*打印路径*/
	void print(int sec, int nVexend, int path[], int d[]);
	/*展示所有节点对应 的编号*/
	void showAllVexInfo();
	void findMinTree(Edge edges[], int start);
	~Graph();
private:
	/*判定当前节点是否已经存在*/
	bool isVexExist(int vexNum);
	/*判定边是否存在*/
	bool isEdgeExist(const Edge &edge);
private:
	//邻接矩阵
	int adjMatrix[MAX][MAX];
	//顶点编号数组
	int aVex[MAX];
	/*定点数组*/
	Vex vexs[MAX];
	//边的数组
	Edge edges[ MAX * 2];
	//顶点个数
	int vexSize;
	//当前顶点个数
	int indexVex;
	//边的个数
	int edgeSize;
	
};

