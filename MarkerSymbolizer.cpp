// MarkerSymbolizer.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "MarkerSymbolizer.h"


// CMarkerSymbolizer

IMPLEMENT_DYNAMIC(CMarkerSymbolizer, CBCGPDockingControlBar)

CMarkerSymbolizer::CMarkerSymbolizer()
{
	m_pContext = NULL;

	CRuntimeClass* pFactory = RUNTIME_CLASS(CFormViewMarkerSymbolizer);
	m_pFormViewMarker = (CFormViewMarkerSymbolizer*)(pFactory->CreateObject());
}

CMarkerSymbolizer::~CMarkerSymbolizer()
{
}

void CMarkerSymbolizer::SettingsXml(std::string xmlString)
{
	m_pFormViewMarker->SettingsXml(xmlString);
}

std::string CMarkerSymbolizer::SettingsXml()
{
	return m_pFormViewMarker->SettingsXml();
}


BEGIN_MESSAGE_MAP(CMarkerSymbolizer, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CMarkerSymbolizer message handlers




int CMarkerSymbolizer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*CRect rectDummy;
	rectDummy.SetRectEmpty();*/
	// TODO:  Add your specialized creation code here
	if (m_pFormViewMarker != NULL)
	{
		m_pFormViewMarker->CreateView(this, m_pContext);
	}
	
	return 0;
}


void CMarkerSymbolizer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CBCGPDockingControlBar::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
}


void CMarkerSymbolizer::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_pFormViewMarker->GetSafeHwnd())
	{
		m_pFormViewMarker->SetWindowPos(NULL, -1, -1, cx, cy,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}


