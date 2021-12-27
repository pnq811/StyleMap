#include "pch.h"
#include "stdafx.h"
#include "Building.h"
#include "../StringProcess.h"
#include "../Relation/CHeight.h"
#include "../Relation/CWeight.h"
#include "../Relation/CWidth.h"

void Building::node(const osmium::Node& node)
{
	Node::Type type = Node::Type::NONE;
	auto id = node.id();
	auto location = node.location();
	double lat = location.lat();
	double lon = location.lon();
	const auto& tags = node.tags();
	double Min[2];
	double Max[2];
	Min[0] = Max[0] = lon;
	Min[1] = Max[1] = lat;
	BMin[0] = (std::min)(BMin[0], lon);
	BMin[1] = (std::min)(BMin[1], lat);
	BMax[0] = (std::max)(BMax[0], lon);
	BMax[1] = (std::max)(BMax[1], lat);
	auto cfloor = tags.get_value_by_key("level");
	if (tags.has_key("amenity"))
	{
		auto amenity = tags.get_value_by_key("amenity");
		if (!strcmp(amenity, "bar"))
		{
			type = Node::Type::BAR;
		}
		if (!strcmp(amenity, "ice_cream"))
		{
			type = Node::Type::ICE_CREAM;
		}
		if (!strcmp(amenity, "restaurant"))
		{
			type = Node::Type::RESTAURANT;
		}
		if (!strcmp(amenity, "cafe"))
		{
			type = Node::Type::CAFE;
		}
		if (!strcmp(amenity, "cinema"))
		{
			type = Node::Type::CINEMA;
		}
		if (!strcmp(amenity, "casino"))
		{
			type = Node::Type::CASINO;
		}
		if (!strcmp(amenity, "fast_food"))
		{
			type = Node::Type::FAST_FOOD;
		}
		if (!strcmp(amenity, "library"))
		{
			type = Node::Type::LIBRARY;
		}
		if (!strcmp(amenity, "toilets"))
		{
			auto female = tags.get_value_by_key("female");
			if (!strcmp(female, "yes"))
			{
				type = Node::Type::WC_FEMALE;
			}
			else
			{
				type = Node::Type::WC_MALE;
			}
		}
	}
	if (tags.has_key("highway"))
	{
		if (!strcmp(tags.get_value_by_key("highway"), "elevator"))
		{
			type = Node::Type::ELEVATOR;
		}
		if (!strcmp(tags.get_value_by_key("highway"), "steps"))
		{
			type = Node::Type::STAIR;
		}
	}

	if (type != Node::Type::NONE)
	{
		POI.push_back(id);
	}
	int floor = StringProcess::ConstCharToInt(cfloor);
	Node* _node = new Node(id, floor, lon, lat);
	_node->type = type;
	m_pRTNode->Insert(Min, Max, _node);
	m_pNode->push_back(_node);
	++m_numnode;
}

void Building::way(const osmium::Way& way)
{
	auto id = way.id(); 
	const auto& tags = way.tags(); 
	int floor; 
	Edge::Type type; 
	if (tags.has_key("level"))
	{
		auto cfloor = tags.get_value_by_key("level");
		floor = StringProcess::ConstCharToInt(cfloor);
		type = Edge::Type::EDGE; 
		m_numfloor = floor; 
	}
	if (tags.has_key("highway"))
	{
		floor = -1;
		if (!strcmp(tags.get_value_by_key("highway"),"elevator"))
		{
			type = Edge::Type::EVELATOR;
		}
		else
		{
			type = Edge::Type::STAIR;
		}
	}
	if (!way.nodes().empty())
	{
		for (int i = 0; i < way.nodes().size() - 1; ++i)
		{
			double Min[2];
			double Max[2];
			const auto& node1 = way.nodes()[i];
			const auto& node2 = way.nodes()[i + 1];
			Node* pnode1 = m_pNode->at(node1.ref() - 1);
			Node* pnode2 = m_pNode->at(node2.ref() - 1);
			Edge* edge = new Edge(id, floor, type, pnode1, pnode2);
			//LAY KHUNG BOUND 
			Min[0] = (std::min)(pnode1->lon, pnode2->lon);
			Min[1] = (std::min)(pnode1->lat, pnode2->lat);
			Max[0] = (std::max)(pnode1->lon, pnode2->lon);
			Max[1] = (std::max)(pnode1->lat, pnode2->lat);
			//THEM NODE KE 
			Node::Adj adj;
			adj.node = pnode2;
			adj.edge = id;
			pnode1->m_pAdj->push_back(adj);
			adj.node = pnode1;
			adj.edge = id;
			pnode2->m_pAdj->push_back(adj);
			m_pRTEdge->Insert(Min, Max, edge);
			m_pEdge->push_back(edge);
		}
	}
	else
	{
		Node* pnode1 = NULL;
		Node* pnode2 = NULL;
		Edge* edge = new Edge(id, floor, type, pnode1, pnode2);
		m_pEdge->push_back(edge);
	}

}

void Building::relation(const osmium::Relation& relation)
{
	auto id = relation.id(); 
	const auto& tags = relation.tags();
	if (tags.has_key("weight") || tags.has_key("width") || tags.has_key("height"))
	{
		std::vector<IConstraint*> constraints;
		int idedge;
		if (relation.members().size() == 1)
		{
			for (const auto& member : relation.members())
			{
				idedge = member.ref(); 
			}
		}
		if (tags.has_key("weight"))
		{
			auto value = tags.get_value_by_key("weight"); 
			double weight = StringProcess::cs2double(value); 
			IConstraint* cweight = new CWeight(id, weight); 
			constraints.push_back(cweight);
		}
		if (tags.has_key("height"))
		{
			auto value = tags.get_value_by_key("height"); 
			double height = StringProcess::cs2double(value); 
			IConstraint* cheight = new CHeight(id, height); 
			constraints.push_back(cheight); 
		}
		if (tags.has_key("width"))
		{
			auto value = tags.get_value_by_key("width"); 
			double width = StringProcess::cs2double(value); 
			IConstraint* cwidth = new CWidth(id, width); 
			constraints.push_back(cwidth); 
		}
		um_pConstraint->insert({ idedge,constraints }); 
	}
}

