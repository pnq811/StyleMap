#pragma once
#ifndef TILE_SYSTEM_H
#define TILE_SYSTEM
#include <math.h>
#include <algorithm>
#include <stdlib.h>

const int TileSize = 256;
const double RadToDeg = 57.29577;
const double EarthRadius = 6378137;
const double MinLatitude = -85.05112878;
const double MaxLatitude = 85.05112878;
const double MinLongitude = -180;
const double MaxLongitude = 180;
const double So_PI = 3.141592653589793238462643;

using namespace std;

// MBR VietNam: 102.144583, 7.391438, 117.817345, 23.393692
// MBR TP.HCM: 106.356421, 10.376714, 107.012798, 11.160291

class TileSystem
{
public:
	TileSystem() {}
	~TileSystem() {}

private:
	static double Clip(double n, double minValue, double maxValue)
	{
		return __min(__max(n, minValue), maxValue);
	}

public:
	static unsigned int MapSize(int levelOfDetail)
	{
		return (unsigned int)TileSize << levelOfDetail;
	}

	static unsigned int MapSizeInTile(int levelOfDetail)
	{
		return (unsigned int)1 << levelOfDetail;
	}

	static double GroundResolution(double latitude, int levelOfDetail)
	{
		latitude = Clip(latitude, MinLatitude, MaxLatitude);
		return cos(latitude * So_PI / 180) * 2 * So_PI * EarthRadius / MapSize(levelOfDetail);
	}

	static double MapScale(double latitude, int levelOfDetail, int screenDpi)
	{
		return GroundResolution(latitude, levelOfDetail) * screenDpi / 0.0254;
	}

	static void LatLongToPixelXY(double latitude, double longitude, int levelOfDetail, int& pixelX, int& pixelY)
	{
		latitude = Clip(latitude, MinLatitude, MaxLatitude);
		longitude = Clip(longitude, MinLongitude, MaxLongitude);

		double x = (longitude + 180) / 360;
		double sinLatitude = sin(latitude * So_PI / 180);
		double y = 0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * So_PI);

