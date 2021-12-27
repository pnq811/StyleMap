#pragma once



// CFormViewDataSourceGDAL form view
#include <iostream>
#include "CustomToolTipCtrl.h"
class CFormViewDataSourceGDAL : public CBCGPFormView
{
	DECLARE_DYNCREATE(CFormViewDataSourceGDAL)

protected:
	CFormViewDataSourceGDAL();           // protected constructor used by dynamic creation
	virtual ~CFormViewDataSourceGDAL();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW_DATASOURCE_GDAL };
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

	void SetDefault();

	DECLARE_MESSAGE_MAP()

public: 
	std::string SettingsXml();
	int CheckValidNumberFromString(std::string strNum);
	void SettingsXml(std::string xml_string);
public:
	std::string default_gdal_file = "";
	std::string default_gdal_base = "";
	std::string default_gdal_encoding = "utf-8";
	int default_gdal_max_image_area = 13107200;
	int default_gdal_band = 0;
	float default_gdal_nodata = 0;
	float default_gdal_nodata_tolerance = 1e-12;
	bool default_gdal_shared = false;
public:
	CBCGPEdit m_gdal_file_edit;
	CBCGPEdit m_gdal_base_edit;
	CBCGPStatic m_gdal_file_open_static;
	CBCGPStatic m_gdal_base_open_static;
	
	CBCGPEdit m_gdal_encoding_edit;
	CBCGPEdit m_gdal_max_image_area_edit;
	CBCGPEdit m_gdal_band_edit;
	CBCGPEdit m_gdal_nodata_edit;
	CBCGPEdit m_gdal_nodata_tolerance_edit;
	CBCGPButton m_gdal_shared_button;
	int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnStnClickedStaticGdalFileOpen();
	afx_msg void OnStnClickedStaticGdalBaseOpen();
	afx_msg void OnSetFocusScriptGDAL();
	CBCGPEdit m_gdal_script_edit;
	afx_msg void OnKillFocusGDAL();
	CBCGPStatic m_gdal_reset_static;
	CCustomToolTipCtrl m_Tooltip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


