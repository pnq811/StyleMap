
// IndoorNavigationView.h : interface of the CSymbolizerProjectView class
//

#pragma once


class CSymbolizerProjectView : public CView
{
protected: // create from serialization only
	CSymbolizerProjectView() noexcept;
	DECLARE_DYNCREATE(CSymbolizerProjectView)

	// Attributes
private:
	BOOL m_bRedraw;
	BOOL m_bRedrawBackground;
	bool m_DrawNetworkWithoutBackground;
	CPoint m_Point;

public:
	CSymbolizerProjectDoc* GetDocument() const;
	void Redraw();
	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CSymbolizerProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFindPathtMenu(CWnd* /* pWnd */, CPoint point);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnZoom(UINT nID);
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBuildingsExit();
	afx_msg void OnBuildingExit();
	afx_msg void OnSelectPoint();
	afx_msg void OnUpdateSelectPoint(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnFlooroptionStylefloor();
	afx_msg void OnPoioptionsView();
	afx_msg void OnPoioptionsFrom();
	afx_msg void OnPoioptionsTo();
	afx_msg void OnRelationsInput();
	afx_msg void OnNetpoiFrom();
	afx_msg void OnNetpoiTo();
	afx_msg void OnUpdateNetpoiFrom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNetpoiTo(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in IndoorNavigationView.cpp
inline CSymbolizerProjectDoc* CSymbolizerProjectView::GetDocument() const
{
	return reinterpret_cast<CSymbolizerProjectDoc*>(m_pDocument);
}
#endif

