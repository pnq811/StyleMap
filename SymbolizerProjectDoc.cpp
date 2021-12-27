
// Indoor NavigationDoc.cpp : implementation of the CSymbolizerProjectDoc class
//
#pragma once
#include "stdafx.h"
#include "pch.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SymbolizerProject.h"
#endif
#include<limits>
#include "SymbolizerProject.h"
#include "SymbolizerProjectDoc.h"
#include "MainFrm.h"
#include <propkey.h>
#include <iostream>
#include <map>
#include "StringProcess.h"

#include <chrono>
#include <sstream>
#include <cpr/cpr.h>
#include "TileSystem.h"

#include "Relations.h" // dialog relations
#include "CDialogProgress.h"
#include "atlimage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "myComparator.h"



// CSymbolizerProjectDoc

IMPLEMENT_DYNCREATE(CSymbolizerProjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CSymbolizerProjectDoc, CDocument)
END_MESSAGE_MAP()


// CSymbolizerProjectDoc construction/destruction

CSymbolizerProjectDoc::CSymbolizerProjectDoc() noexcept
{
	// TODO: add one-time construction code here
	m_pExtents = NULL;
	m_GroupAction = TRANSFORM_MAP;
	m_ActionId = ID_ZOOM_CENTER;
	m_pTransformManager = NULL;
	m_CurrentMode = MODE::QUERY;
	m_CurrentModeExcuteZoom = MODEEXCUTEZOOM::QUERY;
	//connection = NULL; 
	footprintpen.CreatePen(PS_SOLID, 2, RGB(255, 255, 26));
	nodepen.CreatePen(PS_SOLID, 2, RGB(102, 204, 255));
	edgepen.CreatePen(PS_DASH, 2, RGB(191, 191, 191));
	nodebrush.CreateSolidBrush(RGB(51, 102, 255));
	pathbrush.CreateSolidBrush(RGB(255, 0, 0));
	pathpen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	m_idpoi = -1;
	poipen.CreatePen(PS_SOLID, 2, RGB(255, 255, 153));
	m_MouseSize = 10;
	m_MouseSelect = 5;
	convertproj = new ConvertProj();
	m_cachesize = 1000;
	//tile_cache = new LRUCache<TileComparator::Key, CImage>(m_cachesize); 
	tile_cache = new LRUCache<TileComparator::Key, shared_ptr<MetaImage>>(m_cachesize);

	cpr::Response r = cpr::Get(cpr::Url{ "https://api.github.com/repos/whoshuu/cpr/contributors" },
		cpr::Authentication{ "user", "pass" },
		cpr::Parameters{ {"anon", "true"}, {"key", "value"} });
	r.status_code;                  // 200
	r.header["content-type"];       // application/json; charset=utf-8
	r.text;
}

CSymbolizerProjectDoc::~CSymbolizerProjectDoc()
{
	if (m_pExtents != NULL)
	{
		delete m_pExtents;
		m_pExtents = NULL;
	}

	if (m_pTileZoomManager != NULL)
	{
		delete m_pTileZoomManager;
		m_pTileZoomManager = NULL;
	}

	if (m_pTransformManager != NULL)
	{
		delete m_pTransformManager;
		m_pTransformManager = NULL;
	}

	if (convertproj != NULL)
	{
		delete convertproj;
		convertproj = NULL;
	}

	if (tile_cache != NULL)
	{
		tile_cache->clear();
		delete tile_cache;
		tile_cache = NULL;
	}
	GDALDestroy();
	ClearData();

	//-----------------------------------------------
}

void CSymbolizerProjectDoc::ClearData()
{
	if (floors.size() != 0)
	{
		for (int i = 0; i < floors.size(); i++)
			delete floors[i];

		floors.clear();
	}

	switch (m_CurrentMode)
	{
	case CSymbolizerProjectDoc::MODE::QUERY:
	{

	}
	break;
	case CSymbolizerProjectDoc::MODE::BUILDING:
	{
		if (!m_Building.IsNull())
		{
			m_Building.Exit();
		}
	}
	break;
	default:
		break;
	}
}

BOOL CSymbolizerProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	Start();

	return TRUE;
}


// CSymbolizerProjectDoc serialization

void CSymbolizerProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSymbolizerProjectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSymbolizerProjectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSymbolizerProjectDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSymbolizerProjectDoc diagnostics

#ifdef _DEBUG
void CSymbolizerProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSymbolizerProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSymbolizerProjectDoc commands
CView* CSymbolizerProjectDoc::GetView(void)
{
	POSITION posView = this->GetFirstViewPosition();
	CView* pView = this->GetNextView(posView);

	return pView;
}

BOOL CSymbolizerProjectDoc::ExecuteZoom(CPoint p, UINT nFlags)
{
	bool bRet = false;
	MapEngine::GERect2D rc;
	TransformActions action = TRANSFORM_ZOOMALL;

	rc.left = rc.right = p.x;
	rc.top = rc.bottom = p.y;

	if (m_CurrentModeExcuteZoom == MODEEXCUTEZOOM::QUERY)
	{
		action = TRANSFORM_ZOOMALL;
		switch (m_ActionId)
		{
		case ID_ZOOM_ALL:
			action = TRANSFORM_ZOOMALL;
			type = 0;
			break;
		case ID_ZOOM_EXTENTS:
			action = TRANSFORM_ZOOMEXTENTS;
			type = 1;
			break;
		case ID_ZOOM_IN:
		{
			if (m_CurrentModeExcuteZoom == MODEEXCUTEZOOM::QUERY)
			{
				if (m_pTileZoomManager->View.LevelOfDetail < 19)
				{
					type = 2;
					m_ActionId = 32778;
				}
				else
				{
					//Change zoom mode 
					if (m_CurrentMode == MODE::BUILDING)
					{
						m_CurrentModeExcuteZoom = MODEEXCUTEZOOM::BUILDING;
						m_zoomleverbuilding = 0;
						type = -1;
						action = TRANSFORM_ZOOMIN;
					}
					else
					{
						type = -2;
					}
				}
			}
		}
		break;
		case ID_ZOOM_OUT:
			if (m_pTileZoomManager->View.LevelOfDetail > 1)
			{
				action = TRANSFORM_ZOOMOUT;
				type = 3;
			}
			break;
		case ID_ZOOM_CENTER:
			action = TRANSFORM_ZOOMCENTER;
			type = 4;
			break;
		case ID_ZOOM_REALTIME:
			action = TRANSFORM_ZOOMREALTIME;
			rc.right = p.x;
			rc.bottom = p.y;
			type = 5;
			break;
		default:
			type = 0;
			break;
		}
		if (m_pTransformManager != NULL)
		{
			bRet = m_pTransformManager->ExecuteAction(rc, action);
		}
		down.x = rc.left;
		down.y = rc.top;
		up.x = Mouse.x = rc.right;
		up.y = Mouse.y = rc.bottom;
		return bRet;
	}

	if (m_CurrentModeExcuteZoom == MODEEXCUTEZOOM::BUILDING)
	{
		action = TRANSFORM_ZOOMCENTER;
		switch (m_ActionId)
		{
		case ID_ZOOM_REALTIME:
			action = TRANSFORM_ZOOMREALTIME;
			break;
		case ID_ZOOM_EXTENTS:
			action = TRANSFORM_ZOOMEXTENTS;
			break;
		case ID_ZOOM_IN:
			m_zoomleverbuilding++;
			action = TRANSFORM_ZOOMIN;
			break;
		case ID_ZOOM_OUT:
			--m_zoomleverbuilding;
			if (m_zoomleverbuilding >= 0) action = TRANSFORM_ZOOMOUT;
			else
			{
				m_CurrentModeExcuteZoom = MODEEXCUTEZOOM::QUERY;
				type = -2;
				m_ActionId = 32777;
			}
			break;
		case ID_ZOOM_CENTER:
			action = TRANSFORM_ZOOMCENTER;
			break;
		}
		if (m_pTransformManager != NULL)
		{
			bRet = m_pTransformManager->ExecuteAction(rc, action);
		}
		return bRet;
	}
}

BOOL CSymbolizerProjectDoc::RenderAvailable(void)
{
	BOOL bAvailable = (m_pTransformManager != NULL);

	return bAvailable;
}

BOOL CSymbolizerProjectDoc::ExcuteUserAction(CPoint p, UINT nFlags)
{
	BOOL bRet = FALSE;
	switch (m_GroupAction)
	{
	case TRANSFORM_MAP:
	{
		if (!OnClick(p))
		{
			bRet = ExecuteZoom(p, nFlags);
		}
		break;
	}
	case SELECTION_ACTIONS:
		break;
	}

	return bRet;
}

