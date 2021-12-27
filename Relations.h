#pragma once


// Relations dialog

class Relations : public CDialog
{
	DECLARE_DYNAMIC(Relations)

public:
	Relations(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Relations();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
};
