#include "stdafx.h"
#include "FootPrint.h"

FootPrint::FootPrint(OGRGeometry* _Geometry, const int _id, std::string _metadata)
{
	Geometry = _Geometry; 
	id = _id; 
	metadata = _metadata; 
}

FootPrint::~FootPrint()
{

}
