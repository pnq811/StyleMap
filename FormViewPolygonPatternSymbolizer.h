#pragma once



// CFormViewPolygonPatternSymbolizer form view
#include <iostream>
#include <map>
#include "CustomToolTipCtrl.h"
#include "tinyxml2.h"
#include <vector>
#include <string>
class CFormViewPolygonPatternSymbolizer : public CBCGPFormView
{
	DECLARE_DYNCREATE(CFormViewPolygonPatternSymbolizer)

protected:
	CFormViewPolygonPatternSymbolizer();           // protected constructor used by dynamic creation
	virtual ~CFormViewPolygonPatternSymbolizer();
	
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CFormViewPolygonPatternSymbolizer };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
public:
	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	
	CBCGPEdit					m_edit_polygon_pattern_file;
	CBCGPEdit					m_edit_polygon_pattern_gamma;
	CBCGPEdit					m_edit_polygon_pattern_simplify;
	CBCGPEdit					m_edit_polygon_pattern_smooth;
	CBCGPButton					m_button_polygon_pattern_default;
	CBCGPComboBox				m_combo_polygon_pattern_alignment;
	CBCGPButton					m_polygon_pattern_clip;
	CBCGPComboBox				m_combo_polygon_pattern_simplify_algorithm;
	CBCGPComboBox				m_combo_polygon_pattern_geometry_transform;
	CBCGPComboBox				m_combo_polygon_pattern_transform;
	CBCGPComboBox				m_combo_polygon_pattern_compop;
	CBCGPEdit					m_edit_polygon_pattern_opacity;
	CBCGPStatic					m_polygon_pattern_open_folder_static;

	CCustomToolTipCtrl	m_ToolTip;
	std::string polygon_pattern_alignment[2] = { "global", "local" };
	std::string polygon_pattern_simplify_algorithm[4] = 
	{ 
		"radial-distance",
		"zhao-saalfeld",
		"visvalingam-whyatt",
		"douglas-peucker"
	};
	int CheckValidNumberFromString(std::string strNum);
	std::map<std::string, int> polygon_pattern_geometry_transform_map
		= { {"matrix(v00, v01, v10, v11, v20, v21 )", 6},
		{"translate (x,y)", 2},
		{"scale (x,y)", 2},
		{"rotate (v1,v2,v3)", 3},
		{"skewX(a)", 1},
		{"skewY(a)", 1} };
	std::map<std::string, int> polygon_pattern_transform_map
		= { {"matrix(v00, v01, v10, v11, v20, v21 )", 6},
		{"translate (x,y)", 2},
		{"scale (x,y)", 2},
		{"rotate (v1,v2,v3)", 3},
		{"skewX(a)", 1},
		{"skewY(a)", 1} };
	std::string m_polygon_pattern_compop_type[37] = { "clear",
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
	std::string default_polygon_pattern_file = "";
	std::string default_polygon_pattern_alignment = "global";
	float default_polygon_pattern_gamma = 1;
	float default_polygon_pattern_opacity = 1;
	bool default_polygon_pattern_clip = false;
	float default_polygon_pattern_simplify = 0;
	std::string default_polygon_pattern_simplify_algorithm = "radial-distance";
	float default_polygon_pattern_smooth = 0;
	std::string default_polygon_pattern_geometry_transform = "none";
	std::string default_polygon_pattern_transform = "none";
	std::string default_polygon_pattern_compop = "src - over";
public:
	void AddPolygonPatternAlignment();
	void AddPolygonPatternSimplifyAlgorithm();
	void AddPolygonPatternGeometryTransform();
	void AddPolygonPatternTransform();
	void AddPolygonPatternCompOp();
	void SetDefault();
	std::string SettingsXml();
	virtual std::string GetValueAttribute(const tinyxml2::XMLAttribute *att);
	void SettingsXml(std::string xml_string);
	afx_msg void OnBnClickedPolygonPatternApplyButton();
	virtual void OnInitialUpdate();
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CBCGPEdit m_script_polygon_pattern;
	afx_msg void OnKillFocus();
	afx_msg void OnBnClickedButtonPolygonPatternFile();
	afx_msg void OnBnClickedCheckPolygonPatternDefault();
	afx_msg void OnFocusScriptPolygonPattern();
	
	virtual std::vector <std::string > TokenizeString(std::string in_str, const char delimeter);
	
	afx_msg void OnCbnSelchangeComboPolygonPatternAlignment();
	afx_msg void OnCbnSelchangeComboPolygonPatternSimplifyAlgorithm();
	afx_msg void OnBnClickedCheckPolygonPatternClip();
	afx_msg void OnCbnSelchangeComboPolygonPatternCompop();
	afx_msg void OnStnClickedStaticPolygonPattenFolder();
};





