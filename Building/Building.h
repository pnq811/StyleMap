#pragma once
#ifndef _BUILDING_H_ 
#define _BUILDING_H_
#include <osmium/handler.hpp>
#include <osmium/io/any_input.hpp>
#include <osmium/util/memory.hpp>
#include <osmium/visitor.hpp>
#include <map>
#include "Node.h"
#include "Edge.h"
#include "../GE/RTree.h"
#include "../Relation/IConstraint.h"
#include "../Relation/CHeight.h"
#include "../Relation/CWeight.h"
#include "../Relation/CWidth.h"
class Building : public osmium::handler::Handler
{
public: 
	struct value
	{
		Node* p = NULL;
		bool free;
		double w;
		Node* cha = NULL;
	};
	struct Vehicle
	{
		double height = 1.7;
		double weight = 75;
		double width = 0.4;
	};
	//CAC HAM CUA OSMIUM 
	void node(const osmium::Node& node);
	void way(const osmium::Way& way);
	void relation(const osmium::Relation& relation);
	//CAC HAM CUA BUILDING 
	void Exit(); 
	void Initialize(); 
	bool IsNull(); 
	std::vector<Node*> GetNodeWithinBound(double Min[2], double Max[2]); 
	std::vector<Edge*> GetEdgeWithinBound(double Min[2], double Max[2]); 
	std::vector<Node*> GetPathInFloor(double Min[2], double Max[2]);
	void Snap(Node* node); 
	void ResetSnap(Node* node); 
public: 
	int m_numnode; 
	int m_numedge; 
	int m_numfloor; 
	int m_currentfloor;
	double BMin[2]; 
	double BMax[2]; 
	//DATA 
	Node* _From = NULL, * _To = NULL;
	Node* _FromPoint = NULL, * _ToPoint = NULL;
	RTree<Node*, double, 2>* m_pRTNode; 
	RTree<Edge*, double, 2>* m_pRTEdge; 
	std::vector<Node*>* m_pNode = NULL; 
	std::vector<Edge*>* m_pEdge = NULL; 
	std::vector<Node*> m_pPath;
	std::vector<int> POI;
	std::map<int, std::vector<IConstraint*>> *um_pConstraint;
};
#endif //_BUILDING_H_

