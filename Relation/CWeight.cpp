#include "stdafx.h"
#include "CWeight.h"
CWeight::CWeight(int _id, double _weight) : IConstraint(_id)
{
	type = IConstraint::Type::WEIGHT; 
	weight = _weight; 
}

CWeight::~CWeight()
{

}

bool CWeight::check(double _paramater) 
{
	return _paramater <= weight; 
}
