#include "stdafx.h"
#include "IConstraint.h"

IConstraint::IConstraint(int _id)
{
	id = _id;
	type = Type::NONE;
}

IConstraint::~IConstraint()
{

}