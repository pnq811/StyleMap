
#pragma once

#include "ViewTree.h"
#include "CTree_File.h"
#include "SymbolizerProjectDoc.h"
#include <map>

class CFileViewToolBar : public CBCGPToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CBCGPToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CBCGPDockingControlBar
{
	// Construction
public:
	CFileView() noexcept;

	void AdjustLayout();
	void OnChangeVisualStyle();
	void SetData(Edge::Type type);

	// Attributes
protected:

	CTree_File m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

public:
	void FillFileView();

	// Implementation
public:
	virtual ~CFileView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

