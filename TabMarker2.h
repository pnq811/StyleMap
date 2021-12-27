#pragma once


// CTabMarker2 dialog
#include <iostream>
#include "CustomToolTipCtrl.h"
#include "Symbolizer/S_Marker.h"
#include <vector>
class CTabMarker2 : public CBCGPDialog
{
	DECLARE_DYNAMIC(CTabMarker2)

public:
	CTabMarker2(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabMarker2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_MARKER_2};
#endif
public:
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
public:
	
	
	
	CBCGPButton m_marker_allow_overlap_button_check;
	CBCGPButton m_marker_ignore_placement_checkbox;
	CBCGPButton m_marker_avoid_edges_checkbox;
	CBCGPComboBox m_marker_simplify_algorithm_combo;
	CBCGPStatic m_marker_simplify_algorithm_static;
	CCustomToolTipCtrl m_ToolTip;
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedStaticMarkerHeight();
	afx_msg void OnCbnSelchangeComboMarkerMarkerType();
	afx_msg void OnBnClickedCheckMarkerAllowOverlap();
	void AddMarkerSimplifyAlgorithm();

	void AddMarkerGeometryTransform();

	void AddMarkerTransform();
	
	CBCGPStatic m_marker_fill_static;
	bool default_marker_clip = false;
	float default_marker_spacing = 100.0;
	std::string default_marker_file = "";
	float default_marker_opacity = 1;
	float default_marker_fill_opacity = 1;
	float default_marker_max_error = 0.2;
	float default_marker_simplify = 0;
	float default_marker_smooth = 0;
	std::string default_marker_geometry_transform = "none";
	std::string default_marker_transform = "none";
	float default_marker_offset = 0;
	std::string default_marker_compop = "src - over";
	std::string default_marker_direction = "right";

	float default_marker_stroke_width = 0.5;
	float default_marker_stroke_opacity = 1.0;
	float default_marker_width = 10;
	float default_marker_height = 10;
	std::string default_marker_placement = "point";
	std::string default_marker_multi_policy = "each";
	std::string default_marker_marker_type = "ellipse";
	std::string default_marker_simplify_algorithm = "radial-distance";
	COLORREF default_marker_stroke = RGB(0, 0, 0);
	COLORREF default_marker_fill = RGB(0, 0, 255);
	std::map<std::string, int>  marker_geometry_transform_map
		= { {"matrix(v00, v01, v10, v11, v20, v21 )", 6},
		{"translate (x,y)", 2},
		{"scale (x,y)", 2},
		{"rotate (v1,v2,v3)", 3},
		{"skewX(a)", 1},
		{"skewY(a)", 1} };
	std::map<std::string, int> marker_transform_map
		= { {"matrix(v00, v01, v10, v11, v20, v21 )", 6},
		{"translate (x,y)", 2},
		{"scale (x,y)", 2},
		{"rotate (v1,v2,v3)", 3},
		{"skewX(a)", 1},
		{"skewY(a)", 1} };
	bool default_marker_ignore_placement = false;
	bool default_marker_avoid_edges = false;
	bool default_marker_allow_overlap = false;
	
	std::string marker_simplify_algorithm[4] =
	{
		"radial-distance",
		"zhao-saalfeld",
		"visvalingam-whyatt",
		"douglas-peucker"
	};
	
	std::string marker_placement[5] =
	{
		"point",
		"line",
		"interior",
		"vertex-first",
		"vertex-last"
	};
	
	void SetDefault2();
	std::vector<std::string> TokenizeString(std::string in_str, const char delimeter);
	void SetMarkerTab2(S_Marker& t_marker);
	S_Marker GetMarkerSymbolizer();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int CheckValidNumberFromString(std::string strNum);
	afx_msg void OnKillFocusTab2();
	

	afx_msg void OnStnClickedStaticMarkerFill();
	CBCGPComboBox m_marker_transform_combo;
	CBCGPComboBox m_marker_geometry_transform_combo;
	CBCGPEdit m_marker_offset_edit;
	CBCGPEdit m_marker_simplify_edit;
	CBCGPEdit m_marker_smooth_edit;
	CBCGPEdit m_marker_max_error_edit;
	CBCGPEdit m_marker_spacing_edit;
	CBCGPButton m_marker_clip_button;

	afx_msg void OnBnClickedCheckMarkerIgnorePlacement();
	afx_msg void OnBnClickedCheckMarkerAvoidEdges();
	afx_msg void OnBnClickedCheckMarkerClip();
};
