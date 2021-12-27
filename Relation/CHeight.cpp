#include "stdafx.h"
#include "CHeight.h"
CHeight::CHeight(int _id, double _height) : IConstraint(_id)
{
	type = IConstraint::Type::HEIGHT; 
	height = _height; 
}

CHeight::~CHeight()
{

}

bool CHeight::check(double _paramater)
{
	return _paramater <= height; 
}
