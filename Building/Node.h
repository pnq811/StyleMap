#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include <iostream>
class Node
{
public: 
	typedef enum class Type
	{
		NONE,
		ELEVATOR,
		STAIR,
		DOOR,
		CLICK,
		WC_MALE,
		WC_FEMALE,
		RESTAURANT,
		BAR,
		LIBRARY,
		CAFE,
		ICE_CREAM,
		CASINO,
		CINEMA,
		FAST_FOOD
	};
	struct Adj
	{
	public: 
		Node* node; 
		int edge; 
	};
//---
public: 
	Node(int _id, int _floor, double _lon, double _lat); 
	void DeleteAdj(int _id); 
	int GetEdge(int idnode); 
	~Node(); 
public: 
	Type type; 
	int id; 
	int floor; 
	double lat; 
	double lon; 
	std::vector<Adj>* m_pAdj;
};
#endif //_NODE_H_

