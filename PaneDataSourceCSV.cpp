// PaneDataSourceCSV.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "PaneDataSourceCSV.h"


// CPaneDataSourceCSV

IMPLEMENT_DYNAMIC(CPaneDataSourceCSV, CBCGPDockingControlBar)

CPaneDataSourceCSV::CPaneDataSourceCSV()
{
	m_pContext = NULL;

	CRuntimeClass* pFactory = RUNTIME_CLASS(CFormViewDataSourceCSV);
	m_pFormViewCSV = (CFormViewDataSourceCSV*)(pFactory->CreateObject());

}

CPaneDataSourceCSV::~CPaneDataSourceCSV()
{
}


BEGIN_MESSAGE_MAP(CPaneDataSourceCSV, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CPaneDataSourceCSV message handlers




int CPaneDataSourceCSV::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (m_pFormViewCSV != NULL)
	{
		m_pFormViewCSV->CreateView(this, m_pContext);
	}
	
	return 0;
}


void CPaneDataSourceCSV::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	if (m_pFormViewCSV->GetSafeHwnd())
	{
		m_pFormViewCSV->SetWindowPos(NULL, -1, -1, cx, cy,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
	// TODO: Add your message handler code here
}


std::string CPaneDataSourceCSV::SettingsXml()
{
	return m_pFormViewCSV->SettingsXml();
}
void CPaneDataSourceCSV::SettingsXml(std::string xml_string)
{
	m_pFormViewCSV->SettingsXml();
}
void CPaneDataSourceCSV::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CBCGPDockingControlBar::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
}
