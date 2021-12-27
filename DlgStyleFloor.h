#pragma once


// DlgStyleFloor dialog

class DlgStyleFloor : public CBCGPDialog
{
	DECLARE_DYNAMIC(DlgStyleFloor)

public:
	DlgStyleFloor(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgStyleFloor();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STYLE_FLOOR };
#endif

public: 
	COLORREF pen;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCpen();
	afx_msg void OnBnClickedOk();
};
