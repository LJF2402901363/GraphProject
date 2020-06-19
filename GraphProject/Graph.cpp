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
������Ϣ���ļ����ݶ�ȡ����������ȥ��
@param edgeDataFilePath :����Ϣ�ļ�
*/
void Graph::initEdgeData(const char * edgeDataFilePath)
{
	//���ļ����ж�д
	fstream* ism = new fstream(edgeDataFilePath,ios::in|ios::binary);
	if (ism->is_open())
	{
		//�ߵ��������
		int vexFromIndex = -1;
		//�ߵĽ���������
		int vexToIndex = -1;
		//�ߵ�Ȩ��
		int weight = 0;
		//��ʶÿ�ж�ȡ����Ԫ��
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
		cout << "���ļ�ʧ�ܣ�" << endl;
	}
	
}
/*
���ڵ���Ϣ���ļ����ݶ�ȡ���ڵ�������ȥ��
@param vexDataFilePath :�ڵ���Ϣ�ļ�
*/
void Graph::initVexData(const char * vexDataFilePath)
{
	//���ļ����ж�д
	fstream* ism = new fstream(vexDataFilePath, ios::in );
	if (ism->is_open()) {
		//��ȡ�ڵ�ĸ���
		this->vexSize = ism->get() -'0';
		if (vexSize <= 0)
		{
			cout << "����������ȡ����";
			return;
		}
		int vexIndex = 0;
		bool fla = false;
		while (!ism->eof())
		{
			string s = "";
			//��ȡ�ڵ���
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
				//��ȡ���������
				char name[NAME_SIZE];
				ism->getline(name, NAME_SIZE);
				//��ȡ����Ľ���
				char desc[DESC_SIZE];
				ism->getline(desc,DESC_SIZE);
				//����һ���ڵ�
				Vex vex(num, name, desc);
				this->vexs[this->indexVex++] = vex;
				fla = false;
			}

		}
	}
	else {
		cout << "��ȡ�ڵ���Ϣʧ�ܣ�" << endl;
	}
}

/*
����ͼ�����ݱߵ���Ϣ���������ͼ��
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
	//�鿴�Ӹþ����Ƿ��Ѿ�����
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
���ݾ���ı������ȡ�������Ϣ
@param nVex:����ı��
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
���ݴ���ľ����Ż�ȡ�ܱߵľ���Ȼ���ŵ��������У�����ҵ��򷵻رߵ����������򷵻�-1
@param nVex:������
@param edge:�����ź���Χ������ɵıߵ�����
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
	cout << "----------��-------------------" << endl;
	for (int  i = 0; i < this->edgeSize; i++)
	{
		Vex from = this->vexs[this->edges[i].getVetFrom()];
		Vex to = this->vexs[this->edges[i].getVexTo()];
		printf_s("<V%d,V%d>	%d\n", from.getNum(), to.getNum(),this->edges[i].getWeight());
	}
}

void Graph::showVexs()
{
	cout << "----------����-------------------" << endl;
	for (int i = 0; i <this->indexVex; i++)
	{
		Vex vex= this->vexs[i];
		printf_s("%d-----%s------%s\n", vex.getNum(), vex.getName(), vex.getDesc());
	}
}
/*
@to do:����ȫ����·��
*(1) ��������bool bVisited [20]����ͼ�ж���ķ���״̬��
*(2) ��������int nIndex��¼ͼ�ķ�����ȡ�
*(3) �����ж��㶼�����ʹ����ͱ���һ��·����
*(4) ���ʽ����󣬽�����ķ���״̬��Ϊδ���ʣ�������ȼ�1���Ա���������������·�ߡ�
@param nVex:int nVex��������
@param bVisited:bool���͵����飬������¼ĳ�������Ƿ񱻱�������
@paran nIndex:��¼���������
@param pList:�����õ��Ľ��
*/
void Graph::DNF(int nVex, int bVisited[], int  nIndex, PathList & pList)
{

	
	//��Ƿ���״̬
	bVisited[nVex] = 1;
	//��ǽڵ�
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
			//�������+1
			nIndex++;
			DNF(i, bVisited, nIndex, pList);
			pList.vexs[nIndex] = -1;
			//�������-1
			nIndex--;
			//��Ƿ���״̬
			bVisited[i] = 0;
		}

	}
}
/*
 ����������������·��
@param nVexStart:��ʼ ��ı��
@param nVexEnd:������ı��
@param aPath:�ҵ������·������
@ return int :�������·��������
*/
int Graph::findShortPath(int nVexStart, int nVexEnd)
{
	int d[MAX], path[MAX];       //path�������ڼ�¼·��
	memset(path, -1, sizeof(path));//��path�����ʼ��Ϊ-1
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
			//path[j]��¼d[j]��ʱ���·�������һ����;�ڵ�min_num������d[j]���һ�δӽڵ�min_num���ڵ�j
				path[j] = min_num;
				d[j] = min + this->adjMatrix[min_num][j];
			}
		}
	}

	this->print(nVexStart,nVexEnd,path,d);
	return 0;
}
/*
 ��ӡ������������·��
@param nVexStart:��ʼ ��ı��
@param nVexEnd:������ı��
@param aPath:�ҵ������·������
@ return int :�������·��������
*/
void Graph::print(int nVexStart,int nVexend, int path[], int d[])     //nVexStartΪ�����ڵ㣬n��ʾͼ�нڵ�����
{
	
	//���ڼ�¼����;�ڵ��ǵ���ģ�����ʹ��ջ���Ƚ���������������
	stack<int> stack;          
	//��ӡ�ӳ����ڵ㵽���ڵ����̾���;�����·��
	 	int j = nVexend;
		while (path[j] != -1)      //���j����;�ڵ�
		{
			stack.push(j);          //��jѹ���
			j = path[j];          //��j��ǰ����;�ڵ㸳��j
		}
		stack.push(j);
		printf("��%s��%s�����·��Ϊ��%s-->", this->GetVex(nVexStart)->getName(), this->GetVex(nVexend)->getName(), this->GetVex(nVexStart)->getName());
		//�Ƚ����,�������
		while (!stack.empty())      
		{
			if (stack.size() ==1)
			{
				printf("%s\n", this->GetVex(stack.top())->getName());
			}
			else {
				printf("%s--> ", this->GetVex(stack.top())->getName());
			}
			//��ջ��ͷ�ڵ㵯��
			stack.pop();           
		}
		printf("���·��Ϊ��%d\n",d[nVexend]);

}

