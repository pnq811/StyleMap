#include "stdafx.h"
#include "Edge.h"

Edge::Edge(int _id, int _floor, Type _type, Node* _node1, Node* _node2)
{
	id = _id; 
	floor = _floor; 
	type = _type; 
	nodes = std::make_pair(_node1, _node2); 
}

Edge::~Edge()
{

}
