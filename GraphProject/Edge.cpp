#include "Edge.h"
Edge::Edge()
{
}

Edge::Edge(int vexFrom, int vexTo, int weight)
{
	this->vexFrom = vexFrom;
	this->vexTo = vexTo;
	this->weight = weight;
}

void Edge::setVexFrom(int vexFrom)
{
	this->vexFrom = vexFrom;
}

void Edge::setVexTo(int vexTo)
{
	this->vexTo = vexTo;
}

void Edge::setWeight(int weight)
{
	this->weight = weight;
}

int Edge::getVetFrom() const
{
	return this->vexFrom;
}

int Edge::getVexTo() const
{
	return this->vexTo;
}

int Edge::getWeight() const
{
	return this->weight;
}


Edge::~Edge()
{
}
