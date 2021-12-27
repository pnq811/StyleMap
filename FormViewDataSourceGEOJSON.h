#pragma once



// CFormViewDataSourceGEOJSON form view
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <tinyxml2.h>
#include "CustomToolTipCtrl.h"
class CFormViewDataSourceGEOJSON : public CBCGPFormView
{
	DECLARE_DYNCREATE(CFormViewDataSourceGEOJSON)

protected:
	CFormViewDataSourceGEOJSON();           // protected constructor used by dynamic creation
	virtual ~CFormViewDataSourceGEOJSON();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_DATASOURCE_GEOJSON };
#endif
#ifdef _DEBUG
	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	std::string default_geojson_file = "";
	std::string default_geojson_base = "";
	std::string default_geojson_encoding = "utf-8";
	std::string default_geojson_inline = "";
public:

	CCustomToolTipCtrl m_Tooltip;
	CBCGPEdit m_geojson_file_edit;
	CBCGPStatic m_geojson_file_open_static;
	CBCGPEdit m_geojson_base_edit;
	CBCGPStatic m_geojson_base_open_static;
	CBCGPEdit m_geojson_encoding_edit;
	CBCGPEdit m_geojson_inline_edit;
	virtual void OnInitialUpdate();
	void AddParameterTag(CString text_value, std::string name, std::string de_value, tinyxml2::XMLElement*& ds, tinyxml2::XMLDocument& doc);
	std::string SettingsXml();
	void SettingsXml(std::string xml_string);
	afx_msg
		void SetDefault();
	void OnStnClickedStaticGeojsonFileOpen();
	afx_msg void OnStnClickedStaticGeojsonBaseOpen();
	CBCGPEdit m_geojson_script_edit;
	afx_msg void OnSetFocusScriptGEOJSON();
	afx_msg void OnKillFocusGEOJSON();
	CBCGPStatic m_geojson_reset_static;
	afx_msg void OnStnClickedStaticGeojsonReset();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