BOOL CSymbolizerProjectDoc::ExecuteMouseWheel(CPoint p, UINT nFlags, short zDelta)
{
	BOOL bRedraw = TRUE;
	GEPoint2D pt(p.x, p.y);

	if (m_pTransformManager != NULL)
	{
		GETransform2D* pTransform = m_pTransformManager->GetMainTransform();
		if (zDelta > 0)
		{
			if (m_CurrentModeExcuteZoom == MODEEXCUTEZOOM::QUERY)
			{
				if (m_pTileZoomManager->View.LevelOfDetail < 19)
				{
					type = 2;
					m_ActionId = 32778;
				}
				else
				{
					//Change zoom mode 
					if (m_CurrentMode == MODE::BUILDING)
					{
						m_CurrentModeExcuteZoom = MODEEXCUTEZOOM::BUILDING;
						m_zoomleverbuilding = 0;
						type = -1;
					}
					else
					{
						type = -2;
					}
				}
			}
			if (m_CurrentModeExcuteZoom == MODEEXCUTEZOOM::BUILDING)
			{
				++m_zoomleverbuilding;
				pTransform->ZoomPIn(pt);
			}
		}
		else
			if (zDelta < 0)
			{
				if (m_CurrentModeExcuteZoom == MODEEXCUTEZOOM::QUERY)
				{
					if (m_pTileZoomManager->View.LevelOfDetail > 1)
					{
						type = 3;
						m_ActionId = 32779;
					}
					else
					{
						type = -1; m_ActionId = 0;
					}
				}
				if (m_CurrentModeExcuteZoom == MODEEXCUTEZOOM::BUILDING)
				{
					--m_zoomleverbuilding;
					if (m_zoomleverbuilding > 0)
						pTransform->ZoomPOut(pt);
					else
					{
						m_CurrentModeExcuteZoom = MODEEXCUTEZOOM::QUERY;
						type = -2;
						m_ActionId = 32777;
					}
				}
			}
			else
				bRedraw = FALSE;
	}

	Mouse = p;

	return bRedraw;
}

void CSymbolizerProjectDoc::InitMap(void)
{

	if (m_pTransformManager != NULL)
	{
		delete m_pTransformManager;
		m_pTransformManager = NULL;
	}
	if (m_pExtents != NULL)
	{
		CView* pView = GetView();

		if (pView != NULL)
		{
			CRect				rcClient;
			MapEngine::GERect2D rcView;
			MapEngine::GERect2D rcMap;

			rcMap = *m_pExtents;

			pView->GetClientRect(&rcClient);
			rcView.left = rcClient.left;
			rcView.top = rcClient.top;
			rcView.right = rcClient.right;
			rcView.bottom = rcClient.bottom;

			m_pTransformManager = new CTransformManager();
			m_pTransformManager->SetParent(pView);
			m_pTransformManager->InitMainTransform(rcMap, rcView);
			m_pTransformManager->CreateMainWindow(rcClient.Width(), rcClient.Height(), RGB(255, 255, 255));

			UpdateAllViews(NULL);
		}
	}
}

bool CSymbolizerProjectDoc::CheckConstraint(int id)
{
	if (!m_Building.um_pConstraint->count(id))
	{
		return true;
	}
	std::vector<IConstraint*> constraints = m_Building.um_pConstraint->at(id);
	for (auto iCons : constraints)
	{
		switch (iCons->type)
		{
		case IConstraint::Type::HEIGHT:
			if (!iCons->check(vehicle->height))
			{
				return false;
			}
			break;
		case IConstraint::Type::WEIGHT:
			if (!iCons->check(vehicle->weight))
			{
				return false;
			}
			break;
		case IConstraint::Type::WIDTH:
			if (!iCons->check(vehicle->width))
			{
				return false;
			}
			break;
		default:
			break;
		}
	}
	return true;
}

void CSymbolizerProjectDoc::FindPath()
{

	m_Building.Snap(m_Building._To);
	m_Building.Snap(m_Building._From);
	_idEnd = m_Building._To->id;
	_idStart = m_Building._From->id;
	std::priority_queue<Building::value*, std::vector<Building::value*>, myComparator > pq;
	std::map<int, Building::value > D;
	m_Building.m_pPath.clear();
	for (int i = 0; i < m_Building.m_numnode; i++)
	{
		D[i + 1].p = m_Building.m_pNode->at(i);
		D[i + 1].free = true;
		D[i + 1].w = 99999999;
		D[i + 1].cha = NULL;
	}
	if (_idEnd < 0)
	{
		D[_idEnd].p = m_Building._To;
		D[_idEnd].free = true;
		D[_idEnd].w = 99999999;
		D[_idEnd].cha = NULL;
	}
	if (_idStart < 0)
	{
		D[_idStart].p = m_Building._From;
		D[_idStart].cha = NULL;
	}
	D[_idStart].w = 0;
	D[_idStart].free = false;
	pq.push(&D[_idStart]);

	while (!pq.empty())
	{
		Building::value val = *pq.top();
		pq.pop();
		for (Node::Adj _nextNode : *val.p->m_pAdj)
		{
			double W = getDistanceHaversin2(val.p->lon, val.p->lat, _nextNode.node->lon, _nextNode.node->lat);
			if (D[_nextNode.node->id].w > val.w + W && CheckConstraint(_nextNode.edge))
			{
				D[_nextNode.node->id].w = val.w + W;
				if (D[_nextNode.node->id].free)
				{
					D[_nextNode.node->id].free = false;
					pq.push(&D[_nextNode.node->id]);
				}
				D[_nextNode.node->id].cha = val.p;

			}
		}
	}
	Node* Target = m_Building._To;

	while (Target != NULL)
	{
		m_Building.m_pPath.push_back(Target);
		Target = D[Target->id].cha;
	}
	std::reverse(m_Building.m_pPath.begin(), m_Building.m_pPath.end());
	SetPath();
	//Reset snap 
	m_Building.ResetSnap(m_Building._To);
	m_Building.ResetSnap(m_Building._From);
	//if (_idStart < 0)
	//{
	//	delete m_Building._From;
	//}
	//if (_idEnd < 0)
	//{
	//	delete m_Building._To;
	//}
	m_Building._To = NULL;
	m_Building._From = NULL;
}

int CSymbolizerProjectDoc::SetPath()
{
	GETransform2D* pTransform = m_pTransformManager->GetMainTransform();
	PathSelect.clear();
	std::vector<Node*> path = m_Building.m_pPath;
	int numPath = path.size();
	if (path.size() < 2)
	{
		CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
		pMainWnd->m_wndFileView.FillFileView();
		return false;
	};
	int _index = 0;
	int count = 1;
	Edge::Type type1 = Edge::Type::EDGE;
	double length = getDistanceHaversin2(path[0]->lat, path[0]->lon, path[1]->lat, path[1]->lon) * 1000;
	PathSelect.push_back(new ViewP(0, 1, ViewP::Direction::LOCATION, 0, path[0]->floor));
	PathSelect.push_back(new ViewP(0, 1, ViewP::Direction::GOSTRAIGHT, length, path[0]->floor));
	for (int i = 1; i < numPath - 1; ++i)
	{
		Node* node1 = path[i];
		ViewP::Direction direction;
		Node* node2 = path[i + 1];
		Node* node3 = path[i - 1];
		Edge::Type _type = m_Building.m_pEdge->at(node1->GetEdge(node2->id) - 1)->type;
		if (_type != Edge::Type::EDGE)
		{
			type1 = _type;
		}
		MapEngine::GEPoint2D vp1, vp2, vp3;
		convertproj->wgs842mercator(node1->lon, node1->lat, vp1.x, vp1.y);
		convertproj->wgs842mercator(node2->lon, node2->lat, vp2.x, vp2.y);
		convertproj->wgs842mercator(node3->lon, node3->lat, vp3.x, vp3.y);
		length = getDistanceHaversin2(node1->lat, node1->lon, node2->lat, node2->lon) * 1000;// M 
		direction = DirectionOfTo(vp3, vp1, vp2);
		if (direction == ViewP::Direction::GOSTRAIGHT)
		{
			PathSelect[count]->length += length;
			PathSelect[count]->numP++;
		}
		else
		{
			PathSelect.push_back(new ViewP(i, 1, direction, length, path[i]->floor));
			count++;
		}
	}
	PathSelect.push_back(new ViewP(numPath - 1, 1, ViewP::Direction::LOCATION, 0, path[numPath - 1]->floor));

	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	pMainWnd->m_wndFileView.SetData(type1);
	return true;
}

