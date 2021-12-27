#pragma once



// CFormViewDataSourceCSV form view
#include "tinyxml2.h"
#include <iostream>
#include "CustomToolTipCtrl.h"
class CFormViewDataSourceCSV : public CBCGPFormView
{
	DECLARE_DYNCREATE(CFormViewDataSourceCSV)

protected:
	CFormViewDataSourceCSV();           // protected constructor used by dynamic creation
	virtual ~CFormViewDataSourceCSV();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_DATASOURCE_CSV };
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
	std::string default_csv_file = "";
	std::string default_csv_base = "";
	std::string default_csv_encoding = "utf-8";
	std::string default_csv_escape = "\\";
	std::string default_csv_quote = "\"";
	std::string default_csv_separator = ",";
	std::string default_csv_headers = "";
	int default_csv_row_limit = 0;
	bool default_csv_strict = false;
	int default_csv_file_size_max = 20;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	void AddParameterTag(CString text_value,
		std::string name, std::string de_value,
		tinyxml2::XMLElement*& ds, tinyxml2::XMLDocument& doc);
	std::string SettingsXml();
	void SettingsXml(std::string xml_string);
	CBCGPEdit m_csv_file_edit;
	CBCGPStatic m_csv_file_open_static;
	virtual void OnInitialUpdate();
	CBCGPEdit m_csv_base_edit;
	CBCGPStatic m_csv_base_open_static;
	CBCGPEdit m_csv_encoding_edit;
	CBCGPEdit m_csv_row_limit_edit;
	CBCGPEdit m_csv_escape_edit;
	CBCGPEdit m_csv_quote_edit;
	CBCGPEdit m_csv_separator_edit;
	CBCGPEdit m_csv_headers_edit;
	CBCGPEdit m_csv_file_size_max_edit;
	CBCGPEdit m_csv_script_edit;
	CBCGPButton m_csv_strict_button;
	afx_msg void OnStnClickedStaticCsvFileOpen();
	afx_msg void OnStnClickedStaticCsvBaseOpen();
	afx_msg void OnKillFocusCSV();
	afx_msg void OnSetFocusScriptCSV();
	int CheckValidNumberFromString(std::string strNum);

	void SetDefault();
	CCustomToolTipCtrl	m_ToolTip;
	CBCGPStatic m_csv_reset_button_static;
	afx_msg void OnStnClickedStaticResetDefault();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


