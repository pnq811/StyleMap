#pragma once


// CTabMarker1 dialog
#include "CustomToolTipCtrl.h"
#include <iostream>
#include <map>
#include <string>
#include "Symbolizer/S_Marker.h"
#include <vector>
#include <sstream>
class CTabMarker1 : public CBCGPDialog
{
	DECLARE_DYNAMIC(CTabMarker1)

public:
	CTabMarker1(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabMarker1();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_MARKER_1 };
#endif

protected:
	CCustomToolTipCtrl		m_ToolTip;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	S_Marker						m_symbolizer_marker;
	DECLARE_MESSAGE_MAP()
	
	
	CBCGPStatic						m_marker_fill_opacity_static;
	CBCGPStatic						m_marker_opacity_static;
	CBCGPStatic						m_marker_file_static;

	
	CBCGPComboBox					m_marker_compop_combo;
	CBCGPStatic						m_marker_compop_static;
	CBCGPComboBox					m_marker_direction_combo;
	CBCGPStatic						m_marker_direction_static;
	
	CBCGPEdit						m_marker_file_edit;
	CBCGPEdit						m_marker_opacity_edit;
	CBCGPEdit						m_marker_fill_opacity_edit;
	bool m_default = true;
	std::string marker_direction[8] =
	{
		"auto",
		"auto-down",
		"left",
		"right",
		"left-only",
		"right-only",
		"up",
		"down",
		
	};
	std::string marker_comop[37] =
	{ "clear",
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
	std::string marker_multi_policy[3] =
	{
		"each",
		"whole",
		"largest",
	};
	std::string marker_placement[5] =
	{
		"point",
		"line",
		"interior",
		"vertex-first",
		"vertex-last"
	};
	std::map<std::string, int>  marker_geometry_transform_map
		= { {"matrix", 6},
		{"translate", 2},
		{"scale", 2},
		{"rotate", 3},
		{"skewX", 1},
		{"skewY", 1} };
	std::map<std::string, int> marker_transform_map
		= { {"matrix", 6},
		{"translate", 2},
		{"scale", 2},
		{"rotate", 3},
		{"skewX", 1},
		{"skewY", 1} };
	std::string marker_marker_type[2] =
	{
		"arrow",
		"ellipse"
	};
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
	
public:
	virtual int CheckValidNumberFromString(std::string strNum);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void AddMarkerDirection();
	void AddMarkerCompOp();

	void AddMarkerMultiPolicy();
	void AddMarkerType();
	
	void SetDefault();
	void AddValuePlacement();
	std::vector<std::string> TokenizeString(std::string in_str, const char delimeter);

	void SetMarkerTab1(S_Marker & t_marker);
	
	
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	S_Marker GetMarkerSymbolizer();
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocusMarkerTab1();
	afx_msg void OnBnClickedButtonOpenFileMarker();
	
	
	
	CBCGPColorButton m_marker_stroke_colorbutton;
	CBCGPEdit m_marker_stroke_width_edit;
	CBCGPStatic m_marker_stroke_width_static;
	CBCGPEdit m_marker_width_edit;
	CBCGPEdit m_marker_stroke_opacity;
	CBCGPEdit m_marker_height_edit;
	CBCGPComboBox m_marker_placement_combo;
	CBCGPComboBox m_marker_multi_policy_combo;
	CBCGPComboBox m_marker_type_combo;

	CBCGPColorButton m_marker_fill_colorbutton;

	
	afx_msg void OnBnClickedMfccolorbuttonMarkerStroke();
	afx_msg void OnBnClickedMfccolorbuttonMarkerFill();
	afx_msg void OnCbnSelchangeComboMarkerPlacement();
	afx_msg void OnCbnSelchangeComboMarkerMultiPolicy();
	afx_msg void OnCbnSelchangeComboMarkerMarkerType();
	afx_msg void OnCbnSelchangeComboMarkerCompop();
	afx_msg void OnCbnSelchangeComboMarkerDirection();
	CBCGPStatic m_marker_open_file_button;
	afx_msg void OnStnClickedStaticOpenFolder();
};
