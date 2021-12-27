#pragma once
#ifndef _CHEIGHT_H_
#define _CHEIGHT_H_
#include "IConstraint.h"
class CHeight :
	public IConstraint
{
public: 
	CHeight(int _id, double _height); 
	~CHeight(); 
	bool check(double _paramater) override; 
public: 
	double height; 
};
#endif //_CHEIGHT_H_