CSymbolizerProjectDoc::ViewP::Direction CSymbolizerProjectDoc::DirectionOfTo(MapEngine::GEPoint2D A, MapEngine::GEPoint2D B, MapEngine::GEPoint2D P)
{
	B.x -= A.x;
	B.y -= A.y;
	P.x -= A.x;
	P.y -= A.y;

	// Determining cross Product
	real64 cross_product = B.x * P.y - B.y * P.x;
	std::cout << cross_product << '\10' << "\n";
	// return RIGHT if cross product is positive
	if (cross_product > 1.1)
		return ViewP::Direction::TURNLEFT;

	// return LEFT if cross product is negative
	if (cross_product < -1.1)
		return ViewP::Direction::TURNRIGHT;

	// return ZERO if cross product is zero. 
	return ViewP::Direction::GOSTRAIGHT;
}

void CSymbolizerProjectDoc::Draw()
{
	if (Rup == 1)					 // chon option thi ko redraw
	{
		Rup = 0;
		return;
	}
	if (m_pTransformManager != NULL)
	{
		GETransform2D* pTransform = m_pTransformManager->GetMainTransform();
		CDC* pDC = m_pTransformManager->GetMainDC();

		m_pTransformManager->m_MainWindow.FillBackground();

		// Draw here
		if (type != -1)  DrawTile(pTransform, pDC);

		if (m_pTileZoomManager)
		{
			if (m_pTileZoomManager->View.LevelOfDetail >= 15 & m_pTileZoomManager->View.LevelOfDetail <= 19)
			{
				if (m_CurrentModeExcuteZoom == MODEEXCUTEZOOM::QUERY) UpDateMBR();

				MapEngine::GERect2D rcView = pTransform->GetRealViewport();
				double Min[2];
				double Max[2];
				convertproj->mercator2wgs84(rcView.left, rcView.top, Min[0], Min[1]);
				convertproj->mercator2wgs84(rcView.right, rcView.bottom, Max[0], Max[1]);
				double Min84[2];
				double Max84[2];
				Min84[0] = min(Min[0], Max[0]);
				Min84[1] = min(Min[1], Max[1]);
				Max84[0] = max(Min[0], Max[0]);
				Max84[1] = max(Min[1], Max[1]);
				switch (m_CurrentMode)
				{
				case CSymbolizerProjectDoc::MODE::QUERY:
				{
					if (type == -1) return;
					DrawBuildingFootprints(pTransform, pDC, Min84, Max84);
				}
				break;
				case CSymbolizerProjectDoc::MODE::BUILDING:
					DrawNetwork(pTransform, pDC, Min84, Max84);
					break;
				default:
					break;
				}
			}
		}
	}
}

void CSymbolizerProjectDoc::UpDateMBR()
{
	CView* pView;
	CRect cli;
	pView = GetView();
	pView->GetClientRect(&cli);
	int tmp = max(0, m_pTileZoomManager->View.LevelOfDetail);
	int k = (int)pow(2.0, tmp * 1.0) - 1;					// so tile tren 1 dong hoac cot 
	double cl, ct, pl, pt, px1, py1, px2, py2;        // lấy pixel min max của client
	cl = m_pTileZoomManager->View.Left + 256;
	ct = m_pTileZoomManager->View.Top + 256;
	pl = 256 * (m_pTileZoomManager->View.LeftTile + 1);
	pt = 256 * (m_pTileZoomManager->View.TopTile + 1);
	px1 = max(double(0), pl - cl);
	py1 = max(double(0), pt - ct);
	px2 = min(max(double(0), pl + (cli.right - cl)), double((k + 1) * 256));
	py2 = min(max(double(0), pt + (cli.bottom - ct)), double((k + 1) * 256));

	//----------------------------------------------------------------------- convert pixel to wgs84
	double k1, k2, z1, z2;
	TileSystem ts;
	lv = m_pTileZoomManager->View.LevelOfDetail;
	ts.PixelXYToLatLong(px1, py1, lv, k1, k2);
	ts.PixelXYToLatLong(px2, py2, lv, z1, z2);

	double MinMer[2], MaxMer[2];
	MinMer[1] = (std::min)(k1, z1);
	MinMer[0] = (std::min)(k2, z2);
	MaxMer[1] = (std::max)(k1, z1);
	MaxMer[0] = (std::max)(k2, z2);

	//-----------------------------------------------------------------------  set MBR
	if (m_pTileZoomManager)
	{
		convertproj->wgs842mercator(MinMer[0], MinMer[1], k1, k2);
		convertproj->wgs842mercator(MaxMer[0], MaxMer[1], z1, z2);

		GERect2D hcn(k1, k2, z1, z2);
		m_pTransformManager->m_MWTransform.SetMapMBR(hcn);
		m_pTransformManager->m_MWTransform.ZoomFit();
	}
}
//
//static void GetTile(threadpool_context * context, size_t i)
//{
//	string sURL = "https://tile.openstreetmap.org/";
//	sURL += to_string(context->level) + "/" + to_string(context->tileX) + "/" + to_string(context->tileY) + ".png";
//
//	auto r = cpr::Get(cpr::Url{ sURL });
//
//	if (r.status_code == 200)
//	{
//		context->TL->length = r.text.size();
//		char* p = new char[context->TL->length];
//		memcpy(p, r.text.data(), context->TL->length);
//		context->TL->data = (const char*)p;
//	}
//}

//void* GetTile(void* argument)
//{
//	threadpool_context *context = (threadpool_context*)argument;
//	string sURL = "https://tile.openstreetmap.org/";
//	sURL += to_string(context->level) + "/" + to_string(context->tileX) + "/" + to_string(context->tileY) + ".png";
//
//	auto r = cpr::Get(cpr::Url{ sURL });
//
//	shared_ptr<MetaImage> TL;
//
//	if (r.status_code == 200)
//	{
//		TL = make_shared<MetaImage>();
//		TL->length = r.text.size();
//		char* p = new char[TL->length];
//		memcpy(p, r.text.data(), TL->length);
//		TL->data = (const char*)p;
//		TL->type = r.header["content-type"];
//	}
//	//TL->pDoc = (CSymbolizerProjectDoc*)this;
//
//	TileComparator::Key key;
//	key.level = context->level;
//	key.tileX = context->tileX;
//	key.tileY = context->tileY;
//
//	context->pDoc->tile_cache->insert(key, TL);
//	return NULL;
//}

