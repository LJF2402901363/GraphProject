#include "Graph.h"



Graph::Graph()
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX;j++) {
			this->adjMatrix[i][j] = (i == j ? 0 : INF);
			

		}

	}
	for (int i = 0; i < MAX; i++)
	{
		this->aVex[i] = -1;
	}
	this->vexSize = 0;
	this->edgeSize = 0;
	this->indexVex = 0;
}
/*
将边信息的文件内容读取到边数组中去。
@param edgeDataFilePath :边信息文件
*/
void Graph::initEdgeData(const char * edgeDataFilePath)
{
	//打开文件进行读写
	fstream* ism = new fstream(edgeDataFilePath,ios::in|ios::binary);
	if (ism->is_open())
	{
		//边的起点索引
		int vexFromIndex = -1;
		//边的结束点索引
		int vexToIndex = -1;
		//边的权重
		int weight = 0;
		//标识每行读取三个元素
		int index = 0;
		while (!ism->eof())
		{
			string s = "";
			bool fla = false;
			while (!ism->eof()) {
				int ch = ism->get();
				if (isdigit(ch))
				{
					s += to_string(ch - '0');
					fla = true;
				}
				else {
					break;
				}
				
			}
			if (fla)
			{
				int value = atoi(s.c_str());
				if (index == 0)
				{
					index++;
					vexFromIndex = value;
				}
				else if (index == 1) {
					vexToIndex = value;
					index++;
				}
				else if (index == 2)
				{
					weight = value;
					Edge edge(vexFromIndex,vexToIndex,weight);
					this->edges[this->edgeSize++] = edge;
					index = 0;
				}
				fla = false;
			}
			
		
		}
	}else{
		cout << "打开文件失败！" << endl;
	}
	
}
/*
将节点信息的文件内容读取到节点数组中去。
@param vexDataFilePath :节点信息文件
*/
void Graph::initVexData(const char * vexDataFilePath)
{
	//打开文件进行读写
	fstream* ism = new fstream(vexDataFilePath, ios::in );
	if (ism->is_open()) {
		//读取节点的个数
		this->vexSize = ism->get() -'0';
		if (vexSize <= 0)
		{
			cout << "景区数量读取错误！";
			return;
		}
		int vexIndex = 0;
		bool fla = false;
		while (!ism->eof())
		{
			string s = "";
			//读取节点编号
			while (!ism->eof())
			{
				int ch = ism->get();
				if (isdigit(ch))
				{
					s += to_string(ch - '0');
					fla = true;
				}
				else {
					break;
				}
			}
			if (fla)
			{
				int num = atoi(s.c_str());
				//读取景点的名字
				char name[NAME_SIZE];
				ism->getline(name, NAME_SIZE);
				//读取景点的介绍
				char desc[DESC_SIZE];
				ism->getline(desc,DESC_SIZE);
				//建立一个节点
				Vex vex(num, name, desc);
				this->vexs[this->indexVex++] = vex;
				fla = false;
			}

		}
	}
	else {
		cout << "读取节点信息失败！" << endl;
	}
}

/*
创建图：根据边的信息来逐个创建图。
*/
void Graph::createGraph()
{
	for (int  i = 0; i < this->edgeSize; i++)
	{
		Edge edge = this->edges[i];
		this->adjMatrix[edge.getVetFrom()][edge.getVexTo()] = edge.getWeight();
		this->adjMatrix[edge.getVexTo()][edge.getVetFrom()] = edge.getWeight();
	}

}

void Graph::insertVex( const Vex * vex)
{
	//查看接该景点是否已经存在
	bool fla = this->isVexExist(vex->getNum());
	if (fla == false)
	{
		this->vexs[this->indexVex++] = *vex;

	}
}


void Graph::insertEdge(const Edge & edge)
{
	bool fla =isEdgeExist(edge);
	if (fla == false)
	{
		this->edges[this->edgeSize++] = edge;

	}
}

