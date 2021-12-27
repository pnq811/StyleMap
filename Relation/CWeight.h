#pragma once
#ifndef _CWEIGHT_H_ 
#define _CWEIGHT_H_
#include "IConstraint.h"
class CWeight : public IConstraint
{
public: 
	CWeight(int _id, double _weight); 
	~CWeight(); 
	bool check(double _paramater) override; 
public: 
	double weight; 
};
#endif //_CWEIGHT_H_


