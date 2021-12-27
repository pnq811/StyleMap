
// IndoorNavigationView.cpp : implementation of the CSymbolizerProjectView class
//
#pragma once
#include "stdafx.h"
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SymbolizerProject.h"
#endif

#include "SymbolizerProjectDoc.h"
#include "SymbolizerProjectView.h"
#include "DlgStyleFloor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#endif

#include "Relations.h" // dialog relations

// CSymbolizerProjectView

IMPLEMENT_DYNCREATE(CSymbolizerProjectView, CView)

BEGIN_MESSAGE_MAP(CSymbolizerProjectView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSymbolizerProjectView::OnFilePrintPreview)
	ON_COMMAND_RANGE(ID_ZOOM_ALL, ID_ZOOM_CENTER, &CSymbolizerProjectView::OnZoom)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ZOOM_ALL, ID_ZOOM_CENTER, &CSymbolizerProjectView::OnUpdateZoom)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	//ON_COMMAND(ID_BUILDINGS_EXIT, &CSymbolizerProjectView::OnBuildingsExit)
	ON_COMMAND(ID_BUILDING_EXIT, &CSymbolizerProjectView::OnBuildingExit)
	ON_COMMAND(ID_SELECT_POINT, &CSymbolizerProjectView::OnSelectPoint)
	ON_UPDATE_COMMAND_UI(ID_SELECT_POINT, &CSymbolizerProjectView::OnUpdateSelectPoint)
	ON_COMMAND(ID_FLOOROPTION_STYLEFLOOR, &CSymbolizerProjectView::OnFlooroptionStylefloor)
	ON_COMMAND(ID_POIOPTIONS_VIEW, &CSymbolizerProjectView::OnPoioptionsView)
	ON_COMMAND(ID_POIOPTIONS_FROM, &CSymbolizerProjectView::OnPoioptionsFrom)
	ON_COMMAND(ID_POIOPTIONS_TO, &CSymbolizerProjectView::OnPoioptionsTo)
	ON_COMMAND(ID_RELATIONS_INPUT, &CSymbolizerProjectView::OnRelationsInput)
	ON_COMMAND(ID_NETPOI_FROM, &CSymbolizerProjectView::OnNetpoiFrom)
	ON_COMMAND(ID_NETPOI_TO, &CSymbolizerProjectView::OnNetpoiTo)
	ON_UPDATE_COMMAND_UI(ID_NETPOI_FROM, &CSymbolizerProjectView::OnUpdateNetpoiFrom)
	ON_UPDATE_COMMAND_UI(ID_NETPOI_TO, &CSymbolizerProjectView::OnUpdateNetpoiTo)
END_MESSAGE_MAP()

// CSymbolizerProjectView construction/destruction

CSymbolizerProjectView::CSymbolizerProjectView() noexcept
{
	m_bRedraw = TRUE;

}

CSymbolizerProjectView::~CSymbolizerProjectView()
{
}

BOOL CSymbolizerProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSymbolizerProjectView drawing

void CSymbolizerProjectView::OnDraw(CDC* pDC)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->RenderAvailable())
	{
		CRect rectUpdate;

		if (m_bRedraw)
		{
			switch (pDoc->m_CurrentMode)
			{
			case CSymbolizerProjectDoc::MODE::QUERY:
			{
				if (m_bRedrawBackground)
				{
					pDoc->Draw();
					m_bRedraw = FALSE;
					m_bRedrawBackground = FALSE;
				}
			}
			break;
			case CSymbolizerProjectDoc::MODE::BUILDING:
			{
				pDoc->Draw();
				m_bRedraw = FALSE;
			}
			break;
			default:
				break;
			}
			/*pDoc->Draw();
			m_bRedraw = FALSE;*/
		}

		int nType = pDC->GetClipBox(rectUpdate);

		if ((nType == NULLREGION) || (nType == ERROR))
			pDC->SelectClipRgn(NULL);

		pDC->GetClipBox(rectUpdate);

		CDC* pMemDC = pDoc->m_pTransformManager->GetMainDC();

		pDC->BitBlt(rectUpdate.left,
			rectUpdate.top,
			rectUpdate.Width(),
			rectUpdate.Height(),
			pMemDC,
			rectUpdate.left,
			rectUpdate.top,
			SRCCOPY);
	}

	if (pDoc->m_CurrentMode == CSymbolizerProjectDoc::MODE::BUILDING)
	{
		pDoc->OnMouseMoveBuilding(m_Point, pDC);
	}
	if (m_DrawNetworkWithoutBackground)
	{
		if (pDoc->RenderAvailable())
		{
			pDoc->DrawNetWorkWithoutBackground(pDC);
			m_DrawNetworkWithoutBackground = false;
		}
	}
}

// CSymbolizerProjectView printing


void CSymbolizerProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSymbolizerProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSymbolizerProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSymbolizerProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSymbolizerProjectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//pDoc->m_ActionId = 0;
	pDoc->Rup = 1;
	ClientToScreen(&point);
	if (pDoc->MMB == 0) OnContextMenu(this, point);
	else
		OnFindPathtMenu(this, point);
	Redraw();
}

void CSymbolizerProjectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_TRANSFORMATION, point.x, point.y, this, TRUE);
#endif
}
void CSymbolizerProjectView::OnFindPathtMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU3, point.x, point.y, this, TRUE);
#endif
}


// CSymbolizerProjectView diagnostics

