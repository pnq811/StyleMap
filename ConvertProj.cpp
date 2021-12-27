#include "pch.h"
#include "stdafx.h"
#include "ConvertProj.h"
#include <iostream>
ConvertProj::ConvertProj()
{
	const char* srid3785 = "+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +wktext +no_defs";
	const char* srid4326 = "+proj=longlat +datum=WGS84 +no_defs";
	PJ_CONTEXT* c;
	c = proj_context_create();
	p_wgs842mercator = proj_normalize_for_visualization(PJ_DEFAULT_CTX, proj_create_crs_to_crs(c, srid4326, srid3785, NULL));
	p_mercator2wgs84 = proj_normalize_for_visualization(PJ_DEFAULT_CTX, proj_create_crs_to_crs(c, srid3785, srid4326, NULL));
#ifdef DEBUG
	if (p_wgs842mercator == 0)
	{
		std::cout << "Loi proj wgs84 sang mercator" << std::endl;
	}
	if (p_mercator2wgs84 == 0)
	{
		std::cout << "Loi proj mercator sang wgs84" << std::endl;
	}
#endif // DEBUG
	proj_context_destroy(c);
}

ConvertProj::~ConvertProj()
{
	proj_destroy(p_wgs842mercator);
	proj_destroy(p_mercator2wgs84);
}

void ConvertProj::wgs842mercator(double lon, double lat, double& lonmercator, double& latmercator)
{
	int c = 3;
	if (p_wgs842mercator == 0)
		return;
	PJ_COORD a, b;
	a = proj_coord(lon, lat, 0, 0);
	b = proj_trans(p_wgs842mercator, PJ_FWD, a);
	lonmercator = b.enu.e;
	latmercator = b.enu.n;
}

void ConvertProj::mercator2wgs84(double lon, double lat, double& lonwgs84, double& latwgs84)
{
	if (p_mercator2wgs84 == 0)
		return;
	PJ_COORD a, b;
	a = proj_coord(lon, lat, 0, 0);
	b = proj_trans(p_mercator2wgs84, PJ_FWD, a);
	lonwgs84 = b.enu.e;
	latwgs84 = b.enu.n;
}
