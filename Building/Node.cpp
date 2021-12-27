#include "stdafx.h"
#include "Node.h"
Node::Node(int _id, int _floor, double _lon, double _lat)
{
	id = _id;
	floor = _floor; 
	lon = _lon;
	lat = _lat;
	m_pAdj = new std::vector<Adj>();
	type = Type::NONE; 
}

Node::~Node()
{
	if (m_pAdj != NULL)
	{
		m_pAdj->clear();
		delete m_pAdj;
		m_pAdj = NULL;
	}
}

void Node::DeleteAdj(int _id)
{
	int iddelete = -1; 
	for(int i = 0; i < m_pAdj->size(); ++i)
	{
		Node* pnode = m_pAdj->at(i).node; 
		if (pnode->id == _id)
		{
			iddelete = i; 
		}
	}
	if (iddelete != -1)
	{
		m_pAdj->erase(m_pAdj->begin() + iddelete); 
	}
}

int Node::GetEdge(int idnode)
{
	for (int i = 0; i < m_pAdj->size(); ++i)
	{
		if (m_pAdj->at(i).node->id == idnode)
		{
			return m_pAdj->at(i).edge; 
		}
	}
	return -1; 
}