#ifdef _DEBUG
void CSymbolizerProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CSymbolizerProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSymbolizerProjectDoc* CSymbolizerProjectView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSymbolizerProjectDoc)));
	return (CSymbolizerProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CSymbolizerProjectView message handlers


void CSymbolizerProjectView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->RenderAvailable())
	{
		CRect rcClient;

		GetClientRect(&rcClient);

		pDoc->m_pTransformManager->CreateMainWindow(rcClient.Width(), rcClient.Height(), RGB(255, 255, 255));
	}

	m_bRedraw = TRUE;
}


BOOL CSymbolizerProjectView::OnEraseBkgnd(CDC* pDC)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc != NULL)
	{
		if (pDoc->RenderAvailable())
			return TRUE;
	}

	return CView::OnEraseBkgnd(pDC);
}

void CSymbolizerProjectView::OnZoom(UINT nID)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_GroupAction = TRANSFORM_MAP;
	pDoc->m_ActionId = nID;
	//m_bRedraw = TRUE;
	//Invalidate(FALSE);
	return;
	/*if (nID == ID_ZOOM_ALL)
	{
		pDoc->m_pTransformManager->ZoomAll();


	}
	else
	{

		pDoc->m_ActionId = nID;
	}*/
}

void CSymbolizerProjectView::OnUpdateZoom(CCmdUI* pCmdUI)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	BOOL bEnabled = pDoc->RenderAvailable();

	if (bEnabled)
	{
		pCmdUI->SetCheck((pDoc->m_GroupAction == TRANSFORM_MAP) && (pDoc->m_ActionId == pCmdUI->m_nID));
	}

	pCmdUI->Enable(bEnabled);
}


void CSymbolizerProjectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->RenderAvailable())
	{
		if (pDoc->ExcuteUserAction(point, nFlags))
		{
			m_DrawNetworkWithoutBackground = false;
			Redraw();
		}
		else
		{
			if (pDoc->m_CurrentModeExcuteZoom == CSymbolizerProjectDoc::MODEEXCUTEZOOM::QUERY)
			{
				m_DrawNetworkWithoutBackground = true;
				Invalidate(FALSE);
			}
			else
			{
				m_DrawNetworkWithoutBackground = false;
				Redraw();
			}
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


BOOL CSymbolizerProjectView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->RenderAvailable())
	{
		ScreenToClient(&pt);
		CRect rcClient;
		GetClientRect(&rcClient);
		POINT p = pt;

		if (rcClient.PtInRect(p))
		{
			if (pDoc->ExecuteMouseWheel(pt, nFlags, zDelta))
			{
				Redraw();
			}
		}
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CSymbolizerProjectView::OnBuildingsExit()
{
	// TODO: Add your command handler code here
	CSymbolizerProjectDoc* pDoc = GetDocument();
	pDoc->ExitBuildingsMode();
	Redraw();
}

void CSymbolizerProjectView::Redraw()
{
	m_bRedrawBackground = TRUE;
	m_bRedraw = TRUE;
	Invalidate(FALSE);
}


void CSymbolizerProjectView::OnBuildingExit()
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->ExitBuildingsMode();
	m_bRedraw = TRUE;
	Invalidate(FALSE);
}


void CSymbolizerProjectView::OnSelectPoint()
{
	//CSymbolizerProjectDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//pDoc->m_sObject = !(pDoc->m_sObject);
}


void CSymbolizerProjectView::OnUpdateSelectPoint(CCmdUI* pCmdUI)
{
	//CSymbolizerProjectDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//pCmdUI->SetCheck(pDoc->m_sObject);
}

void CSymbolizerProjectView::OnMouseMove(UINT nFlags, CPoint point)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->RenderAvailable())
	{
		if (pDoc->m_CurrentMode == CSymbolizerProjectDoc::MODE::BUILDING && pDoc->m_CurrentModeExcuteZoom == CSymbolizerProjectDoc::MODEEXCUTEZOOM::BUILDING)
		{
			m_Point = point;
			Invalidate(FALSE);
		}
	}
}


void CSymbolizerProjectView::OnFlooroptionStylefloor()
{
	DlgStyleFloor dlg;
	dlg.DoModal();
}


void CSymbolizerProjectView::OnPoioptionsView()
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	pDoc->JumpToPoi();
	Redraw();
}


void CSymbolizerProjectView::OnPoioptionsFrom()
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetFrom();
	Redraw();
}


void CSymbolizerProjectView::OnPoioptionsTo()
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetTo();
	Redraw();
}


void CSymbolizerProjectView::OnRelationsInput()
{
	Relations DlgRl;
	DlgRl.DoModal();
}


void CSymbolizerProjectView::OnNetpoiFrom()
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->m_To)
	{
		pDoc->m_From = !(pDoc->m_From);
	}
	pDoc->OnClick(pDoc->ms);

	Redraw();
}


void CSymbolizerProjectView::OnNetpoiTo()
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->m_From)
	{
		pDoc->m_To = !(pDoc->m_To);
	}
	pDoc->OnClick(pDoc->ms);
	Redraw();
}


void CSymbolizerProjectView::OnUpdateNetpoiFrom(CCmdUI* pCmdUI)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc->m_To)
	{
		pCmdUI->SetCheck(pDoc->m_From);
	}
}


void CSymbolizerProjectView::OnUpdateNetpoiTo(CCmdUI* pCmdUI)
{
	CSymbolizerProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc->m_From)
	{
		pCmdUI->SetCheck(pDoc->m_To);
	}
}
