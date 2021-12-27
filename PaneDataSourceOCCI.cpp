// PaneDataSourceOCCI.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "PaneDataSourceOCCI.h"


// CPaneDataSourceOCCI

IMPLEMENT_DYNAMIC(CPaneDataSourceOCCI, CBCGPDockingControlBar)

CPaneDataSourceOCCI::CPaneDataSourceOCCI()
{
	m_pContext = NULL;

	CRuntimeClass* pFactory = RUNTIME_CLASS(CFormViewDataSourceOCCI);
	m_pFormViewOCCI = (CFormViewDataSourceOCCI*)(pFactory->CreateObject());
}

CPaneDataSourceOCCI::~CPaneDataSourceOCCI()
{
}


BEGIN_MESSAGE_MAP(CPaneDataSourceOCCI, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CPaneDataSourceOCCI message handlers




int CPaneDataSourceOCCI::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (m_pFormViewOCCI != NULL)
	{
		m_pFormViewOCCI->CreateView(this, m_pContext);
	}
	return 0;
}


void CPaneDataSourceOCCI::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CBCGPDockingControlBar::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
}
std::string CPaneDataSourceOCCI::SettingsXml()
{
	return m_pFormViewOCCI->SettingsXml();
}
void CPaneDataSourceOCCI::SettingsXml(std::string xml_string)
{
	m_pFormViewOCCI->SettingsXml();
}

void CPaneDataSourceOCCI::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	if (m_pFormViewOCCI->GetSafeHwnd())
	{
		m_pFormViewOCCI->SetWindowPos(NULL, -1, -1, cx, cy,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
	// TODO: Add your message handler code here
}