bool Graph::isEdgeExist(const Edge & edge)
{
	for (int i = 0; i < this->edgeSize; i++)
	{
		if (this->edges[i].getVetFrom() == edge.getVetFrom() && this->edges[i].getVexTo() == edge.getVexTo()) {
			return true;
		}

	}
	
	return false;
}
/*
根据景点的编号来获取景点的信息
@param nVex:景点的编号
*/
Vex* Graph::GetVex(int nVex)
{
	for (int i = 0; i < this->indexVex; i++)
	{
		if (this->vexs[i].getNum() == nVex) {
			return &this->vexs[i];
		}

	}
	return  nullptr;
}
/*
根据传入的景点编号获取周边的景点然后存放到边数组中，如果找到则返回边的条数，否则返回-1
@param nVex:景点编号
@param edge:景点编号和周围景点组成的边的数组
*/
int Graph::FindEdge(int nVex, Edge *edges)
{
	bool fla = this->isVexExist(nVex);
	if (fla)
	{
		int count = 0;
		for (int  i = 0; i < this->vexSize; i++)
		{
			if (this->adjMatrix[nVex][i] != INF)
			{
			 count++;
			}
		}
		if (count > 0)
		{
			int index = 0;
			for (int i = 0; i < this->vexSize; i++)
			{
				if (this->adjMatrix[nVex][i] != INF)
				{
					Edge e(nVex,i, this->adjMatrix[nVex][i]);
					edges[index++] = e;
				}
			}
			return count;
		}
	}
	else {
		return -1;
	}
	return 0;
}

int Graph::getVexSize()
{
	return this->vexSize;
}

int Graph::getEdgeSize()
{
	return this->edgeSize;
}

void Graph::showEdges()
{
	cout << "----------边-------------------" << endl;
	for (int  i = 0; i < this->edgeSize; i++)
	{
		Vex from = this->vexs[this->edges[i].getVetFrom()];
		Vex to = this->vexs[this->edges[i].getVexTo()];
		printf_s("<V%d,V%d>	%d\n", from.getNum(), to.getNum(),this->edges[i].getWeight());
	}
}

void Graph::showVexs()
{
	cout << "----------景点-------------------" << endl;
	for (int i = 0; i <this->indexVex; i++)
	{
		Vex vex= this->vexs[i];
		printf_s("%d-----%s------%s\n", vex.getNum(), vex.getName(), vex.getDesc());
	}
}
/*
@to do:遍历全部的路径
*(1) 定义数组bool bVisited [20]保存图中顶点的访问状态。
*(2) 定义整数int nIndex记录图的访问深度。
*(3) 若所有顶点都被访问过，就保存一条路径。
*(4) 访问结束后，将顶点的访问状态改为未访问，访问深度减1，以便于生成其他访问路线。
@param nVex:int nVex，顶点编号
@param bVisited:bool类型的数组，用来记录某个顶点是否被遍历过。
@paran nIndex:记录遍历的深度
@param pList:遍历得到的结果
*/
void Graph::DNF(int nVex, int bVisited[], int  nIndex, PathList & pList)
{

	
	//标记访问状态
	bVisited[nVex] = 1;
	//标记节点
	pList.vexs[nIndex] = nVex;
	if (nIndex == this->vexSize-1)
	{
		
		PathList *p = &pList;
		while (p->next != nullptr)
		{
			p = p->next;
		}
		p->next = new PathList();
		int index = 0;
		for (int i = 0; i <= nIndex; i++)
		{
			if (pList.vexs[i] != -1) {
				p->next->vexs[index] = pList.vexs[i];
				index++;
			}
		}
	
		return;
	}
	for (int i = 0; i < MAX; i++)
	{
		if ( nVex != i && this->adjMatrix[nVex][i] != INF && bVisited[i] == 0)
		{
			//访问深度+1
			nIndex++;
			DNF(i, bVisited, nIndex, pList);
			pList.vexs[nIndex] = -1;
			//访问深度-1
			nIndex--;
			//标记访问状态
			bVisited[i] = 0;
		}

	}
}
/*
 查找两个景点间最短路径
@param nVexStart:开始 点的编号
@param nVexEnd:结束点的编号
@param aPath:找到的最短路径数组
@ return int :返回最短路径的条数
*/
int Graph::findShortPath(int nVexStart, int nVexEnd)
{
	int d[MAX], path[MAX];       //path数组用于记录路径
	memset(path, -1, sizeof(path));//将path数组初始化为-1
	int i = 0, j = 0;
	int min, min_num = 0;
	int vis[MAX] = { 0, };
	for (i = 0; i < this->vexSize; i++)
	{
		d[i] = this->adjMatrix[nVexStart][i];
	}
	vis[nVexStart] = 1; d[nVexStart] = 0;
	for (i = 0; i < this->vexSize; i++)
	{
		
		min = INF;
		for (j = 0; j < this->vexSize; j++)
		{
			if (!vis[j] && d[j] < min)
			{
				min = d[j];
				min_num = j;
			}
		}
		vis[min_num] = 1;
		for (j = 0; j < this->vexSize; j++)
		{
			if (d[j] > min + this->adjMatrix[min_num][j])
			{
			//path[j]记录d[j]暂时最短路径的最后一个中途节点min_num，表明d[j]最后一段从节点min_num到节点j
				path[j] = min_num;
				d[j] = min + this->adjMatrix[min_num][j];
			}
		}
	}

	this->print(nVexStart,nVexEnd,path,d);
	return 0;
}
/*
 打印两个景点间最短路径
@param nVexStart:开始 点的编号
@param nVexEnd:结束点的编号
@param aPath:找到的最短路径数组
@ return int :返回最短路径的条数
*/
void Graph::print(int nVexStart,int nVexend, int path[], int d[])     //nVexStart为出发节点，n表示图中节点总数
{
	
	//由于记录的中途节点是倒序的，所以使用栈（先进后出），获得正序
	stack<int> stack;          
	//打印从出发节点到各节点的最短距离和经过的路径
	 	int j = nVexend;
		while (path[j] != -1)      //如果j有中途节点
		{
			stack.push(j);          //将j压入堆
			j = path[j];          //将j的前个中途节点赋给j
		}
		stack.push(j);
		printf("从%s到%s的最短路径为：%s-->", this->GetVex(nVexStart)->getName(), this->GetVex(nVexend)->getName(), this->GetVex(nVexStart)->getName());
		//先进后出,获得正序
		while (!stack.empty())      
		{
			if (stack.size() ==1)
			{
				printf("%s\n", this->GetVex(stack.top())->getName());
			}
			else {
				printf("%s--> ", this->GetVex(stack.top())->getName());
			}
			//将栈的头节点弹出
			stack.pop();           
		}
		printf("最短路径为：%d\n",d[nVexend]);

}

