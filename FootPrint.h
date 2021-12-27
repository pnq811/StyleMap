#pragma once
#ifndef _FOOTPRINT_H_
#define _FOOTPRINT_H_
#include <string>
#include "ogrsf_frmts.h"
#include "ogr_geometry.h"
class FootPrint
{
public: 
	FootPrint(OGRGeometry* _Geometry, const int _id, std::string _metadata); 
	~FootPrint(); 
public: 
	OGRGeometry* Geometry; 
	std::string metadata; 
	int id; 
};
#endif // _FOOTPRINT_H_

