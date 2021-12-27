#pragma once



// CFormViewPolygonSymbolizer form view
#include <iostream>
#include <map>
#include "CustomToolTipCtrl.h"
#include <tinyxml2.h>
#include <sstream>
#include <vector>
class CFormViewPolygonSymbolizer : public CBCGPFormView
{
	DECLARE_DYNCREATE(CFormViewPolygonSymbolizer)

protected:
	CFormViewPolygonSymbolizer();           // protected constructor used by dynamic creation
	virtual ~CFormViewPolygonSymbolizer();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CFormViewPolygonSymbolizer };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	// edit attribute fill
	std :: string m_xml_string;
	CBCGPEdit m_edit_polygon_fill_opacity;
	CBCGPEdit m_edit_gamma;
	CBCGPEdit m_edit_polygon_simplify;
	CBCGPEdit m_edit_polygon_smooth;
	CBCGPComboBox m_combo_polygon_gamma_method;
	CBCGPButton m_check_polygon_clip;
	CBCGPComboBox m_combo_polygon_simplify_algorithm;
	afx_msg void OnCbnSelchangeComboPolygonCompop();
	virtual int CheckValidNumberFromString(std::string strNum);
	CBCGPColorButton  m_colorbutton_polygon_fill;
	CBCGPComboBox m_combo_polygon_geometry_transform;
	CBCGPComboBox m_combo_polygon_compop;
	CBCGPButton m_button_polygon_default;

	CCustomToolTipCtrl		m_ToolTip;
	float default_polygon_gamma = 1;
	bool default_polygon = false;
	std::string default_polygon_gamma_method = "power";
	float default_polygon_fill_opacity = 1;
	COLORREF default_polygon_fill = RGB(128, 128, 128);
	bool default_polygon_clip = false;
	float default_polygon_simplify = 0;
	std::string default_polygon_simplify_algorithm = "radial-distance";
	float default_polygon_smooth = 0;
	std::string default_polygon_geometry_transform = "none";
	std::string default_polygon_compop = "src - over";


	std::string polygon_gamma_method[5] = 
	{
		"power",
		"linear",
		"none",
		"threshold",
		"multiply"
	};
	
	std::map<std::string, int> polygon_geometry_transform_map
		= { {"matrix(v00, v01, v10, v11, v20, v21 )", 6},
		{"translate (x,y)", 2},
		{"scale (x,y)", 2},
		{"rotate (v1,v2,v3)", 3},
		{"skewX(a)", 1},
		{"skewY(a)", 1} };
	std::string polygon_compop_type[37] = { "clear",
								"src",
								"dst",
								"src - over",
								"dst - over",
								"src - in",
								"dst - in",
								"src - out",
								"dst - out",
								"src - atop",
								"dst - atop",
								"xor",
								"plus",
								"minus",
								"multiply",
								"divide",
								"screen",
								"overlay",
								"darken",
								"lighten",
								"color - dodge",
								"color - burn",
								"linear - dodge",
								"linear - burn",
								"hard - light",
								"soft - light",
								"difference",
								"exclusion",
								"contrast",
								"invert",
								"invert - rgb",
								"grain - merge",
								"grain - extract",
								"hue",
								"saturation",
								"color",
								"value", };
	std::string polygon_simplify_algorithm[4] =
	{
		"radial-distance",
		"zhao-saalfeld",
		"visvalingam-whyatt",
		"douglas-peucker"
	};
	CButton m_polygon_button_ok;
	CButton m_polygon_button_apply;
	CButton m_polygon_buton_cancel;
	virtual void OnInitialUpdate();

	void SetDefault();
	void AddPolygonSimplifyAlgorithm();
	void AddPolygonCompop();
	void AddPolygonGeometryTransform();
	void AddPolygonGammaMethod();

	void DisableControl(bool check);
	afx_msg void OnBnClickedCheckPolygonDefault();

	std::string SettingsXML();
	std::string GetValueAttribute(const tinyxml2::XMLAttribute* att);
	void SettingsXML(std::string xml_string);
	afx_msg void OnBnClickedButtonPolygonApply();
	// CListBox m_list_polygon_text_box;
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	COLORREF HexStringToColor(std::string hex);
	
	afx_msg void OnBnKillfocusPolygon();
	CBCGPEdit m_script_polygon_text;
//	afx_msg void OnEnKillfocusEditPolygonFillOpacity();
	afx_msg void OnCbnKillfocusComboPolygonSymplifyAlgorithm();
	afx_msg void OnCbnSelchangeComboPolygonSymplifyAlgorithm();
	afx_msg void OnFocusScriptPolygon();
	
	afx_msg void OnStnClickedStaticPolygonSimplifyAlgorithm();

	std::vector <std::string > TokenizeString(std::string in_str, const char delimeter);
	afx_msg void OnBnClickedMfccolorbuttonPolygonFill();
	afx_msg void OnEnChangeKill();
	afx_msg void OnCbnSelchangeComboPolygonGammaMethod();
	afx_msg void OnBnClickedCheckPolygonClip();
};