void Graph::showAllVexInfo()
{
	cout << "编号 ：景点" << endl;
	for (int i = 0; i < this->vexSize; i++)
	{
		cout << i << " :" << this->vexs[i].getName() << endl;
	}
}
/*
@param deges:结果边集合数组
@param start: 开始修建的起点
*/
void Graph::findMinTree(Edge edges[],int start)
{
	int lowcost[MAX], closest[MAX], i, min, j, k;
	//记录边数
	int index = 0;
	/*初始化lowcost数组，closest数组(即从起点开始设置lowcost数组，closest数组相应的值，以便后续生成使用)*/
	//赋初值，即将closest数组都赋为第一个节点v，lowcost数组赋为第一个节点v到各节点的权重
	for (i = 0; i < this->getVexSize(); i++)
	{
		closest[i] = start;
		//this->adjMatrix[start][i]的值指的是节点v到i节点的权重
		lowcost[i] = this->adjMatrix[start][i];
	}

	//接下来找剩下的n-1个节点
	for (i = 1; i < this->getVexSize(); i++)
	{

		/*找到一个节点，该节点到已选节点中的某一个节点的权值是当前最小*/
		//INF表示正无穷（每查找一个节点，min都会重新更新为INF，以便获取当前最小权重的节点）
		min = INF;
		//遍历所有节点
		for (j = 0; j < this->getVexSize(); j++)
		{
			//若该节点还未被选且权值小于之前遍历所得到的最小值
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				//更新min的值
				min = lowcost[j];
				//记录当前最小权重的节点的编号
				k = j;
			}
		}

		/*输出被连接节点与连接节点，以及它们的权**/
		//printf("边(%d,%d)权为:%d\n", closest[k], k, min);
		edges[index++] = *new Edge(closest[k],k,min);
		/*更新lowcost数组，closest数组，以便生成下一个节点*/
		//表明k节点已被选了(作标记)
		lowcost[k] = 0;
		//选中一个节点完成连接之后，作数组相应的调整
		for (j = 0; j < this->getVexSize(); j++)//遍历所有节点
		{
			
			if (this->adjMatrix[k][j] != 0 && this->adjMatrix[k][j] < lowcost[j])
			{
				//更新权重，使其当前最小
				lowcost[j] = this->adjMatrix[k][j];
				//进入到该if语句里，说明刚选的节点k与当前节点j有更小的权重，则closest[j]的被连接节点需作修改为k
				closest[j] = k;
			}
		}
	}
	
}




Graph::~Graph()
{

}

bool Graph::isVexExist(int vexNum)
{
	for (int i = 0; i < this->indexVex; i++)
	{
		if (this->vexs[i].getNum() == vexNum)
		{
			return true;
		}
	}
	return false;
}
