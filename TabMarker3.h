#pragma once


// CTabMarker3 dialog

class CTabMarker3 : public CBCGPDialog
{
	DECLARE_DYNAMIC(CTabMarker3)

public:
	CTabMarker3(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabMarker3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_MARKER_3 };
#endif
public:
	void AddValueCompop();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

};
