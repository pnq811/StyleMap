// CPaneDataSourceGDAL.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "PaneDataSourceGDAL.h"


// CPaneDataSourceGDAL

IMPLEMENT_DYNAMIC(CPaneDataSourceGDAL, CBCGPDockingControlBar)

CPaneDataSourceGDAL::CPaneDataSourceGDAL()
{
	m_pContext = NULL;

	CRuntimeClass* pFactory = RUNTIME_CLASS(CFormViewDataSourceGDAL);
	m_pFormViewGDAL = (CFormViewDataSourceGDAL*)(pFactory->CreateObject());
}

CPaneDataSourceGDAL::~CPaneDataSourceGDAL()
{
}


BEGIN_MESSAGE_MAP(CPaneDataSourceGDAL, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CPaneDataSourceGDAL message handlers




int CPaneDataSourceGDAL::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (m_pFormViewGDAL != NULL)
	{
		m_pFormViewGDAL->CreateView(this, m_pContext);
	}
	return 0;
}


void CPaneDataSourceGDAL::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CBCGPDockingControlBar::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
}

std::string CPaneDataSourceGDAL::SettingsXml()
{
	return m_pFormViewGDAL->SettingsXml();
}
void CPaneDataSourceGDAL::SettingsXml(std::string xml_string)
{
	m_pFormViewGDAL->SettingsXml();
}
void CPaneDataSourceGDAL::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	if (m_pFormViewGDAL->GetSafeHwnd())
	{
		m_pFormViewGDAL->SetWindowPos(NULL, -1, -1, cx, cy,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
	// TODO: Add your message handler code here
}
