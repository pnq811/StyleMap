// TabCtrlMarker.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "TabCtrlMarker.h"
#include "TabMarker1.h"
#include "TabMarker2.h"
#include "TabMarker3.h"
// CTabCtrlMarker

IMPLEMENT_DYNAMIC(CTabCtrlMarker, CBCGPTabCtrl)

CTabCtrlMarker::CTabCtrlMarker()
{
	m_tabPages[0] = new CTabMarker1;
	m_tabPages[1] = new CTabMarker2;
	
	m_nNumPages = 2;
}

CTabCtrlMarker::~CTabCtrlMarker()
{
	for (int nCount = 0; nCount < m_nNumPages; nCount++)
	{
		delete m_tabPages[nCount];
	}
}


BEGIN_MESSAGE_MAP(CTabCtrlMarker, CBCGPTabCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CTabCtrlMarker message handlers




void CTabCtrlMarker::Init()
{
	// TODO: Add your implementation code here.
	m_tabCurrent = 0;
	m_tabPages[0]->Create(IDD_TAB_MARKER_1, this);
	m_tabPages[1]->Create(IDD_TAB_MARKER_2, this);
	
	
	m_tabPages[0]->ShowWindow(SW_SHOW);
	m_tabPages[1]->ShowWindow(SW_HIDE);

	SetRectangle();
}


void CTabCtrlMarker::SetRectangle()
{
	// TODO: Add your implementation code here.
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;
	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);
	
	nX = itemRect.left;
	nY = itemRect.bottom  + 1;
	nXc = tabRect.right - itemRect.left - 1;
	nYc = tabRect.bottom - nY - 1;

	m_tabPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for (int nCount = 1; nCount < m_nNumPages; nCount++)
	{
		m_tabPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
}


void CTabCtrlMarker::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CBCGPTabCtrl::OnLButtonDown(nFlags, point);

	if (m_tabCurrent != GetCurFocus())
	{
		m_tabPages[m_tabCurrent]->ShowWindow(SW_HIDE);
		m_tabCurrent = GetCurFocus();
		m_tabPages[m_tabCurrent]->ShowWindow(SW_SHOW);
		m_tabPages[m_tabCurrent]->SetFocus();
	}
}


void CTabCtrlMarker::OnSize(UINT nType, int cx, int cy)
{
	CBCGPTabCtrl::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;
	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX = itemRect.left;
	nY = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 1;
	nYc = tabRect.bottom - nY - 1;

	m_tabPages[m_tabCurrent]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for (int nCount = 0; nCount < m_nNumPages; nCount++)
	{
		if (nCount != m_tabCurrent)
		{
			m_tabPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
		}
	}
}
