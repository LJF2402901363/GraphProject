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
	//��ȡ���ļ�����
	void initEdgeData(const char* dataFilePath);
	//��ȡ���ļ�����
	void initVexData(const char* dataFilePath);
	//����ͼ
	void createGraph();
	//���붥��
	void insertVex(const Vex *vex);
	//�����
	void insertEdge(const Edge& edge);
	//��ѯָ��������Ϣ
	Vex* GetVex(int nVex);
	//��ѯ��ָ�����������ıߡ�
	int FindEdge(int nVex, Edge *edge);
	//��ȡ��ǰ������
	int getVexSize();
	int getEdgeSize();
	/*չʾ���бߵ���Ϣ*/
	void showEdges();
	/*չʾ���нڵ����Ϣ*/
	void showVexs();
	/*��ȱ���*/
	void DNF(int nVex, int bVisted[], int nIndex, PathList &pList);
	/*������������·��*/
	int findShortPath(int nVexStart,int nVexEnd);
	/*��ӡ·��*/
	void print(int sec, int nVexend, int path[], int d[]);
	/*չʾ���нڵ��Ӧ �ı��*/
	void showAllVexInfo();
	void findMinTree(Edge edges[], int start);
	~Graph();
private:
	/*�ж���ǰ�ڵ��Ƿ��Ѿ�����*/
	bool isVexExist(int vexNum);
	/*�ж����Ƿ����*/
	bool isEdgeExist(const Edge &edge);
private:
	//�ڽӾ���
	int adjMatrix[MAX][MAX];
	//����������
	int aVex[MAX];
	/*��������*/
	Vex vexs[MAX];
	//�ߵ�����
	Edge edges[ MAX * 2];
	//�������
	int vexSize;
	//��ǰ�������
	int indexVex;
	//�ߵĸ���
	int edgeSize;
	
};

