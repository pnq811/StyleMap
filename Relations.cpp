// Relations.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "Relations.h"
#include "afxdialogex.h"

#include "SymbolizerProjectDoc.h"
#include "SymbolizerProjectView.h"
#include <string>

// Relations dialog

IMPLEMENT_DYNAMIC(Relations, CBCGPDialog)

Relations::Relations(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

Relations::~Relations()
{
}

void Relations::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Relations, CDialog)
	ON_EN_CHANGE(IDC_WEIGHT, &Relations::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &Relations::OnBnClickedOk)
END_MESSAGE_MAP()


// Relations message handlers


void Relations::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Relations::OnBnClickedOk()
{
	CFrameWnd* pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	CSymbolizerProjectView* pView = (CSymbolizerProjectView*)pFrame->GetActiveView();
	CSymbolizerProjectDoc* pDoc = pView->GetDocument();

	CString weight , height , width ;

	GetDlgItemText(IDC_WEIGHT, weight);
	GetDlgItemText(IDC_HEIGHT, height);
	GetDlgItemText(IDC_WIDHT, width);

	pDoc->vehicle->weight = _wtof(weight);
	pDoc->vehicle->height = _wtof(height);
	pDoc->vehicle->width = _wtof(width);

	CDialog::OnOK();
}
