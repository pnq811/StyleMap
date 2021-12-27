#pragma once



// CFormViewDataSourceOCCI form view
#include <iostream>
#include <string>
#include <fstream>
#include <tinyxml2.h>
#include <sstream>
#include "CustomToolTipCtrl.h"
class CFormViewDataSourceOCCI : public CBCGPFormView
{
	DECLARE_DYNCREATE(CFormViewDataSourceOCCI)

protected:
	CFormViewDataSourceOCCI();           // protected constructor used by dynamic creation
	virtual ~CFormViewDataSourceOCCI();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_DATASOURCE_OCCI };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	std::string default_occi_encoding = "utf-8";
public:
	CCustomToolTipCtrl m_Tooltip;
	CBCGPEdit m_occi_encoding_edit;
	CBCGPEdit m_occi_script_edit;
	virtual void OnInitialUpdate();
	void SetDefault();
	std::string SettingsXml();
	void SettingsXml(std::string xml_string);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocusScriptOCCI();
	afx_msg void OnKillFocusOCCI();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CBCGPStatic m_occi_reset_button;
	afx_msg void OnStnClickedStaticOcciReset();
};


