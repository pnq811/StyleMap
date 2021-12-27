#pragma once
#ifndef _CONVERTPROJ_H_
#define _CONVERTPROJ_H_

#include "proj.h"
class ConvertProj
{
public:
	ConvertProj();
	~ConvertProj();
	void wgs842mercator(double lon, double lat, double& lonmercator, double& latmercator);
	void mercator2wgs84(double lon, double lat, double& lonwgs84, double& latwgs84);
public:
	PJ* p_wgs842mercator;
	PJ* p_mercator2wgs84;
};
#endif // _CONVERTPROJ_H_