// CPaneDataSourceGEOJSON.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "PaneDataSourceGEOJSON.h"


// CPaneDataSourceGEOJSON

IMPLEMENT_DYNAMIC(CPaneDataSourceGEOJSON, CBCGPDockingControlBar)

CPaneDataSourceGEOJSON::CPaneDataSourceGEOJSON()
{
	m_pContext = NULL;

	CRuntimeClass* pFactory = RUNTIME_CLASS(CFormViewDataSourceGEOJSON);
	m_pFormViewGEOJSON = (CFormViewDataSourceGEOJSON*)(pFactory->CreateObject());
}

CPaneDataSourceGEOJSON::~CPaneDataSourceGEOJSON()
{
}


BEGIN_MESSAGE_MAP(CPaneDataSourceGEOJSON, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CPaneDataSourceGEOJSON message handlers




int CPaneDataSourceGEOJSON::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (m_pFormViewGEOJSON != NULL)
	{
		m_pFormViewGEOJSON->CreateView(this, m_pContext);
	}
	return 0;
}

std::string CPaneDataSourceGEOJSON::SettingsXml()
{
	return m_pFormViewGEOJSON->SettingsXml();
}
void CPaneDataSourceGEOJSON::SettingsXml(std::string xml_string)
{
	m_pFormViewGEOJSON->SettingsXml();
}
void CPaneDataSourceGEOJSON::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	if (m_pFormViewGEOJSON->GetSafeHwnd())
	{
		m_pFormViewGEOJSON->SetWindowPos(NULL, -1, -1, cx, cy,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}


void CPaneDataSourceGEOJSON::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CBCGPDockingControlBar::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
}
