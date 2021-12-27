#pragma once


// CTabCtrlMarker

class CTabCtrlMarker : public CBCGPTabCtrl
{
	DECLARE_DYNAMIC(CTabCtrlMarker)

public:
	CTabCtrlMarker();
	virtual ~CTabCtrlMarker();
	CBCGPDialog* m_tabPages[2];
	int m_tabCurrent;
	int m_nNumPages;
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Init();
	void SetRectangle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