void CSymbolizerProjectDoc::DrawTile(GETransform2D* pTransform, CDC* pDC)
{
	//------------------------------------------------------------------------------------------------------ khai bao 
	CDialogProgress dlg;
	dlg.Create(IDD_DIALOG_PROGRESS);
	dlg.ShowWindow(SW_SHOW);
	dlg.UpdateWindow();
	dlg.CenterWindow();
	MapEngine::GERect2D rcView1 = pTransform->GetRealViewport();
	shared_ptr<MetaImage> tile;
	IStream* pMemStream;
	CComPtr<IStream> stream;
	CImage image;

	int tmp;
	double left, top;

	RECT rcDest;

	CView* pView;


	//----------------------------------------------------------------------------------------------------
	CRect cli;
	pView = GetView();
	pView->GetClientRect(&cli);


	if (!m_pTileZoomManager)
	{
		m_pTileZoomManager = new CTileZoomManager;
		m_pTileZoomManager->View.Left = -247;
		m_pTileZoomManager->View.LeftTile = 417428;
		m_pTileZoomManager->View.Top = -254;
		m_pTileZoomManager->View.TopTile = 246238;
		m_pTileZoomManager->View.LevelOfDetail = 19;
	}
	else
		m_pTileZoomManager->SetTop(m_ActionId, type, cli, up, down, Mouse);


	//--------------------------------------------------------------------------------------------------tinh tile min maxx
	tmp = max(0, m_pTileZoomManager->View.LevelOfDetail);
	int k = (int)pow(2.0, tmp * 1.0) - 1;					// so tile tren 1 dong hoac cot 
	//Get Tile max 
	int n, m, n_max, m_max;
	left = m_pTileZoomManager->View.Left;
	top = m_pTileZoomManager->View.Top;
	n = m_pTileZoomManager->View.TopTile;
	m = m_pTileZoomManager->View.LeftTile;
	n_max = min(int(cli.bottom / 256) + 2, k); //tile max y
	m_max = min(int(cli.right / 256) + 2, k); // tile max x

	int num = (n_max) * (m_max);
	dlg.SetRange(num);

	//--------------------------------------------------------------------------------------------------
	TileComparator::Key key;

	ThreadPool pThreadPool(10);
	IThreadTask* tasks[48]; // thread pool 

	int count = -1;

	for (int y = n; y <= n + n_max; y++)
	{
		for (int x = m; x <= m + m_max; x++)
		{
			key.level = tmp;
			key.tileX = x;
			key.tileY = y;



			if (!tile_cache->exists(key))
			{
				count++;
				shared_ptr<MetaImage> tile = make_shared<MetaImage>();
				threadpool_context context = { tmp, x, y , tile };

				tasks[count] = (IThreadTask*)new Task(context);
				pThreadPool.addTask(tasks[count]);

				/*	tile->length = tasks[count]->t_length;
					tile->data = tasks[count]->t_data;*/

				tile_cache->insert(key, tile);
			}
		}
	}
	pThreadPool.create();
	pThreadPool.start();
	pThreadPool.wait();

	for (int i = 0; i <= count; i++)
		delete tasks[i];

	//getchar();

	for (int y = n; y <= n + n_max; y++)
	{
		for (int x = m; x <= m + m_max; x++)						//(neu hinh nam trong khung thi tai ve)	 
		{
			//----------------------------lay anh ve luu qua memory
			image.Destroy();

			key.level = tmp;
			key.tileX = x;
			key.tileY = y;
			tile = tile_cache->fetch(key);						// lay tile ra tu cache 	

			pMemStream = SHCreateMemStream((const byte*)tile->data, tile->length);			 // ep kieu tile ve anh de draw
			stream.Attach(pMemStream);
			image.Load(stream);

			//--------------------------------------------------------------------- ve anh voi goc tren la (left,top)
			rcDest.left = left;
			rcDest.top = top;
			rcDest.right = left + 256;
			rcDest.bottom = top + 256;
			if (!image.IsNull())
			{
				image.Draw(pDC->GetSafeHdc(), rcDest);
			}
			stream.Release();
			dlg.UpdateUI();
			left += 256;
			if (left >= cli.right) break;
		}

		left = m_pTileZoomManager->View.Left;					// thay doi toa do
		top += 256;
		if (top >= cli.bottom) break;
	}

	//---------------------------------------------------------------------------------------------------- // xoa thread pool 

	dlg.DestroyWindow();
	//_CrtDumpMemoryLeaks();
}
BOOL CSymbolizerProjectDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	m_strDatabaseFile = lpszPathName;

	return TRUE;
}

BOOL CSymbolizerProjectDoc::Start()
{
	if (m_pExtents != NULL)
	{
		delete m_pExtents;
		m_pExtents = NULL;
	}
	ClearData();
	if (Connect())
	{

#ifdef DEBUG
		std::cout << "Connect Success To buildings" << std::endl;

#endif
	}
	else
	{
		int msgBoxId = MessageBox(
			NULL,
			(LPCWSTR)L"Cannot Connect Database",
			(LPCWSTR)L"Warning",
			MB_ICONWARNING | MB_DEFBUTTON2
		);
		return FALSE;
	}

	m_pExtents = new MapEngine::GERect2D(-180, -90, 180, 90);

	//---------------------------------------------------------------------------------------------------- // khoi tao thread pool 

	//----------------------------------------------------------------------------------------------------

	InitMap();
}

BOOL CSymbolizerProjectDoc::Connect()
{
	GDALAllRegister();
	const char* path = "PG:dbname=postgres host=127.0.0.1 port=5432 user=postgres password =1";
	geDS = (GDALDataset*)GDALOpenEx(path, GDAL_OF_VECTOR, NULL, NULL, NULL);
	if (geDS == NULL)
	{
		return FALSE;
	}
	return TRUE;
}

std::vector<OGRGeometry*> CSymbolizerProjectDoc::GetFootPrintWithinBound(double Min[2], double Max[2])
{
	//Query 
	std::vector<OGRGeometry*> result;
	if (geDS != NULL)
	{
		std::string query = "SELECT ST_AsBinary(geom),filename FROM gis_osm_buildings_a_free_1 WHERE ST_Intersects(ST_MakeEnvelope($min_0, $min_1, $max_0, $max_1, 4326), geom) = TRUE";
		StringProcess::Replace(query, "$min_0", std::to_string(Min[0]));
		StringProcess::Replace(query, "$min_1", std::to_string(Min[1]));
		StringProcess::Replace(query, "$max_0", std::to_string(Max[0]));
		StringProcess::Replace(query, "$max_1", std::to_string(Max[1]));
		OGRLayer* layer = geDS->ExecuteSQL(query.c_str(), NULL, NULL);
		if (layer != NULL)
		{
			for (auto& geFeture : layer)
			{
				OGRGeometry* Geometry = geFeture->GetGeometryRef();
				result.push_back(Geometry->clone());
			}
		}
	}
	return result;
}

void CSymbolizerProjectDoc::DrawPolygon(GETransform2D* pTransform, CDC* pDC, OGRPolygon* polygon)
{
	int numberofinnerring = polygon->getNumInteriorRings();
	int a = polygon->getNumInteriorRings();
	OGRLinearRing* poExteriorRing = polygon->getExteriorRing();
	int NumberOfExteriorRingVertices = poExteriorRing->getNumPoints();
	CPoint* Pt;
	Pt = new CPoint[NumberOfExteriorRingVertices];
	TileSystem ts;
	for (int i = 0; i < NumberOfExteriorRingVertices; ++i)
	{
		OGRPoint pt;
		double x, y;
		int pixelX, pixelY;
		poExteriorRing->getPoint(i, &pt);

		convertproj->wgs842mercator(pt.getX(), pt.getY(), x, y);
		MapEngine::GEPoint2D p(x, y);
		MapEngine::GEPoint2D vp;
		pTransform->RP2VP(p, vp);
		Pt[i] = CPoint((int)vp.x, (int)vp.y);

	}
	//-----------------------------------------------------------------------------
	pDC->Polygon(Pt, NumberOfExteriorRingVertices);
	delete[]Pt;
	Pt = NULL;
	//-----------------------------------------------------------------------------
	for (int i = 0; i < numberofinnerring; ++i)
	{
		OGRLinearRing* poInnerring = polygon->getInteriorRing(i);
		int numberofInneringVertices = poInnerring->getNumPoints();
		CPoint* Pt;
		Pt = new CPoint[numberofInneringVertices];
		for (int i = 0; i < numberofInneringVertices; ++i)
		{
			OGRPoint pt;
			double x, y;
			int pixelX, pixelY;
			poInnerring->getPoint(i, &pt);

			convertproj->wgs842mercator(pt.getX(), pt.getY(), x, y);
			MapEngine::GEPoint2D p(x, y);
			MapEngine::GEPoint2D vp;
			pTransform->RP2VP(p, vp);
			Pt[i] = CPoint((int)vp.x, (int)vp.y);
		}
		pDC->Polygon(Pt, numberofInneringVertices);
		delete[]Pt;
		Pt = NULL;
	}
}

void CSymbolizerProjectDoc::DrawGeom(GETransform2D* pTransform, CDC* pDC, OGRGeometry* Geometry)
{
	if (wkbFlatten(Geometry->getGeometryType()) == wkbPolygon)
	{
		OGRPolygon* polygon = Geometry->toPolygon();
		DrawPolygon(pTransform, pDC, polygon);
	}
	if (wkbFlatten(Geometry->getGeometryType()) == wkbMultiPolygon)
	{
		OGRMultiPolygon* multipolygon = Geometry->toMultiPolygon();
		int numberofgeometries = multipolygon->getNumGeometries();
		for (int i = 0; i < numberofgeometries; ++i)
		{
			OGRGeometry* poPolygonGeometry = multipolygon->getGeometryRef(i);
			OGRPolygon* polygon = poPolygonGeometry->toPolygon();
			DrawPolygon(pTransform, pDC, polygon);
		}
	}
}