void Building::Initialize()
{
	//DATA 
	m_numnode = 0;
	m_numedge = 0;
	m_currentfloor = 1; 
	m_numfloor = 0; 
	BMin[0] = (std::numeric_limits<double>::max)();
	BMin[1] = (std::numeric_limits<double>::max)();
	BMax[0] = (std::numeric_limits<double>::lowest)();
	BMax[1] = (std::numeric_limits<double>::lowest)(); 
	m_pRTNode = new RTree<Node*, double, 2>(); 
	m_pNode = new std::vector<Node*>(); 
	m_pRTEdge = new RTree<Edge*, double, 2>(); 
	m_pEdge = new std::vector<Edge*>(); 
	um_pConstraint = new std::map<int, std::vector<IConstraint*>>(); 
}

bool Building::IsNull()
{
	return (m_pNode == NULL) && (m_pEdge == NULL); 
}

void Building::Exit()
{
	m_numnode = 0; 
	m_numedge = 0; 
	m_currentfloor = 0; 
	BMin[0] = (std::numeric_limits<double>::max)();
	BMin[1] = (std::numeric_limits<double>::max)();
	BMax[0] = (std::numeric_limits<double>::lowest)();
	BMax[1] = (std::numeric_limits<double>::lowest)();
	if (m_pRTNode != NULL)
	{
		m_pRTNode->RemoveAll(); 
		delete m_pRTNode; 
		m_pRTNode = NULL; 
		
		if (m_pNode != NULL)
		{
			for (int i = 0; i < m_pNode->size(); ++i)
			{
				delete m_pNode->at(i); 
				m_pNode->at(i) = NULL; 
			}
		}
		m_pNode->clear(); 
		delete m_pNode; 
		m_pNode = NULL; 
	}

	if (m_pRTEdge != NULL)
	{
		m_pRTEdge->RemoveAll(); 
		delete m_pRTEdge; 
		m_pRTEdge = NULL; 

		if (m_pEdge != NULL)
		{
			for (int i = 0; i < m_pEdge->size(); ++i)
			{
				delete m_pEdge->at(i); 
			}
			m_pEdge->clear(); 
			delete m_pEdge; 
			m_pEdge = NULL; 
		}
	}

	if (um_pConstraint != NULL)
	{
		std::map<int, std::vector<IConstraint*>>::iterator it; 
		for (it = um_pConstraint->begin(); it != um_pConstraint->end(); ++it)
		{
			std::vector<IConstraint*> constraints = it->second; 
			for (int i = 0; i < constraints.size(); ++i)
			{
				delete constraints.at(i); 
			}
		}
		um_pConstraint->clear(); 
		delete um_pConstraint; 
		um_pConstraint = NULL; 
	}
	m_pPath.clear();
	//if (m_nCData.size() != 0)
	//{
	//	for (int i = 0; i < m_nCData.size(); ++i)
	//	{
	//		if (m_nCData.at(i) != NULL)
	//		{
	//			if (m_nCData.at(i)->type == Node::Type::CLICK)
	//			{
	//				delete m_nCData.at(i);
	//			}
	//		}
	//	}
	//	
	//}

}

std::vector<Node*> Building::GetNodeWithinBound(double Min[2], double Max[2])
{
	std::vector<Node*> result; 
	if (m_pRTNode != NULL)
	{
		RTree<Node*, double, 2>::Iterator it(Min, Max); 
		m_pRTNode->GetFirst(it); 
		Node* _node; 
		while (!it.IsNull())
		{
			_node = *it; 
			if (_node->floor == m_currentfloor)
			{
				result.push_back(_node); 
			}
			m_pRTNode->GetNext(it);
		}
	}
	return result; 
}



std::vector<Edge*> Building::GetEdgeWithinBound(double Min[2], double Max[2])
{
	std::vector<Edge*> result; 
	if (m_pRTEdge != NULL)
	{
		RTree<Edge*, double, 2>::Iterator it(Min, Max); 
		m_pRTEdge->GetFirst(it); 
		Edge* edge; 
		while (!it.IsNull())
		{
			edge = *it; 
			if (edge->floor == m_currentfloor)
			{
				result.push_back(edge); 
			}
			m_pRTEdge->GetNext(it); 
		}
	}
	return result; 
}

std::vector<Node*> Building::GetPathInFloor(double Min[2], double Max[2])
{
	std::vector<Node*> result;
	for (Node* _node : m_pPath)
	{
		if (_node->floor == m_currentfloor)
		{
			result.push_back(_node);
		}
	}
	return result;
}

void Building::Snap(Node* node)
{
	if (node->id < 0)
	{
		//SNAP 
		if (node->m_pAdj->size() != 0)
		{
			for (Node::Adj adj : *node->m_pAdj)
			{
				Node* pnode = adj.node;
				int idedge = adj.edge;
				Node::Adj adj;
				adj.node = node;
				adj.edge = idedge;
				pnode->m_pAdj->push_back(adj); 
			}
		}
	}
}

void Building::ResetSnap(Node* node)
{
	if (node->id < 0)
	{
		if (node->m_pAdj->size() != 0)
		{
			for (Node::Adj adj : *node->m_pAdj)
			{
				Node* pnode = adj.node; 
				pnode->DeleteAdj(node->id); 
			}
		}
	}
}


