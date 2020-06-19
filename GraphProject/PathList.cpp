#include "PathList.h"



PathList::PathList()
{
	for (int i = 0; i < 20; i++)
	{
		this->vexs[i] = -1;
	}
}


PathList::~PathList()
{
}
