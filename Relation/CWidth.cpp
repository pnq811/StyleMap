#include "stdafx.h"
#include "CWidth.h"

CWidth::CWidth(int _id, double _width) : IConstraint(_id)
{
	type = IConstraint::Type::WIDTH; 
	width = _width; 
}

CWidth::~CWidth()
{

}

bool CWidth::check(double _paramater)
{
	return _paramater <= width; 
}