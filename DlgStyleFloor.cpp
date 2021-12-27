// DlgStyleFloor.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "DlgStyleFloor.h"
#include "afxdialogex.h"
#include "SymbolizerProjectDoc.h"
#include "SymbolizerProjectView.h"


// DlgStyleFloor dialog

IMPLEMENT_DYNAMIC(DlgStyleFloor, CBCGPDialog)

DlgStyleFloor::DlgStyleFloor(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_STYLE_FLOOR, pParent)
{

}

DlgStyleFloor::~DlgStyleFloor()
{
}

void DlgStyleFloor::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgStyleFloor, CBCGPDialog)
	ON_BN_CLICKED(IDC_CPEN, &DlgStyleFloor::OnBnClickedCpen)
	ON_BN_CLICKED(IDOK, &DlgStyleFloor::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgStyleFloor message handlers


void DlgStyleFloor::OnBnClickedCpen()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		pen = dlg.GetColor();
		int r = GetRValue(pen);
		int g = GetGValue(pen);
		int b = GetBValue(pen);
		CFrameWnd* pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
		CSymbolizerProjectView* pView = (CSymbolizerProjectView*)pFrame->GetActiveView();
		CSymbolizerProjectDoc* pDoc = pView->GetDocument();
		pDoc->colorChose = pen;
	}
}


void DlgStyleFloor::OnBnClickedOk()
{
	CFrameWnd* pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	CSymbolizerProjectView* pView = (CSymbolizerProjectView*)pFrame->GetActiveView();
	CSymbolizerProjectDoc* pDoc = pView->GetDocument();

	CString sWidthPath;
	GetDlgItemText(IDC_EDIT_WIDTH, sWidthPath);
	int i = _ttoi(sWidthPath);

	pDoc->ChangeStyleFloor(pen, i);

	pView->Redraw();
	CBCGPDialog::OnOK();
}