		unsigned int mapSize = MapSize(levelOfDetail);
		pixelX = (int)Clip(x * mapSize + 0.5, 0, mapSize - 1);
		pixelY = (int)Clip(y * mapSize + 0.5, 0, mapSize - 1);
	}

	static void PixelXYToLatLong(int pixelX, int pixelY, int levelOfDetail, double& latitude, double& longitude)
	{
		double mapSize = MapSize(levelOfDetail);
		double x = (Clip(pixelX, 0, mapSize - 1) / mapSize) - 0.5;
		double y = 0.5 - (Clip(pixelY, 0, mapSize - 1) / mapSize);

		latitude = 90 - 360 * atan(exp(-y * 2 * So_PI)) / So_PI;
		longitude = 360 * x;
	}

	static void PixelXYToTileXY(int pixelX, int pixelY, int& tileX, int& tileY)
	{
		tileX = pixelX / TileSize;
		tileY = pixelY / TileSize;
	}

	static void TileXYToPixelXY(int tileX, int tileY, int& pixelX, int& pixelY)
	{
		pixelX = tileX * TileSize;
		pixelY = tileY * TileSize;
	}

	static void LatLongToTileXY(double latitude, double longitude, int levelOfDetail, int& tileX, int& tileY)
	{
		latitude = Clip(latitude, MinLatitude, MaxLatitude);
		longitude = Clip(longitude, MinLongitude, MaxLongitude);

		double x = (longitude + 180) / 360;
		double sinLatitude = sin(latitude * So_PI / 180);
		double y = 0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * So_PI);

		unsigned int mapSize = MapSize(levelOfDetail);
		int pixelX = (int)Clip(x * mapSize + 0.5, 0, mapSize - 1);
		int pixelY = (int)Clip(y * mapSize + 0.5, 0, mapSize - 1);

		tileX = pixelX / TileSize;
		tileY = pixelY / TileSize;
	}

	static void TileXYToBound(int levelOfDetail, int tileX, int tileY, double& minLat, double& minLon, double& maxLat, double& maxLon)
	{
		long pixelMinX = tileX * TileSize;
		long pixelMinY = tileY * TileSize;
		long pixelMaxX = (tileX + 1) * TileSize;
		long pixelMaxY = (tileY + 1) * TileSize;

		PixelXYToLatLong(pixelMinX, pixelMinY, levelOfDetail, maxLat, minLon);
		PixelXYToLatLong(pixelMaxX, pixelMaxY, levelOfDetail, minLat, maxLon);
	}

	static void GetBound(int levelOfDetail, int tileX, int tileY, double& latMin, double& lonMin, double& latMax, double& lonMax)
	{
		double powZoom = MapSizeInTile(levelOfDetail);
		double lonDegPerPix = 360.0 / (TileSize * powZoom);

		latMax = atan(sinh(So_PI * (1 - 2 * (tileY) / powZoom))) * RadToDeg;	//NW corner
		latMin = atan(sinh(So_PI * (1 - 2 * (tileY + 1) / powZoom))) * RadToDeg;	//SE corner

		lonMin = (tileX / powZoom) * 360.0 - 180.0;
		lonMax = lonMin + lonDegPerPix * TileSize;
	}

	static void GetBound(int nLevelOfDetail, int nTileX, int nTileY, int nRadius, double& dLatMin, double& dLonMin, double& dLatMax, double& dLonMax, int& nWidth, int& nHeight)
	{
		double dPowZoom = MapSizeInTile(nLevelOfDetail);
		double dLonDegPerPix = 360.0 / (TileSize * dPowZoom);
		int nTileXMin = std::max<int>(0, nTileX - nRadius), nTileXMax = std::min<int>(dPowZoom, nTileX + nRadius);
		int nTileYMin = std::max<int>(0, nTileY - nRadius), nTileYMax = std::min<int>(dPowZoom, nTileY + nRadius);
		int nXTiles = nTileXMax - nTileXMin, nYTiles = nTileYMax - nTileYMin;

		nWidth = TileSize * nXTiles;
		nHeight = TileSize * nYTiles;

		dLatMax = atan(sinh(So_PI * (1 - 2 * (nTileYMin) / dPowZoom))) * RadToDeg;	//NW corner
		dLatMin = atan(sinh(So_PI * (1 - 2 * (nTileYMin + nYTiles) / dPowZoom))) * RadToDeg;	//SE corner

		dLonMin = (nTileXMin / dPowZoom) * 360.0 - 180.0;
		dLonMax = dLonMin + dLonDegPerPix * TileSize * nXTiles;
	}

	static void GetTiles(double latMin, double lonMin, double latMax, double lonMax, int levelOfDetail,
		int& tileXMin, int& tileYMin, int& tileXMax, int& tileYMax)
	{
		LatLongToTileXY(latMax, lonMin, levelOfDetail, tileXMin, tileYMin);
		LatLongToTileXY(latMin, lonMax, levelOfDetail, tileXMax, tileYMax);
	}

	static void GetTiles(double latMin, double lonMin, double latMax, double lonMax, int levelOfDetail,
		int& tileXMin, int& tileYMin, int& tileXMax, int& tileYMax,
		int& pixelXMin, int& pixelYMin, int& pixelXMax, int& pixelYMax)
	{
		// latitude1, longitude1
		latMin = Clip(latMin, MinLatitude, MaxLatitude);
		lonMin = Clip(lonMin, MinLongitude, MaxLongitude);

		double x = (lonMin + 180) / 360;
		double sinLatitude = sin(latMin * So_PI / 180);
		double y = 0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * So_PI);

		unsigned int mapSize = MapSize(levelOfDetail);
		int pixelX = (int)Clip(x * mapSize + 0.5, 0, mapSize - 1);
		int pixelY = (int)Clip(y * mapSize + 0.5, 0, mapSize - 1);

		tileXMin = pixelX / TileSize;
		tileYMin = pixelY / TileSize;
		pixelXMin = pixelX % TileSize;
		pixelYMin = pixelY % TileSize;

		// latitude2, longitude2
		latMax = Clip(latMax, MinLatitude, MaxLatitude);
		lonMax = Clip(lonMax, MinLongitude, MaxLongitude);

		x = (lonMax + 180) / 360;
		sinLatitude = sin(latMax * So_PI / 180);
		y = 0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * So_PI);

		pixelX = (int)Clip(x * mapSize + 0.5, 0, mapSize - 1);
		pixelY = (int)Clip(y * mapSize + 0.5, 0, mapSize - 1);

		tileXMax = pixelX / TileSize;
		tileYMax = pixelY / TileSize;
		pixelXMax = pixelX % TileSize;
		pixelYMax = pixelY % TileSize;
	}
};

#endif // TILE_SYSTEM)