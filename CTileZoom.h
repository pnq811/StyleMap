#pragma once 
#include "TileSystem.h"
//#include "atltypes.h"
#include "TransformActions.h"
#include "GE\Rect2D.h"
#include "afxwin.h"
#include <iostream> 

using namespace std;

struct TileRange
{
	int Left;
	int Top;
	int LeftTile;
	int TopTile;
	int RightTile;
	int BottomTile;
	int LevelOfDetail = 1;
};

class CUserAction;

class CTileZoomManager
{
public:
	CTileZoomManager();
	CTileZoomManager(int viewWidth, int viewHeight);
	CTileZoomManager(int viewWidth, int viewHeight, UINT tileSize);

public:
	TileRange    View;
	TileSystem TileSystem;

public:
	int        ViewWidth;
	int        ViewHeight;

	int        MaxLevel;
	int        MinLevel;
	BOOL    ZoomLocation;

public:
	UINT TileSize;
	int  WindowMinX;
	int  WindowMinY;
	int  WindowMaxX;
	int  WindowMaxY;

public:
	void ZoomAll(CRect client);
	void MoveTo(double lat, double lon, int levelOfDetail);
	void Pan(int pxFromX, int pxFromY, int pxToX, int pxToY);
	void SetTop(int nZoom, int type, CRect client, CPoint up, CPoint down, CPoint Mouse);
	void ZoomOut(int pX, int pY);
	void ZoomIn(int pX, int pY);
	void ZoomRealTime(CPoint up, CPoint down, CRect client);
	//	void ZoomPOut(int pxMinX, int pxMinY);
	//	void ZoomPIn(int pxMinX, int pxMinY);
	//
	void Resize(UINT w, UINT h);
	//
	//private:
	//	bool ZoomCenter(GEPoint2D p);
	//	bool ZoomRealtime(GERect2D& rc);
	//	bool ZoomExtents(GERect2D& rc, CDC* pDC);
	//	bool ZoomIn(GERect2D& rc);
	//	bool ZoomOut(GERect2D& rc);
	//	void ZoomOut_(GERect2D& rc);
	//	void ZoomIn_(GERect2D& rc);
	//
	//public:
	//	bool ExecuteAction(MapEngine::GERect2D& rc, TransformActions action, CDC* pDC);
	//	void SetParent(CWnd* pParent);
	//	void SetDC(CDC* pDC);

private:
	CUserAction* m_pUserAction;
	CWnd* m_pParent;
};