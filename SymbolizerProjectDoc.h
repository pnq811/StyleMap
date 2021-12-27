// SymbolizerProjectDoc.h : interface of the CSymbolizerProjectDoc class
//
#include "TransformManager.h"
#include "GE/Point2D.h"
#include "GE/RTree.h"
#include <vector>
#include "Building/Building.h"
#include "ConvertProj.h"
#include "FootPrint.h"
#include <map>
//-----------------------------raster tile
#include <string> 
#include "CTileZoom.h"
#include "lru_cache.h"
#include <sstream>
#include <cpr/cpr.h>

#include <pthreadpool.h>			// thread pool 
#include <assert.h>
#include <pthread.h>
#include "ThreadPool.h"
#pragma once

#define max_thpool 48

using namespace std;


class MetaImage
{
public:
	~MetaImage()
	{
		if (data != NULL)
		{
			delete[]data;
			data = NULL;
		}
	}

	double length;
	const char* data;

protected:

private:

};

struct threadpool_context
{
	int level, tileX, tileY;
	shared_ptr<MetaImage> TL;
};

class Task : IThreadTask
{
public:

	threadpool_context tile;

public:
	Task(threadpool_context tile) :tile(tile) {}

	void implement(CRITICAL_SECTION* const pCritical)
	{
		string sURL = "https://tile.openstreetmap.org/";
		sURL += to_string(tile.level) + "/" + to_string(tile.tileX) + "/" + to_string(tile.tileY) + ".png";

		auto r = cpr::Get(cpr::Url{ sURL });

		if (r.status_code == 200)
		{
			tile.TL->length /*= t_length*/ = r.text.size();
			char* p = new char[tile.TL->length];
			memcpy(p, r.text.data(), tile.TL->length);
			tile.TL->data /*= t_data */ = (const char*)p;
		}
	}
};

class CSymbolizerProjectDoc : public CDocument
{
protected: // create from serialization only
	CSymbolizerProjectDoc() noexcept;
	DECLARE_DYNCREATE(CSymbolizerProjectDoc)

	// Attributes
public:
	enum class MODE
	{
		QUERY,
		BUILDING
	};
	enum class MODEEXCUTEZOOM
	{
		QUERY,
		BUILDING
	};
public:
	struct Vector
	{
		Vector()
		{

		}
		Vector(MapEngine::GEPoint2D _p1, MapEngine::GEPoint2D _p2) : p1(_p1), p2(_p2)
		{
			x = (_p2.x - _p1.x);
			y = (_p2.y - _p1.y);
			length = sqrt(x * x + y * y);
		}
		MapEngine::GEPoint2D p1;
		MapEngine::GEPoint2D p2;
		double x;
		double y;
		double length;
		double dx;
		double dy;
	};
public:
	struct ViewP
	{
		typedef enum class Direction
		{
			GOSTRAIGHT,
			TURNRIGHT,
			TURNLEFT,
			LOCATION,
		};
		ViewP(int _index, int _numP, Direction _dir, double _length, int _floor)
		{
			index = _index;
			numP = _numP;
			direction = _dir;
			length = _length;
			floor = _floor;
		}
		Direction direction;
		double length;
		int index;
		int numP;
		int floor;
	};

public:
	struct Floor
	{
		COLORREF colorPath;
		int widthPath;
	};
public:
	CTransformManager* m_pTransformManager;
	// Operations
public:
	CString				 m_strDatabaseFile;
	MapEngine::GERect2D* m_pExtents;
	//TILE
	CTileZoomManager* m_pTileZoomManager = NULL;
	CPoint up, down;
	int type = 0;
	CPoint Mouse;
	double BMin[2];
	double BMax[2];
	int Rup = 0;

	int MMB = 0;					// on mouse move building tim node va canh 
	CPoint ms;

	int lv;

	bool CheckConstraint(int id);
	void FindPath();
	int SetPath();


	//--------------------------------------------------------------------

	CSymbolizerProjectDoc::ViewP::Direction DirectionOfTo(MapEngine::GEPoint2D A, MapEngine::GEPoint2D B, MapEngine::GEPoint2D P);

