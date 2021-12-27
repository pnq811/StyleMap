// PolygonPatternSymbolizer.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "PolygonPatternSymbolizer.h"


// CPolygonPatternSymbolizer

IMPLEMENT_DYNAMIC(CPolygonPatternSymbolizer, CBCGPDockingControlBar)

CPolygonPatternSymbolizer::CPolygonPatternSymbolizer()
{
	m_pContext = NULL;

	CRuntimeClass* pFactory = RUNTIME_CLASS(CFormViewPolygonPatternSymbolizer);
	m_pFormViewPolygonPattern = (CFormViewPolygonPatternSymbolizer*)(pFactory->CreateObject());
}

CPolygonPatternSymbolizer::~CPolygonPatternSymbolizer()
{
}


BEGIN_MESSAGE_MAP(CPolygonPatternSymbolizer, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CPolygonPatternSymbolizer message handlers




int CPolygonPatternSymbolizer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	/*CRect rectDummy;
	rectDummy.SetRectEmpty();*/

	if (m_pFormViewPolygonPattern != NULL)
	{
		m_pFormViewPolygonPattern->CreateView(this, m_pContext);
	}
	return 0;
}


void CPolygonPatternSymbolizer::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_pFormViewPolygonPattern->GetSafeHwnd())
	{
		m_pFormViewPolygonPattern->SetWindowPos(NULL, -1, -1, cx, cy,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

}


void CPolygonPatternSymbolizer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CBCGPDockingControlBar::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
}

void CPolygonPatternSymbolizer::SettingsXml(std::string xmlString)
{
	m_pFormViewPolygonPattern->SettingsXml(xmlString);
}

std::string CPolygonPatternSymbolizer::SettingsXml()
{
	return m_pFormViewPolygonPattern->SettingsXml();
}


