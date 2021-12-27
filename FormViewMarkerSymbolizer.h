#pragma once



// CFormViewMarkerSymbolizer form view
#include "TabMarker1.h"
#include "TabMarker2.h"
#include "TabCtrlMarker.h"
#include "CustomToolTipCtrl.h"
#include "Symbolizer/S_Marker.h"
#include "tinyxml2.h"
#include <vector>
#include <string>
class CFormViewMarkerSymbolizer : public CBCGPFormView
{
	DECLARE_DYNCREATE(CFormViewMarkerSymbolizer)

protected:
	CFormViewMarkerSymbolizer();           // protected constructor used by dynamic creation
	virtual ~CFormViewMarkerSymbolizer();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CFormViewMarkerSymbolizer };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	COLORREF HexStringToColor(std::string hex);
	void InitTab();
	void SetTextScript();
	void SetDefault();
	virtual std::string  GetValueAttribute(const tinyxml2::XMLAttribute* att);
	std::vector<std::string> TokenizeString(std::string in_str, const char delimeter);
	std::string SettingsXml();
	void SettingsXml(std::string xml_string);
public:
	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	afx_msg void OnCbnSelchangeComboMarkerPlacement();
	CBCGPTabCtrl					m_tab_marker_symbolizer;
	CBCGPButton						m_button_check_marker_default;
	CTabCtrlMarker					m_tabctrl_marker;
	
	CCustomToolTipCtrl		m_ToolTip;
	virtual void OnInitialUpdate();

	afx_msg void OnBnClickedMarkerButtonApply();
	afx_msg void OnBnClickedMarkerButtonCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CBCGPEdit m_script_marker;

	S_Marker m_marker_symbolizer;

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
	std::string default_marker_simplify_algorithm = "radial-distance";
	bool default_marker_clip = false;

	float default_marker_stroke_width = 0.5;
	float default_marker_stroke_opacity = 1.0;
	float default_marker_width = 10;
	float default_marker_height = 10;
	std::string default_marker_placement = "point";
	std::string default_marker_multi_policy = "each";
	std::string default_marker_marker_type = "ellipse";

	COLORREF default_marker_stroke = RGB(0, 0, 0);
	COLORREF default_marker_fill = RGB(0, 0, 255);

	bool default_marker_ignore_placement = false;
	bool default_marker_avoid_edges = false;
	bool default_marker_allow_overlap = false;
	afx_msg void OnBnClickedCheckMarkerDefault();
	afx_msg void OnFocusScriptMarker();
};