	//ZOOM 
	int m_zoomlever;
	int m_zoomleverbuilding;
	//DATA 
	GDALDataset* geDS;
	int _idStart, _idEnd;
	BOOL				 m_From = false;
	BOOL				 m_To = false;
	Building::Vehicle* vehicle = new Building::Vehicle;
	std::vector<ViewP*
	> PathSelect;
	//MAU
	COLORREF colorChose;
	CPen footprintpen;
	CPen nodepen;
	CBrush nodebrush;
	CPen poipen;
	CPen edgepen;
	CPen pathpen;
	CBrush pathbrush;
	//SIZE 
	int m_MouseSize;
	int m_MouseSelect;
	int m_idrclick;
	int m_idpoi;
	int m_idfrom;
	int m_idto;
	ViewP* m_PathSelect = NULL;
	int m_drawPath = -1;
	//MODE 
	MODE m_CurrentMode;
	MODEEXCUTEZOOM m_CurrentModeExcuteZoom;
	std::vector<Floor*> floors;
	//BUIDING 
	Building m_Building;
	//CONVERT 
	ConvertProj* convertproj;
	//CACHE 
	LRUCache<TileComparator::Key, shared_ptr<MetaImage>>* tile_cache;
	int m_cachesize;
	BOOL OnClick(CPoint p);
private:
	void ClearData();
	void DrawBuildingFootprints(GETransform2D* pTransform, CDC* pDC, double Min[2], double Max[2]);
	void DrawGeom(GETransform2D* pTransform, CDC* pDC, OGRGeometry* Geometry);
	BOOL Connect();
	std::vector<OGRGeometry*> GetFootPrintWithinBound(double Min[2], double Max[2]);
	std::string GetMetadataWithinBound(double Min[2], double Max[2]);
	void DrawNetwork(GETransform2D* pTransform, CDC* pDC, double Min[2], double Max[2]);
	double getDistanceHaversin2(double lat1, double lon1, double lat2, double lon2);
	double Distance2Point(double x1, double y1, double x2, double y2);
	double CalDistancePoint2Edge(MapEngine::GEPoint2D p_A, MapEngine::GEPoint2D p_B, MapEngine::GEPoint2D p_C, MapEngine::GEPoint2D& projection_P);
	bool OnQueryClick(CPoint p, double Min[2], double Max[2]);
	bool OnNetWorkClick(CPoint p, double Min[2], double Max[2]);
	GEPoint2D PointLineDistance(GEPoint2D p1, GEPoint2D p2, GEPoint2D p3);
	bool GetEdgeClick(CPoint point);
	bool GetNodeClick(CPoint point);
	BOOL OpenNetWork(std::string filename);
	void DrawPolygon(GETransform2D* pTransform, CDC* pDC, OGRPolygon* polygon);
	void UpDateMBR();
	void DrawTile(GETransform2D* pTransform, CDC* pDC);
	void DrawIMG(CString path, int x, int y, int size, CDC* pDC);
public:
	UINT				 m_ActionId;
	UINT				 m_GroupAction;

public:
	/*BOOL OnNewDocument();*/
	BOOL Start();
	void InitMap(void);
	BOOL RenderAvailable(void);
	void Draw(void);
	BOOL ExcuteUserAction(CPoint p, UINT nFlags);
	void ExitBuildingsMode();
	void SelectFloor(int floor);
	void OnMouseMoveBuilding(CPoint p, CDC* pDC);
	void ChangeStyleFloor(COLORREF pen, int width);
	void JumpToPoi();
	void JumpToCenter(MapEngine::GEPoint2D p);
	void SetFrom();
	void SetTo();
	void JumpToPath(ViewP* path);

	void DrawNetWorkWithoutBackground(CDC* pDC);

	void DrawArrow(CDC* pDC, GETransform2D* pTransform, MapEngine::GEPoint2D  dau, MapEngine::GEPoint2D  cuoi);
	void calcVertexes(MapEngine::GEPoint2D  startP, MapEngine::GEPoint2D  endP, MapEngine::GEPoint2D& p1, MapEngine::GEPoint2D& p2);

private:
	CView* GetView(void);
	BOOL ExecuteZoom(CPoint p, UINT nFlags);
	BOOL ExecuteSelection(CPoint p, UINT nFlags);
public:
	BOOL ExecuteMouseWheel(CPoint p, UINT nFlags, short zDelta);

	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CSymbolizerProjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};