std::string CSymbolizerProjectDoc::GetMetadataWithinBound(double Min[2], double Max[2])
{
	std::string result;
	if (geDS != NULL)
	{
		std::string query = "SELECT filename FROM gis_osm_buildings_a_free_1 WHERE ST_Intersects(ST_MakeEnvelope($min_0, $min_1, $max_0, $max_1, 4326), geom) = TRUE";
		StringProcess::Replace(query, "$min_0", std::to_string(Min[0]));
		StringProcess::Replace(query, "$min_1", std::to_string(Min[1]));
		StringProcess::Replace(query, "$max_0", std::to_string(Max[0]));
		StringProcess::Replace(query, "$max_1", std::to_string(Max[1]));
		OGRLayer* layer = geDS->ExecuteSQL(query.c_str(), NULL, NULL);
		if (layer != NULL)
		{
			for (auto& geFeture : layer)
			{
				result = geFeture->GetFieldAsString("filename");
			}
		}
	}
	return result;
}

void CSymbolizerProjectDoc::DrawBuildingFootprints(GETransform2D* pTransform, CDC* pDC, double Min[2], double Max[2])
{
	pDC->SelectObject(GetStockObject(NULL_BRUSH));
	pDC->SelectObject(footprintpen);
	std::vector<OGRGeometry*> result = GetFootPrintWithinBound(Min, Max);
	if (result.size() != 0)
	{
		for (OGRGeometry* geom : result)
		{
			DrawGeom(pTransform, pDC, geom);
		}
	}
}

void CSymbolizerProjectDoc::calcVertexes(MapEngine::GEPoint2D  startP, MapEngine::GEPoint2D  endP, MapEngine::GEPoint2D& p1, MapEngine::GEPoint2D& p2)
{
	double arrow_degrees = PI / 6;
	double angle = atan2(endP.y - startP.y, endP.x - startP.x) + PI;
	double arrow_lenght = 12;

	p1.x = endP.x + arrow_lenght * cos(angle - arrow_degrees);
	p1.y = endP.y + arrow_lenght * sin(angle - arrow_degrees);
	p2.x = endP.x + arrow_lenght * cos(angle + arrow_degrees);
	p2.y = endP.y + arrow_lenght * sin(angle + arrow_degrees);
}

void CSymbolizerProjectDoc::DrawArrow(CDC* pDC, GETransform2D* pTransform, MapEngine::GEPoint2D  dau, MapEngine::GEPoint2D  cuoi)
{
	/*CPen redPendd(PS_DASH, 2, RGB(255, 0, 0));
	pDC->SelectObject(redPendd);*/

	MapEngine::GEPoint2D  giua, duoi1, duoi2;

	giua.x = abs(dau.x - cuoi.x) / 2 + min(dau.x, cuoi.x);
	giua.y = abs(dau.y - cuoi.y) / 2 + min(dau.y, cuoi.y);

	calcVertexes(dau, giua, duoi1, duoi2);

	pDC->MoveTo((giua.x), (giua.y));
	pDC->LineTo((duoi2.x), (duoi2.y));

	pDC->MoveTo((giua.x), (giua.y));
	pDC->LineTo((duoi1.x), (duoi1.y));
}

