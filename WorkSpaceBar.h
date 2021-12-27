// workspacebar.h : interface of the CWorkSpaceBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CWorkSpaceBar : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar();

// Attributes
protected:
	CBCGPTreeCtrl m_wndTree;
	CCreateContext* m_pContext;
// Operations
public:

// Overrides

// Implementation
public:
	virtual ~CWorkSpaceBar();
	void SetContext(CCreateContext* pContext)
	{
		m_pContext = pContext;
	}
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
