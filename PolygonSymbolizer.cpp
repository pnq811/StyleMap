// PolygonSymbolizer.cpp : implementation file
//

#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "PolygonSymbolizer.h"


// CPolygonSymbolizer



IMPLEMENT_DYNAMIC(CPolygonSymbolizer, CBCGPDockingControlBar)

CPolygonSymbolizer::CPolygonSymbolizer()
{
	m_pContext = NULL;

	CRuntimeClass* pFactory = RUNTIME_CLASS(CFormViewPolygonSymbolizer);
	m_pFormViewPolygon = (CFormViewPolygonSymbolizer*)(pFactory->CreateObject());
}

CPolygonSymbolizer::~CPolygonSymbolizer()
{
}



BEGIN_MESSAGE_MAP(CPolygonSymbolizer, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()

END_MESSAGE_MAP()


// CPolygonSymbolizer message handlers




int CPolygonSymbolizer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  Add your specialized creation code here
	/*CRect rectDummy;
	rectDummy.SetRectEmpty();*/
	if (m_pFormViewPolygon != NULL)
	{
		m_pFormViewPolygon->CreateView(this, m_pContext);
	}
	return 0;
}




void CPolygonSymbolizer::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	if (m_pFormViewPolygon->GetSafeHwnd())
	{
		m_pFormViewPolygon->SetWindowPos(NULL, -1, -1, cx, cy,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}


void CPolygonSymbolizer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CBCGPDockingControlBar::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
}

std::string CPolygonSymbolizer::SettingsXml()
{
	return std::string(m_pFormViewPolygon->SettingsXML());
}

void CPolygonSymbolizer::SettingXml(std::string xmlString)
{
	m_pFormViewPolygon->SettingsXML(xmlString);
}