void CSymbolizerProjectDoc::DrawNetwork(GETransform2D* pTransform, CDC* pDC, double Min[2], double Max[2])
{
	if (!m_Building.IsNull())
	{
		//DRAW EDGE 
		std::vector<Edge*> edges = m_Building.GetEdgeWithinBound(Min, Max);
		pDC->SelectObject(edgepen);
		if (edges.size() != 0)
		{
			for (auto edge : edges)
			{
				double lon1, lat1, lon2, lat2;
				convertproj->wgs842mercator(edge->nodes.first->lon, edge->nodes.first->lat, lon1, lat1);
				convertproj->wgs842mercator(edge->nodes.second->lon, edge->nodes.second->lat, lon2, lat2);
				MapEngine::GEPoint2D p1(lon1, lat1);
				MapEngine::GEPoint2D p2(lon2, lat2);
				MapEngine::GEPoint2D vp1, vp2;
				pTransform->RP2VP(p1, vp1);
				pTransform->RP2VP(p2, vp2);
				int x1 = (int)(vp1.x + 0.5);
				int y1 = (int)(vp1.y + 0.5);
				int x2 = (int)(vp2.x + 0.5);
				int y2 = (int)(vp2.y + 0.5);
				pDC->MoveTo(x1, y1);
				pDC->LineTo(x2, y2);
			}
		}
		//DRAW NODE 
		std::vector<Node*> nodes = m_Building.GetNodeWithinBound(Min, Max);
		pDC->SelectObject(nodepen);
		pDC->SelectObject(nodebrush);
		if (nodes.size() != 0)
		{
			for (auto node : nodes)
			{
				double lon, lat;
				convertproj->wgs842mercator(node->lon, node->lat, lon, lat);
				MapEngine::GEPoint2D p(lon, lat);
				MapEngine::GEPoint2D vp;
				pTransform->RP2VP(p, vp);
				int x = (int)(vp.x + 0.5);
				int y = (int)(vp.y + 0.5);
				CString  path = _T("res\\Img\\");
				pDC->Ellipse(x - 3, y - 3, x + 3, y + 3);
				if (node->type == Node::Type::WC_FEMALE)
				{
					DrawIMG(path + _T("nu.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::WC_MALE)
				{
					DrawIMG(path + _T("nam.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::CAFE)
				{
					DrawIMG(path + _T("cafe.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::BAR)
				{
					DrawIMG(path + _T("bar.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::CASINO)
				{
					DrawIMG(path + _T("casino.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::CINEMA)
				{
					DrawIMG(path + _T("cinema.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::FAST_FOOD)
				{
					DrawIMG(path + _T("fastfood.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::ICE_CREAM)
				{
					DrawIMG(path + _T("icecream.png"), x, y, 20, pDC);

				}
				if (node->type == Node::Type::LIBRARY)
				{
					DrawIMG(path + _T("library.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::RESTAURANT)
				{
					DrawIMG(path + _T("restaurant.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::ELEVATOR)
				{
					DrawIMG(path + _T("elevator.png"), x, y, 20, pDC);
				}
				if (node->type == Node::Type::STAIR)
				{
					DrawIMG(path + _T("stairs.png"), x, y, 20, pDC);
				}
			}
		}
		//DRAW PATH
		CPen colorPath;

		int r, g, b;
		r = GetRValue(floors.at(m_Building.m_currentfloor)->colorPath);
		g = GetGValue(floors.at(m_Building.m_currentfloor)->colorPath);
		b = GetBValue(floors.at(m_Building.m_currentfloor)->colorPath);
		colorPath.CreatePen(PS_SOLID, floors.at(m_Building.m_currentfloor - 1)->widthPath, RGB(r, g, b));
		pDC->SelectObject(colorPath);
		std::vector<Node*> _path = m_Building.GetPathInFloor(Min, Max);
		if (!_path.empty())
		{
			for (int i = 0; i < _path.size() - 1; i++)
			{
				double lon1, lat1, lon2, lat2;
				convertproj->wgs842mercator(_path.at(i)->lon, _path.at(i)->lat, lon1, lat1);
				convertproj->wgs842mercator(_path.at(i + 1)->lon, _path.at(i + 1)->lat, lon2, lat2);

				MapEngine::GEPoint2D p1(lon1, lat1);
				MapEngine::GEPoint2D p2(lon2, lat2);

				MapEngine::GEPoint2D vp1, vp2;
				pTransform->RP2VP(p1, vp1);
				pTransform->RP2VP(p2, vp2);
				int x1 = (int)(vp1.x + 0.5);
				int y1 = (int)(vp1.y + 0.5);
				int x2 = (int)(vp2.x + 0.5);
				int y2 = (int)(vp2.y + 0.5);

				pDC->MoveTo(x1, y1);
				pDC->LineTo(x2, y2);

				MapEngine::GEPoint2D  pd(x1, y1);
				MapEngine::GEPoint2D  pc(x2, y2);
				DrawArrow(pDC, pTransform, pd, pc);
			}
		}
		//DRAW SELECT
		pDC->SelectObject(pathpen);
		pDC->SelectObject(pathbrush);
		if (m_Building._ToPoint != NULL)
		{
			Node* p = m_Building._ToPoint;
			double lon, lat;
			if (p->floor == m_Building.m_currentfloor)
			{
				convertproj->wgs842mercator(p->lon, p->lat, lon, lat);
				MapEngine::GEPoint2D p(lon, lat);
				MapEngine::GEPoint2D vp;
				pTransform->RP2VP(p, vp);
				int x = (int)(vp.x + 0.5);
				int y = (int)(vp.y + 0.5);
				pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
			}
		}
		if (m_Building._FromPoint != NULL)
		{
			Node* p = m_Building._FromPoint;
			double lon, lat;
			if (p->floor == m_Building.m_currentfloor)
			{
				convertproj->wgs842mercator(p->lon, p->lat, lon, lat);
				MapEngine::GEPoint2D p(lon, lat);
				MapEngine::GEPoint2D vp;
				pTransform->RP2VP(p, vp);
				int x = (int)(vp.x + 0.5);
				int y = (int)(vp.y + 0.5);
				pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
			}
		}
		//Draw Poi 
		if (m_idpoi != -1)
		{
			pDC->SelectObject(poipen);
			MapEngine::GEPoint2D vp;
			Node* p = m_Building.m_pNode->at(m_idpoi - 1);
			if (p->floor != m_Building.m_currentfloor)
				return;
			double lon, lat;
			convertproj->wgs842mercator(p->lon, p->lat, lon, lat);
			pTransform->RP2VP(lon, lat, vp);
			int x = (int)(vp.x + 0.5);
			int y = (int)(vp.y + 0.5);
			pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
		}
		if (m_drawPath != -1)
		{
			for (int i = m_PathSelect->index; i < m_PathSelect->index + m_PathSelect->numP; i++)
			{
				pDC->SelectObject(poipen);
				double lon1, lat1, lon2, lat2;
				convertproj->wgs842mercator(m_Building.m_pPath[i]->lon, m_Building.m_pPath[i]->lat, lon1, lat1);
				convertproj->wgs842mercator(m_Building.m_pPath[i + 1]->lon, m_Building.m_pPath[i + 1]->lat, lon2, lat2);
				MapEngine::GEPoint2D p1(lon1, lat1);
				MapEngine::GEPoint2D p2(lon2, lat2);
				MapEngine::GEPoint2D vp1, vp2;
				pTransform->RP2VP(p1, vp1);
				pTransform->RP2VP(p2, vp2);
				int x1 = (int)(vp1.x + 0.5);
				int y1 = (int)(vp1.y + 0.5);
				int x2 = (int)(vp2.x + 0.5);
				int y2 = (int)(vp2.y + 0.5);
				pDC->MoveTo(x1, y1);
				pDC->LineTo(x2, y2);
			}
		}
	}
}

bool CSymbolizerProjectDoc::OnQueryClick(CPoint p, double Min[2], double Max[2])
{
	std::string metadata = GetMetadataWithinBound(Min, Max);
	if (metadata.empty())
	{
		return false;
	}
	return OpenNetWork(metadata);
}

bool CSymbolizerProjectDoc::OnNetWorkClick(CPoint p, double Min[2], double Max[2])
{
	bool check = false;
	if (m_To || m_From)
	{
		m_Building.m_pPath.clear();
		if (m_Building._To == NULL && m_Building._From == NULL)
		{
			m_Building._ToPoint = NULL;
			m_Building._FromPoint = NULL;
		}
		check = GetNodeClick(p);
		if (!check)
		{
			check = GetEdgeClick(p);
		}
		if (m_Building._To != NULL)
		{
			m_To = false;
			m_Building._ToPoint = m_Building._To;
		}
		if (m_Building._From != NULL)
		{
			m_From = false;
			m_Building._FromPoint = m_Building._From;
		}
		if (m_Building._To != NULL && m_Building._From != NULL)
		{
			FindPath();
		}
	}
	return check;
}

GEPoint2D CSymbolizerProjectDoc::PointLineDistance(GEPoint2D p1, GEPoint2D p2, GEPoint2D p3)
{
	GEPoint2D v1, v2, v3, v2d, v3p2;
	real64 l1, l2, l3;

	v1 = GEPoint2D(p1.x - p2.x, p1.y - p2.y);
	v2 = GEPoint2D(p3.x - p2.x, p3.y - p2.y);

	l1 = Distance(p2, p1);
	l2 = Distance(p2, p3);

	v2d.x = v2.x / l2;
	v2d.y = v2.y / l2;

	real64 dp = v1.x * v2.x + v1.y * v2.y;
	l3 = dp / l2;
	v3 = GEPoint2D(l3 * v2d.x, l3 * v2d.y);
	l3 = sqrt(v3.x * v3.x + v3.y * v3.y);

	v3p2.x = p2.x + v3.x;
	v3p2.y = p2.y + v3.y;

	return v3p2;
}

bool CSymbolizerProjectDoc::GetEdgeClick(CPoint point)
{
	GETransform2D* pTransform = m_pTransformManager->GetMainTransform();
	CDC* pDC = m_pTransformManager->GetMainDC();
	BOOL result = false;
	GEPoint2D res;
	double Min[2];
	double Max[2];
	Edge* pEdge, * _edge = NULL;
	real64 tmp = 1000;
	GEPoint2D rP, wP;
	pTransform->VP2RP(point.x, point.y, rP);
	convertproj->mercator2wgs84(rP.x, rP.y, wP.x, wP.y);
	Min[0] = Max[0] = wP.x;
	Min[1] = Max[1] = wP.y;

	RTree<Edge*, double, 2>::Iterator it(Min, Max);
	m_Building.m_pRTEdge->GetFirst(it);
	while (!it.IsNull())
	{
		pEdge = *it;
		GEPoint2D A = GEPoint2D(pEdge->nodes.first->lon, pEdge->nodes.first->lat);
		GEPoint2D B = GEPoint2D(pEdge->nodes.second->lon, pEdge->nodes.second->lat);
		GEPoint2D pH = PointLineDistance(wP, A, B);
		GEPoint2D mP, vPH;
		convertproj->wgs842mercator(pH.x, pH.y, mP.x, mP.y);
		pTransform->RP2VP(mP, vPH);
		real64 distView = Distance(vPH, GEPoint2D(point.x, point.y));
		real64 dist = Distance(pH, wP);
		if (dist < tmp && distView < 10 && m_Building.m_currentfloor == pEdge->floor)
		{
			result = true;
			tmp = dist;
			res = pH;
			_edge = pEdge;
		}
		m_Building.m_pRTEdge->GetNext(it);
	}
	if (result)
	{
		int stop = 3;
		Node* p = new Node(-_edge->id - 1, m_Building.m_currentfloor, res.x, res.y);
		p->type = Node::Type::CLICK;
		Node::Adj adj;
		adj.edge = _edge->id;
		Node* pn1 = m_Building.m_pNode->at(_edge->nodes.first->id - 1);
		adj.node = pn1;
		p->m_pAdj->push_back(adj);
		Node* pn2 = m_Building.m_pNode->at(_edge->nodes.second->id - 1);
		adj.node = pn2;
		p->m_pAdj->push_back(adj);
		if (m_To)
		{
			m_Building._To = p;
		}
		else
		{
			m_Building._From = p;
		}
	}
	return result;
}

bool CSymbolizerProjectDoc::GetNodeClick(CPoint point)
{
	GETransform2D* pTransform = m_pTransformManager->GetMainTransform();
	CDC* pDC = m_pTransformManager->GetMainDC();
	Node* pNode = NULL;
	double Min[2], Max[2];
	MapEngine::GEPoint2D vP1, vP2, p1, p2;

	vP1.x = point.x - 5;
	vP1.y = point.y - 5;
	vP2.x = point.x + 5;
	vP2.y = point.y + 5;

	pTransform->VP2RP(vP1, p1);
	pTransform->VP2RP(vP2, p2);
	convertproj->mercator2wgs84(p1.x, p1.y, vP1.x, vP1.y);
	convertproj->mercator2wgs84(p2.x, p2.y, vP2.x, vP2.y);
	Min[0] = min(vP1.x, vP2.x);
	Min[1] = min(vP1.y, vP2.y);
	Max[0] = max(vP1.x, vP2.x);
	Max[1] = max(vP1.y, vP2.y);

	if (m_Building.m_pRTNode != NULL)
	{
		RTree<Node*, double, 2>::Iterator it(Min, Max);
		m_Building.m_pRTNode->GetFirst(it);
		while (!it.IsNull())
		{
			pNode = *it;
			if (pNode->floor == m_Building.m_currentfloor)
			{
				if (m_To)
				{
					m_Building._To = pNode;
				}
				else
				{
					m_Building._From = pNode;
				}
				return true;
			}
			m_Building.m_pRTNode->GetNext(it);
		}
	}
	return false;
}

BOOL CSymbolizerProjectDoc::OnClick(CPoint p)
{
	GETransform2D* pTransform = m_pTransformManager->GetMainTransform();
	MapEngine::GEPoint2D _p((double)p.x, (double)p.y);
	MapEngine::GEPoint2D pMin((double)((double)p.x - m_MouseSize), (double)((double)p.y - m_MouseSize));
	MapEngine::GEPoint2D pMax((double)((double)p.x + m_MouseSize), (double)((double)p.y + m_MouseSize));
	MapEngine::GEPoint2D rpMin;
	MapEngine::GEPoint2D rpMax;
	MapEngine::GEPoint2D rp;
	double min;
	pTransform->VP2RP(pMin, rpMin);
	pTransform->VP2RP(pMax, rpMax);
	pTransform->VP2RP(_p, rp);
	double MinM[2];
	double MaxM[2];
	convertproj->mercator2wgs84((std::min)(rpMin.x, rpMax.x), (std::min)(rpMin.y, rpMax.y), MinM[0], MinM[1]);
	convertproj->mercator2wgs84((std::max)(rpMin.x, rpMax.x), (std::max)(rpMin.y, rpMax.y), MaxM[0], MaxM[1]);
	double Min[2];
	double Max[2];
	Min[0] = (std::min)(MinM[0], MaxM[0]);
	Min[1] = (std::min)(MinM[1], MaxM[1]);
	Max[0] = (std::max)(MinM[0], MaxM[0]);
	Max[1] = (std::max)(MinM[1], MaxM[1]);
	//QUERY
	switch (m_CurrentMode)
	{
	case CSymbolizerProjectDoc::MODE::QUERY:
	{
		return OnQueryClick(p, Min, Max);
	}
	break;
	case CSymbolizerProjectDoc::MODE::BUILDING:
	{
		return OnNetWorkClick(p, Min, Max);
	}
	break;
	default:
		return false;
		break;
	}
}

double CSymbolizerProjectDoc::getDistanceHaversin2(double lat1, double lon1, double lat2, double lon2)
{
	// distance between latitudes
	// and longitudes
	double dLat = (lat2 - lat1) *
		M_PI / 180.0;
	double dLon = (lon2 - lon1) *
		M_PI / 180.0;

	// convert to radians
	lat1 = (lat1)*M_PI / 180.0;
	lat2 = (lat2)*M_PI / 180.0;

	// apply formulae
	double a = pow(sin(dLat / 2), 2) +
		pow(sin(dLon / 2), 2) *
		cos(lat1) * cos(lat2);
	double rad = 6371;
	double c = 2 * asin(sqrt(a));
	return rad * c;
}

double CSymbolizerProjectDoc::Distance2Point(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) +
		pow(y2 - y1, 2) * 1.0);
}

double CSymbolizerProjectDoc::CalDistancePoint2Edge(MapEngine::GEPoint2D p_A, MapEngine::GEPoint2D p_B, MapEngine::GEPoint2D p_C, MapEngine::GEPoint2D& projection_P)
{
	Vector v1(p_A, p_C);
	Vector v2(p_A, p_B);
	Vector v3;
	v3.p1 = p_A;

	v2.dx = v2.x / v2.length;
	v2.dy = v2.y / v2.length;

	//dot product 

	double dp = v1.x * v2.x + v1.y * v2.y;
	double length = dp / v2.length;

	v3.x = length * v2.dx;
	v3.y = length * v2.dy;

	v3.length = sqrt(v3.x * v3.x + v3.y * v3.y);
	v3.p2.x = v3.p1.x + v3.x;
	v3.p2.y = v3.p1.y + v3.y;

	projection_P = v3.p2;

	double d;

	if (dp < 0)
	{
		d = -1;
	}
	else
	{
		if (v3.length > v2.length)
		{
			d = -1;
		}
		else
		{
			double dx = v1.x - v3.x;
			double dy = v1.y - v3.y;
			d = sqrt(dx * dx + dy * dy);
		}
	}

	return d;
}

void CSymbolizerProjectDoc::OnMouseMoveBuilding(CPoint p, CDC* pDC)
{
	GETransform2D* pTransform = m_pTransformManager->GetMainTransform();
	MapEngine::GEPoint2D pMin((double)((double)p.x - m_MouseSize), (double)((double)p.y - m_MouseSize));
	MapEngine::GEPoint2D pMax((double)((double)p.x + m_MouseSize), (double)((double)p.y + m_MouseSize));
	MapEngine::GEPoint2D rpMin;
	MapEngine::GEPoint2D rpMax;
	MapEngine::GEPoint2D rpMecator;
	MapEngine::GEPoint2D rp;
	double min;
	pTransform->VP2RP(pMin, rpMin);
	pTransform->VP2RP(pMax, rpMax);
	pTransform->VP2RP(p.x, p.y, rpMecator);
	double MinM[2];
	double MaxM[2];
	convertproj->mercator2wgs84(rpMecator.x, rpMecator.y, rp.x, rp.y);
	convertproj->mercator2wgs84((std::min)(rpMin.x, rpMax.x), (std::min)(rpMin.y, rpMax.y), MinM[0], MinM[1]);
	convertproj->mercator2wgs84((std::max)(rpMin.x, rpMax.x), (std::max)(rpMin.y, rpMax.y), MaxM[0], MaxM[1]);
	double Min[2];
	double Max[2];
	Min[0] = (std::min)(MinM[0], MaxM[0]);
	Min[1] = (std::min)(MinM[1], MaxM[1]);
	Max[0] = (std::max)(MinM[0], MaxM[0]);
	Max[1] = (std::max)(MinM[1], MaxM[1]);

	MMB = 0;
	ms = p;
	//NODE 
	std::vector<Node*> nodes = m_Building.GetNodeWithinBound(Min, Max);
	if (nodes.size() != 0)
	{
		min = (std::numeric_limits<double>::max)();
		Node* pnodemin = NULL;
		for (Node* pnode : nodes)
		{
			MapEngine::GEPoint2D pt;
			convertproj->wgs842mercator(pnode->lon, pnode->lat, pt.x, pt.y);
			MapEngine::GEPoint2D vp;
			pTransform->RP2VP(pt, vp);
			double disthaversine = getDistanceHaversin2(pnode->lat, pnode->lon, rp.y, rp.x);
			double distpytago = Distance2Point(vp.x, vp.y, p.x, p.y);
			if (disthaversine < min && distpytago <= m_MouseSelect)
			{
				min = disthaversine;
				pnodemin = pnode;
			}
		}
		//Draw node 
		if (pnodemin != NULL)
		{
			MMB = 1;
			pDC->SelectObject(footprintpen);
			MapEngine::GEPoint2D pt;
			MapEngine::GEPoint2D vp;
			convertproj->wgs842mercator(pnodemin->lon, pnodemin->lat, pt.x, pt.y);
			pTransform->RP2VP(pt, vp);
			int x = (int)(vp.x + 0.5);
			int y = (int)(vp.y + 0.5);
			pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
			std::string str = "";
			switch (pnodemin->type)
			{
			case Node::Type::WC_FEMALE:
				str = "WC WOMAN"; break;
			case Node::Type::WC_MALE:
				str = "WC MAN"; break;
			case Node::Type::CAFE:
				str = "CAFE"; break;
			case Node::Type::BAR:
				str = "BAR"; break;
			case Node::Type::CASINO:
				str = "CASINO"; break;
			case Node::Type::CINEMA:
				str = "CINEMA"; break;
			case Node::Type::FAST_FOOD:
				str = "FAST_FOOD"; break;
			case Node::Type::ICE_CREAM:
				str = "ICE_CREAM"; break;
			case Node::Type::LIBRARY:
				str = "LIBRARY"; break;
			case Node::Type::RESTAURANT:
				str = "RESTAURANT"; break;
			default:
				break;
			}
			if (str == "") str = "POS " + std::to_string(pnodemin->id);
			CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();
			mainFrame->m_wndOutput.FillDebugWindow(str, pnodemin->lon, pnodemin->lat);
		}
	}
	else
	{
		//EDGE  
		std::vector<Edge*> edges = m_Building.GetEdgeWithinBound(Min, Max);
		if (edges.size() != 0)
		{
			min = (std::numeric_limits<double>::max)();
			Edge* pedgemin = NULL;
			for (Edge* pedge : edges)
			{
				MapEngine::GEPoint2D pt1(pedge->nodes.first->lon, pedge->nodes.first->lat);
				MapEngine::GEPoint2D pt2(pedge->nodes.second->lon, pedge->nodes.second->lat);
				MapEngine::GEPoint2D ptproj, ptprojmecator, vpptroj;
				double dist = CalDistancePoint2Edge(pt1, pt2, rp, ptproj);
				convertproj->wgs842mercator(ptproj.x, ptproj.y, ptprojmecator.x, ptprojmecator.y);
				pTransform->RP2VP(ptprojmecator, vpptroj);
				double distpytago = Distance2Point(vpptroj.x, vpptroj.y, p.x, p.y);
				if (dist < min && distpytago <= m_MouseSelect)
				{
					min = dist;
					pedgemin = pedge;
				}
			}
			//DRAW EDGE 
			if (pedgemin != NULL)
			{
				MMB = 1;
				pDC->SelectObject(footprintpen);
				MapEngine::GEPoint2D pt1, pt2, vp1, vp2;
				convertproj->wgs842mercator(pedgemin->nodes.first->lon, pedgemin->nodes.first->lat, pt1.x, pt1.y);
				convertproj->wgs842mercator(pedgemin->nodes.second->lon, pedgemin->nodes.second->lat, pt2.x, pt2.y);
				pTransform->RP2VP(pt1, vp1);
				pTransform->RP2VP(pt2, vp2);
				pDC->MoveTo((int)(vp1.x + 0.5), (int)(vp1.y + 0.5));
				pDC->LineTo((int)(vp2.x + 0.5), (int)(vp2.y + 0.5));
			}
		}
	}
}

BOOL CSymbolizerProjectDoc::OpenNetWork(std::string filename)
{
	m_CurrentMode = MODE::BUILDING;
	if (!m_Building.IsNull())
	{
		m_Building.Exit();
	}
	m_Building.Initialize();
	std::string path = "res\\data";
	std::string pathfile = path + "\\" + filename;
	try
	{
		osmium::io::File input_file{ pathfile };
		osmium::io::Reader reader{ input_file };
		osmium::apply(reader, m_Building);
		if (m_pExtents != NULL)
		{
			delete m_pExtents;
			m_pExtents = NULL;
		}
		double Min[2];
		double Max[2];
		convertproj->wgs842mercator(m_Building.BMin[0], m_Building.BMin[1], Min[0], Min[1]);
		convertproj->wgs842mercator(m_Building.BMax[0], m_Building.BMax[1], Max[0], Max[1]);
		m_pExtents = new MapEngine::GERect2D(Min[0], Min[1], Max[0], Max[1]);
		CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
		pMainWnd->m_wndClassView.FillData(m_Building.m_numfloor);
		for (int i = 0; i <= m_Building.m_numfloor; i++) {
			Floor* tmp = new Floor();
			tmp->colorPath = 0x000000FF;
			tmp->widthPath = 2;
			floors.push_back(tmp);
		}
#ifdef DEBUG
		std::cout << "DOC FILE THANH CONG ..." << std::endl;
#endif
	}
	catch (const std::exception& e)
	{
#ifdef DEBUG
		std::cerr << "exception: " << e.what() << std::endl;
#endif
		return FALSE;
	}
	return TRUE;
}

void CSymbolizerProjectDoc::ExitBuildingsMode()
{
	if (m_CurrentMode != MODE::BUILDING)
	{
		return;
	}
	m_Building.Exit();
	m_CurrentMode = MODE::QUERY;
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	pMainWnd->m_wndClassView.FillClassView();
}

void CSymbolizerProjectDoc::SelectFloor(int floor)
{
	if (m_CurrentMode != MODE::BUILDING)
	{
		return;
	}
	if (m_Building.m_currentfloor != floor)
	{
		m_Building.m_currentfloor = floor;
	}
}

void CSymbolizerProjectDoc::ChangeStyleFloor(COLORREF pen, int width)
{
	floors.at(m_Building.m_currentfloor)->colorPath = pen;
	floors.at(m_Building.m_currentfloor)->widthPath = width;
}

void CSymbolizerProjectDoc::JumpToPoi()
{
	m_idpoi = m_idrclick;
	Node* node = m_Building.m_pNode->at(m_idpoi - 1);
	m_Building.m_currentfloor = node->floor;
	MapEngine::GEPoint2D p(node->lon, node->lat);
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	pMainWnd->m_wndClassView.m_wndClassView.UpdateUI(m_Building.m_currentfloor);
	JumpToCenter(p);
}

void CSymbolizerProjectDoc::JumpToCenter(MapEngine::GEPoint2D p)
{
	GETransform2D* pTransform = m_pTransformManager->GetMainTransform();
	MapEngine::GERect2D rcView = pTransform->GetRealViewport();
	double Min[2];
	double Max[2];
	convertproj->mercator2wgs84(rcView.left, rcView.top, Min[0], Min[1]);
	convertproj->mercator2wgs84(rcView.right, rcView.bottom, Max[0], Max[1]);
	double Min84[2];
	double Max84[2];
	Min84[0] = (std::min)(Min[0], Max[0]);
	Min84[1] = (std::min)(Min[1], Max[1]);
	Max84[0] = (std::max)(Min[0], Max[0]);
	Max84[1] = (std::max)(Min[1], Max[1]);
	double dX = Max84[0] - Min84[0];
	double dY = Max84[1] - Min84[1];
	double MinR[2];
	double MaxR[2];
	MinR[0] = p.x - dX / 2;
	MinR[1] = p.y - dY / 2;
	MaxR[0] = p.x + dX / 2;
	MaxR[1] = p.y + dY / 2;
	convertproj->wgs842mercator(MinR[0], MinR[1], MinR[0], MinR[1]);
	convertproj->wgs842mercator(MaxR[0], MaxR[1], MaxR[0], MaxR[1]);
	MapEngine::GERect2D rect(MinR[0], MinR[1], MaxR[0], MaxR[1]);
	m_pTransformManager->m_MWTransform.SetMapMBR(rect);
	m_pTransformManager->m_MWTransform.ZoomFit();
}

void CSymbolizerProjectDoc::SetFrom()
{
	m_idfrom = m_idrclick;
	Node* node = m_Building.m_pNode->at(m_idfrom - 1);
	m_Building.m_currentfloor = node->floor;
	MapEngine::GEPoint2D p(node->lon, node->lat);
	m_Building._From = node;
	m_Building._FromPoint = node;
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	pMainWnd->m_wndClassView.m_wndClassView.UpdateUI(m_Building.m_currentfloor);
	if (m_Building._To != NULL && m_Building._From != NULL)
	{
		FindPath();
	}
	JumpToCenter(p);
}

void CSymbolizerProjectDoc::SetTo()
{
	m_idto = m_idrclick;
	Node* node = m_Building.m_pNode->at(m_idto - 1);
	m_Building.m_currentfloor = node->floor;
	MapEngine::GEPoint2D p(node->lon, node->lat);
	m_Building._To = node;
	m_Building._ToPoint = node;
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	pMainWnd->m_wndClassView.m_wndClassView.UpdateUI(m_Building.m_currentfloor);
	if (m_Building._To != NULL && m_Building._From != NULL)
	{
		FindPath();
	}
	JumpToCenter(p);
}

void CSymbolizerProjectDoc::JumpToPath(ViewP* path)
{
	if (path->direction != ViewP::Direction::LOCATION)
	{
		m_drawPath = 1;
		m_PathSelect = path;
	}
	else m_drawPath = -1;
	if (path->index != -1)
	{
		m_Building.m_currentfloor = path->floor;
		Node* node = m_Building.m_pPath.at(path->index);
		MapEngine::GEPoint2D p(node->lon, node->lat);
		JumpToCenter(p);
	}

}

void CSymbolizerProjectDoc::DrawIMG(CString path, int x, int y, int size, CDC* pDC)
{
	CImage img;
	img.Load(path);
	CRect rect(x - int(size / 2) - 1, y - int(size / 2) - 1, x - int(size / 2) + size + 1, y - int(size / 2) + size + 1);
	img.Draw(pDC->GetSafeHdc(), rect);
}

void CSymbolizerProjectDoc::DrawNetWorkWithoutBackground(CDC* pDC)
{
	GETransform2D* pTransform = m_pTransformManager->GetMainTransform();
	MapEngine::GERect2D rcView = pTransform->GetRealViewport();
	double Min[2];
	double Max[2];
	convertproj->mercator2wgs84(rcView.left, rcView.top, Min[0], Min[1]);
	convertproj->mercator2wgs84(rcView.right, rcView.bottom, Max[0], Max[1]);
	double Min84[2];
	double Max84[2];
	Min84[0] = min(Min[0], Max[0]);
	Min84[1] = min(Min[1], Max[1]);
	Max84[0] = max(Min[0], Max[0]);
	Max84[1] = max(Min[1], Max[1]);
	DrawNetwork(pTransform, pDC, Min, Max);
}