void Graph::showAllVexInfo()
{
	cout << "��� ������" << endl;
	for (int i = 0; i < this->vexSize; i++)
	{
		cout << i << " :" << this->vexs[i].getName() << endl;
	}
}
/*
@param deges:����߼�������
@param start: ��ʼ�޽������
*/
void Graph::findMinTree(Edge edges[],int start)
{
	int lowcost[MAX], closest[MAX], i, min, j, k;
	//��¼����
	int index = 0;
	/*��ʼ��lowcost���飬closest����(������㿪ʼ����lowcost���飬closest������Ӧ��ֵ���Ա��������ʹ��)*/
	//����ֵ������closest���鶼��Ϊ��һ���ڵ�v��lowcost���鸳Ϊ��һ���ڵ�v�����ڵ��Ȩ��
	for (i = 0; i < this->getVexSize(); i++)
	{
		closest[i] = start;
		//this->adjMatrix[start][i]��ֵָ���ǽڵ�v��i�ڵ��Ȩ��
		lowcost[i] = this->adjMatrix[start][i];
	}

	//��������ʣ�µ�n-1���ڵ�
	for (i = 1; i < this->getVexSize(); i++)
	{

		/*�ҵ�һ���ڵ㣬�ýڵ㵽��ѡ�ڵ��е�ĳһ���ڵ��Ȩֵ�ǵ�ǰ��С*/
		//INF��ʾ�����ÿ����һ���ڵ㣬min�������¸���ΪINF���Ա��ȡ��ǰ��СȨ�صĽڵ㣩
		min = INF;
		//�������нڵ�
		for (j = 0; j < this->getVexSize(); j++)
		{
			//���ýڵ㻹δ��ѡ��ȨֵС��֮ǰ�������õ�����Сֵ
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				//����min��ֵ
				min = lowcost[j];
				//��¼��ǰ��СȨ�صĽڵ�ı��
				k = j;
			}
		}

		/*��������ӽڵ������ӽڵ㣬�Լ����ǵ�Ȩ**/
		//printf("��(%d,%d)ȨΪ:%d\n", closest[k], k, min);
		edges[index++] = *new Edge(closest[k],k,min);
		/*����lowcost���飬closest���飬�Ա�������һ���ڵ�*/
		//����k�ڵ��ѱ�ѡ��(�����)
		lowcost[k] = 0;
		//ѡ��һ���ڵ��������֮����������Ӧ�ĵ���
		for (j = 0; j < this->getVexSize(); j++)//�������нڵ�
		{
			
			if (this->adjMatrix[k][j] != 0 && this->adjMatrix[k][j] < lowcost[j])
			{
				//����Ȩ�أ�ʹ�䵱ǰ��С
				lowcost[j] = this->adjMatrix[k][j];
				//���뵽��if����˵����ѡ�Ľڵ�k�뵱ǰ�ڵ�j�и�С��Ȩ�أ���closest[j]�ı����ӽڵ������޸�Ϊk
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
