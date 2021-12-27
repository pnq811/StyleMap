#pragma once
#ifndef _EDGE_H_
#define _EDGE_H_
#include "Node.h"

class Edge
{
public:
	enum class Type
	{
		EDGE,
		EVELATOR,
		STAIR,
		LOCATION
	};
public: 
	Edge(int _id, int _floor, Type _type ,Node* _node1, Node* _node2); 
	~Edge(); 
public: 
	int id; 
	int floor;
	Type type; 
	std::pair<Node*, Node*> nodes; 
};
#endif //_EDGE_H_

