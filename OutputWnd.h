
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList window
#include <string>
using namespace std;

class COutputList : public CListBox
{
	// Construction
public:
	COutputList() noexcept;

	// Implementation
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CBCGPDockingControlBar
{
	// Construction
public:
	COutputWnd() noexcept;

	void FillDebugWindow(string str, double x, double y);
	void UpdateFonts();

	// Attributes
protected:
	CBCGPTabWnd	m_wndTabs;

	COutputList m_wndOutputBuild;
	COutputList m_wndOutputDebug;
	COutputList m_wndOutputFind;

protected:
	void FillBuildWindow();
	void FillFindWindow();

	void AdjustHorzScroll(CListBox& wndListBox);

	// Implementation
public:
	virtual ~COutputWnd();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

