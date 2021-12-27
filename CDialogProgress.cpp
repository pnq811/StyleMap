// CDialogProgress.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "CDialogProgress.h"
#include "afxdialogex.h"
#include "StringProcess.h"
#include <iostream>


// CDialogProgress dialog

IMPLEMENT_DYNAMIC(CDialogProgress, CBCGPDialog)

CDialogProgress::CDialogProgress(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_DIALOG_PROGRESS, pParent)
{

}

CDialogProgress::~CDialogProgress()
{
}

void CDialogProgress::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NUMTILEDRAW, m_Text_NumTileDraw);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

void CDialogProgress::SetRange(int num)
{
	numtile = num; 
	m_Progress.SetRange(1, num); 
}

void CDialogProgress::UpdateUI()
{
	m_Text_NumTileDraw.SetWindowTextW(StringProcess::int2cstring((int)((numtiledraw * 100) / (numtile))));
	++numtiledraw; 
	m_Progress.OffsetPos(1); 
}


BEGIN_MESSAGE_MAP(CDialogProgress, CBCGPDialog)
END_MESSAGE_MAP()


// CDialogProgress message handlers
