#pragma once


// CDialogProgress dialog

class CDialogProgress : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDialogProgress)

public:
	CDialogProgress(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogProgress();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROGRESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SetRange(int num); 
	void UpdateUI(); 
	CBCGPStatic m_Text_NumTileDraw;
	CProgressCtrl m_Progress;
	int numtiledraw = 1; 
	int numtile; 
};
