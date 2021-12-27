#pragma once
#ifndef _CWIDTH_H_
#define _CWIDTH_H_
#include "IConstraint.h"
class CWidth :
	public IConstraint
{
public: 
	CWidth(int _id, double _width); 
	~CWidth(); 
	bool check(double _paramater) override;
public:
	double width; 
};
#endif //_CWIDTH_H_


