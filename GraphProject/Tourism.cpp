#include "Tourism.h"



Tourism::Tourism()
{
	
	showGrapMenu();
	

}

void Tourism::showGrapMenu()
{
	PathList p;
	PathList* temp = nullptr;
	int nVex = 0;
	int i = -1;
	int count = 0;
	int start = -1;
	int end = -1;
	cout << "=======景区信息管理系统============" << endl;
	while (i != 0)
	{
		cout << "1.创建景区节点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << "请输入操作编号：";
		cin >> i;
		switch (i)
		{
		case 1:
			createGrap();
			break;
		case 2:
			findVex();
			break;
		case 3:
			this->g.showAllVexInfo();
			cout << "请输入起始景点编号：";
			cin >> nVex;
			DFSTraverse(nVex, p);
			temp = p.next;
			while (temp!=nullptr)
			{
			
				int index = 0;
				count++;
				cout << "线路" << count << ":";
				for (int  i = 0; i < this->g.getVexSize(); i++)
				{
					if (temp->vexs[i] >= 0)
					{
						index++;
						Vex* vex=	g.GetVex(temp->vexs[i]);
					if (index == this->g.getVexSize())
					{
						cout << vex->getName() << endl;
					}
					else {
						cout << vex->getName() << "-->";
					}
					}
				}
				temp = temp->next;
				
			}
			count = 0;
			p.next = nullptr;
			break;
		case 4:
			this->g.showAllVexInfo();
			cout << "请输入起始点:";
			cin >> start;
			cout << "请输入结束点点:";
			cin >> end;
			cout << endl;
			this->findShortPath(start,end);
			break;
		case 5:
			cout << "请输入起始开始建设的点编号：";
			cin >> start;
			this->desigPath(start);
			break;
		default:
			break;
		}
	}
}

void Tourism::createGrap()
{
	char vixFileNmae[20] = "vex.txt";
	g.initVexData(vixFileNmae);
	char edgeFileNmae[20] = "edge.txt";
	g.initEdgeData(edgeFileNmae);
	cout << "景点的个数:" << g.getVexSize() << endl;
	g.createGraph();
	g.showVexs();
	g.showEdges();

}



void Tourism::findVex()
{
	int i = -2;
	while (i != -1)
	{

		cout << "请输入景点编号：";
		cin >> i;
		Vex* vex = g.GetVex(i);
		if (vex != nullptr)
		{
			printf_s("%d-----%s------%s\n", vex->getNum(), vex->getName(), vex->getDesc());
			cout << "=====周边信息=====" << endl;
			Edge *edges = new Edge[MAX];
			int len = g.FindEdge(i, edges);
			if (len != -1)
			{
				for (int i = 0; i < len; i++) {
					Vex* from = g.GetVex(edges[i].getVetFrom());
					Vex* to = g.GetVex(edges[i].getVexTo());
					printf_s("%s--->%s   %dm\n", from->getName(), to->getName(), edges[i].getWeight());
				}

			}
			else {
				cout << "暂无周边信息。" << endl;
			}
		}
		else {
			cout << "该编号对应的景点不存在！" << endl;
		}
		cin.clear();
		cin.sync();
		cin.ignore();
	}
}

/*
@param nVex:顶点编号。
@param pList:遍历得到的结果
*/
void Tourism::DFSTraverse(int nVex, PathList & pList)
{
	for (int i = 0; i < MAX; i++)
	{
		this->bVisited[i] = 0;
	}
	this->g.DNF(nVex,bVisited, 0, pList);

}

void Tourism::findShortPath(int nVexStart, int nVexEnd)
{
	this->g.findShortPath(nVexStart,nVexEnd);
}

void Tourism::desigPath(int start)
{
	int edgeSize = this->g.getVexSize() -1 ;
	Edge* edges = new Edge[edgeSize];
	this->g.findMinTree(edges,start);
	int totalCost = 0;
	for (int  i = 0; i < edgeSize; i++)
	{
		Vex* from = this->g.GetVex(edges[i].getVetFrom());
		Vex* to = this->g.GetVex(edges[i].getVexTo());
		totalCost += edges[i].getWeight();
		printf("%s-->%s:	%dm\n",from->getName(),to->getName(),edges[i].getWeight());
	}
	cout << "总共：" << totalCost<<"m"<<endl;
}




Tourism::~Tourism()
{
}
