// FormViewMarkerSymbolizer.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "FormViewMarkerSymbolizer.h"
#include "CustomToolTipCtrl.h"
#include "Symbolizer/S_Marker.h"
#include <fstream>
#include <sstream>
// CFormViewMarkerSymbolizer

IMPLEMENT_DYNCREATE(CFormViewMarkerSymbolizer, CBCGPFormView)

CFormViewMarkerSymbolizer::CFormViewMarkerSymbolizer()
	: CBCGPFormView(IDD_CFormViewMarkerSymbolizer)
{

}

CFormViewMarkerSymbolizer::~CFormViewMarkerSymbolizer()
{
}

void CFormViewMarkerSymbolizer::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MARKER_SYMBOLIZER, m_tabctrl_marker);
	DDX_Control(pDX, IDC_CHECK_MARKER_DEFAULT, m_button_check_marker_default);

	DDX_Control(pDX, IDC_EDIT_SCRIPT_MARKER, m_script_marker);
}

COLORREF CFormViewMarkerSymbolizer::HexStringToColor(std::string hex)
{
	LPCSTR color_cstr = hex.c_str();
	color_cstr++;
	COLORREF ref;
	ref = strtol(color_cstr, NULL, 16);
	return COLORREF(RGB(GetBValue(ref), GetGValue(ref), GetRValue(ref)));
}

void CFormViewMarkerSymbolizer::InitTab()
{
	
	
	m_tab_marker_symbolizer.InsertItem(0, _T("TabOne"));
	m_tab_marker_symbolizer.InsertItem(1, _T("TabTwo"));
}

void CFormViewMarkerSymbolizer::SetTextScript()
{

	std::string text = SettingsXml();

	SettingsXml(text);
	m_script_marker.SetWindowTextW(CString(text.c_str()));

}

void CFormViewMarkerSymbolizer::SetDefault()
{
	CTabMarker1* tab1 = (CTabMarker1*)m_tabctrl_marker.m_tabPages[0];
	CTabMarker2* tab2 = (CTabMarker2*)m_tabctrl_marker.m_tabPages[1];
	tab1->SetDefault();
	tab2->SetDefault2();
}

std::string CFormViewMarkerSymbolizer::GetValueAttribute(const tinyxml2::XMLAttribute* att)
{
	if (att != NULL)
	{
		return att->Value();
	}
	return std::string();
}

std::vector<std::string> CFormViewMarkerSymbolizer::TokenizeString(std::string in_str, const char delimeter)
{
	std::vector <std::string> out;
	std::stringstream str(in_str);
	std::string s1;
	while (std::getline(str, s1, delimeter))
	{
		out.push_back(s1); // store the string in s1 
	}
	return out;
}

std::string CFormViewMarkerSymbolizer::SettingsXml()
{
	/// <summary>
   /// The function is used to get string of tinyxml for attribute in marker symbolizer formview
   /// from the controls.
   /// </summary>
   /// <returns>The string xml </returns>
	CTabMarker1* tab1 = (CTabMarker1*)m_tabctrl_marker.m_tabPages[0];
	CTabMarker2* tab2 = (CTabMarker2*)m_tabctrl_marker.m_tabPages[1];
	S_Marker s_marker_1 = tab1->GetMarkerSymbolizer();
	S_Marker s_marker_2 = tab2->GetMarkerSymbolizer();
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* marker = doc.NewElement("MarkerSymbolizer");

	if (s_marker_1.marker_default != false)
	{
		m_marker_symbolizer.marker_default = s_marker_1.marker_default;
		marker->SetAttribute("default", "true");
	}
	if (s_marker_2.marker_clip == true)
	{
		m_marker_symbolizer.marker_clip = s_marker_2.marker_clip;
		marker->SetAttribute("clip", "true");
	}
	if (s_marker_1.marker_file != default_marker_file)
	{
		marker->SetAttribute("file", s_marker_1.marker_file.c_str());
	}

	if (s_marker_1.marker_opacity != default_marker_opacity)
	{
		marker->SetAttribute("opacity", std::to_string(s_marker_1.marker_opacity).c_str());
	}
	if (s_marker_1.marker_fill_opacity != default_marker_fill_opacity)
	{
		marker->SetAttribute("fill-opacity",
			std::to_string(s_marker_1.marker_fill_opacity).c_str());
	}
	if (s_marker_1.marker_stroke != default_marker_stroke)
	{
		CString color;
		color.Format(_T("#%02X%02X%02X"),
			GetRValue(s_marker_1.marker_stroke),
			GetGValue(s_marker_1.marker_stroke),
			GetBValue(s_marker_1.marker_stroke));
		marker->SetAttribute("stroke", std::string(CT2A(color)).c_str());
	}
	if (s_marker_1.marker_stroke_width != default_marker_stroke_width)
	{
		marker->SetAttribute("stroke-width", std::to_string(s_marker_1.marker_stroke_width).c_str());
	}
	if (s_marker_1.marker_stroke_opacity != default_marker_stroke_opacity)
	{

		marker->SetAttribute("stroke-opacity",
			std::to_string(s_marker_1.marker_stroke_opacity).c_str());
	}
	if (s_marker_1.marker_placement != default_marker_placement)
	{
		marker->SetAttribute("placement", s_marker_1.marker_placement.c_str());
	}
	if (s_marker_1.marker_multi_policy != default_marker_multi_policy)
	{
		marker->SetAttribute("multi-policy", s_marker_1.marker_multi_policy.c_str());
	}
	if (s_marker_1.marker_type.compare(default_marker_marker_type) != 0)
	{
		marker->SetAttribute("type", s_marker_1.marker_type.c_str());
	}
	if (s_marker_1.marker_width != default_marker_width)
	{
		marker->SetAttribute("width", std::to_string(s_marker_1.marker_width).c_str());
	}
	if (s_marker_1.marker_height != default_marker_height)
	{
		marker->SetAttribute("height", std::to_string(s_marker_1.marker_height).c_str());
	}
	if (s_marker_1.marker_fill != default_marker_fill)
	{
		CString color_1;
		color_1.Format(_T("#%02X%02X%02X"),
			GetRValue(s_marker_1.marker_fill),
			GetGValue(s_marker_1.marker_fill),
			GetBValue(s_marker_1.marker_fill));
		marker->SetAttribute("fill", std::string(CT2A(color_1)).c_str());
	}
	if (s_marker_2.allow_overlap != default_marker_allow_overlap)
	{
		marker->SetAttribute("allow-overlap", "true");
	}
	if (s_marker_2.avoid_edges != default_marker_avoid_edges)
	{
		marker->SetAttribute("avoid-edges", "true");
	}
	if (s_marker_2.ignore_placement != default_marker_ignore_placement)
	{
		marker->SetAttribute("ignore-placement", "true");
	}
	if (s_marker_2.marker_spacing != default_marker_spacing)
	{
		marker->SetAttribute("spacing", std::to_string(s_marker_1.marker_spacing).c_str());
	}
	if (s_marker_2.marker_max_error != default_marker_max_error)
	{
		marker->SetAttribute("max-error", std::to_string(s_marker_1.marker_max_error).c_str());
	}
	if (s_marker_2.marker_transform != default_marker_transform)
	{
		m_marker_symbolizer.marker_transform = s_marker_2.marker_transform;
		marker->SetAttribute("transform", m_marker_symbolizer.marker_transform.c_str());
	}
	if (s_marker_2.marker_simplify != default_marker_simplify)
	{
		m_marker_symbolizer.marker_simplify = s_marker_2.marker_simplify;
		marker->SetAttribute("simplify", std::to_string(m_marker_symbolizer.marker_simplify).c_str());
	}
	if (s_marker_2.marker_simplify_algorithm != default_marker_simplify_algorithm)
	{
		marker->SetAttribute("simplify-algorithm", s_marker_2.marker_simplify_algorithm.c_str());
	}
	if (s_marker_2.marker_smooth != default_marker_smooth)
	{
		marker->SetAttribute("smooth", std::to_string(s_marker_1.marker_smooth).c_str());
	}
	if (s_marker_2.marker_geomtry_transform.compare(default_marker_geometry_transform) != 0)
	{
		marker->SetAttribute("geometry-transform", s_marker_2.marker_geomtry_transform.c_str());
	}
	if (s_marker_1.marker_compop.compare(default_marker_compop) != 0)
	{
		marker->SetAttribute("comp-op", s_marker_1.marker_compop.c_str());
	}
	if (s_marker_1.marker_direction.compare(default_marker_direction) != 0)
	{
		marker->SetAttribute("direction", s_marker_1.marker_direction.c_str());
	}
	if (s_marker_2.marker_offset != default_marker_offset)
	{
		marker->SetAttribute("offset", std::to_string(s_marker_2.marker_offset).c_str());
	}
	doc.LinkEndChild(marker);


	doc.SaveFile("marker_text.txt");

	std::fstream fs;
	fs.open("marker_text.txt", std::fstream::in | std::fstream::binary);
	//read all contents of file into string buf
	std::string buf((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

	return buf;
}


void CFormViewMarkerSymbolizer::SettingsXml(std::string xml_string)
{
	/// <summary>
	/// The function is used to set values for controls from the string xml.
	/// </summary>
	/// <param name="xml_string">The string xml.</param>
	SetDefault();
	tinyxml2::XMLDocument doc;
	doc.Parse(xml_string.c_str());
	tinyxml2::XMLElement* symbolizer = doc.FirstChildElement("MarkerSymbolizer");
	std::string default_str, clip, file, opacity, fill_opacity, stroke,
		stroke_width, stroke_opacity, placement, multi_policy, type,
		width, height, fill, allow_overlap, avoid_edges, ignore_placement,
		spacing, max_error, transform, simplify, simplify_algorithm, smooth,
		geometry_transform, offset, compop, direction;
	S_Marker marker_1;
	const tinyxml2::XMLAttribute* att_default = symbolizer->FindAttribute("default");
	default_str = GetValueAttribute(att_default);
	if (default_str.compare("") != 0)
	{
		m_button_check_marker_default.SetCheck(false);
	}
	
	const tinyxml2::XMLAttribute* att_clip = symbolizer->FindAttribute("clip");
	clip = GetValueAttribute(att_clip);
	if (clip.compare("") != 0)
	{
		marker_1.marker_clip = true;
	}
	const tinyxml2::XMLAttribute* att_file = symbolizer->FindAttribute("file");
	file = GetValueAttribute(att_file);
	if (file.compare("") != 0)
	{
		marker_1.marker_file = file;
	}
	const tinyxml2::XMLAttribute* att_opacity = symbolizer->FindAttribute("opacity");
	opacity = GetValueAttribute(att_opacity);
	if (opacity.compare("") != 0)
	{
		marker_1.marker_opacity = stof(opacity);
	}
	const tinyxml2::XMLAttribute* att_fill_opacity = symbolizer->FindAttribute("fill-opacity");
	fill_opacity = GetValueAttribute(att_fill_opacity);
	if (fill_opacity.compare("") != 0)
	{
		marker_1.marker_fill_opacity = stof(fill_opacity);
	}
	const tinyxml2::XMLAttribute* att_stroke = symbolizer->FindAttribute("stroke");
	stroke = GetValueAttribute(att_stroke );
	if (stroke.compare("") != 0)
	{
		marker_1.marker_stroke = HexStringToColor(stroke);
	}
	const tinyxml2::XMLAttribute* att_stroke_width = symbolizer->FindAttribute("stroke-width");
	stroke_width = GetValueAttribute(att_stroke_width);
	if (stroke_width.compare("") != 0)
	{
		marker_1.marker_stroke_width = stof(stroke_width);
	}
	const tinyxml2::XMLAttribute* att_stroke_opacity = symbolizer->FindAttribute("stroke-opacity");
	stroke_opacity = GetValueAttribute(att_stroke_opacity);
	if (stroke_opacity.compare("") != 0)
	{
		marker_1.marker_stroke_opacity = stof(stroke_opacity);
	}
	const tinyxml2::XMLAttribute* att_placement = symbolizer->FindAttribute("placement");
	placement = GetValueAttribute(att_placement);
	if (placement.compare("") != 0)
	{
		marker_1.marker_placement = placement;
	}
	const tinyxml2::XMLAttribute* att_multi_policy = symbolizer->FindAttribute("multi-policy");
	multi_policy = GetValueAttribute(att_multi_policy);
	if (multi_policy.compare("") != 0)
	{
		marker_1.marker_multi_policy = multi_policy;
	}
	const tinyxml2::XMLAttribute* att_type = symbolizer->FindAttribute("type");
	type = GetValueAttribute(att_type);
	if (type.compare("") != 0)
	{
		marker_1.marker_type = type;
	}
	const tinyxml2::XMLAttribute* att_width = symbolizer->FindAttribute("width");
	width = GetValueAttribute(att_width);
	if (width.compare("") != 0)
	{
		marker_1.marker_width = stof(width);
	}
	const tinyxml2::XMLAttribute* att_height = symbolizer->FindAttribute("height");
	height = GetValueAttribute(att_height);
	if (height.compare("") != 0)
	{
		marker_1.marker_height = stof(height);
	}
	const tinyxml2::XMLAttribute* att_fill = symbolizer->FindAttribute("fill");
	fill = GetValueAttribute(att_fill);
	if (fill.compare("") != 0)
	{
		marker_1.marker_fill = HexStringToColor(fill);
	}
	const tinyxml2::XMLAttribute* att_allow_overlap = symbolizer->FindAttribute("allow-overlap");
	allow_overlap = GetValueAttribute(att_allow_overlap);
	if (allow_overlap.compare("") != 0)
	{
		marker_1.allow_overlap = true;
	}
	const tinyxml2::XMLAttribute* att_avoid_edges = symbolizer->FindAttribute("avoid-edges");
	avoid_edges = GetValueAttribute(att_avoid_edges);
	if (avoid_edges.compare("") != 0)
	{
		marker_1.avoid_edges = true;
	}
	const tinyxml2::XMLAttribute* att_ignore_placement = symbolizer->FindAttribute("ignore-placement");
	ignore_placement = GetValueAttribute(att_ignore_placement);
	if (ignore_placement.compare("") != 0)
	{
		marker_1.ignore_placement = true;
	}
	const tinyxml2::XMLAttribute* att_spacing = symbolizer->FindAttribute("spacing");
	spacing = GetValueAttribute(att_spacing);
	if (spacing.compare("") != 0)
	{
		marker_1.marker_spacing = stof(spacing);
	}
	const tinyxml2::XMLAttribute* att_max_error = symbolizer->FindAttribute("max-error");
	max_error = GetValueAttribute(att_max_error);
	if (max_error.compare("") != 0)
	{
		marker_1.marker_max_error = stof(max_error);
	}
	const tinyxml2::XMLAttribute* att_transform = symbolizer->FindAttribute("transform");
	transform = GetValueAttribute(att_transform);
	if (transform.compare("") != 0)
	{
		marker_1.marker_transform = transform;
	}
	const tinyxml2::XMLAttribute* att_simplify = symbolizer->FindAttribute("simplify");
	simplify = GetValueAttribute(att_simplify);
	if (simplify.compare("") != 0)
	{
		marker_1.marker_simplify = stof(simplify);
	}
	const tinyxml2::XMLAttribute* att_simplify_algorithm = symbolizer->FindAttribute("simplify-algorithm");
	simplify_algorithm = GetValueAttribute(att_simplify_algorithm);
	if (simplify_algorithm.compare("") != 0)
	{
		marker_1.marker_simplify_algorithm = simplify_algorithm;
	}
	const tinyxml2::XMLAttribute* att_smooth = symbolizer->FindAttribute("smooth");
	smooth = GetValueAttribute(att_smooth);
	if (smooth.compare("") != 0)
	{
		marker_1.marker_smooth = stof(smooth);
	}
	const tinyxml2::XMLAttribute* att_geometry_transform = symbolizer->FindAttribute("geometry-transform");
	geometry_transform = GetValueAttribute(att_geometry_transform);
	if (geometry_transform.compare("") != 0)
	{
		marker_1.marker_geomtry_transform = geometry_transform;
	}
	const tinyxml2::XMLAttribute* att_offset = symbolizer->FindAttribute("offset");
	offset = GetValueAttribute(att_offset);
	if (offset.compare("") != 0)
	{
		marker_1.marker_offset = stof(offset);
	}
	const tinyxml2::XMLAttribute* att_compop = symbolizer->FindAttribute("comp-op");
	compop = GetValueAttribute(att_compop);
	if (compop.compare("") != 0)
	{
		marker_1.marker_compop = compop;
	}
	const tinyxml2::XMLAttribute* att_direction = symbolizer->FindAttribute("direction");
	direction = GetValueAttribute(att_direction);
	if (direction.compare("") != 0)
	{
		marker_1.marker_direction = direction;
	}
	CTabMarker1* tab1 = (CTabMarker1*)m_tabctrl_marker.m_tabPages[0];
	CTabMarker2* tab2 = (CTabMarker2*)m_tabctrl_marker.m_tabPages[1];
	tab1->SetMarkerTab1(marker_1);
	tab2->SetMarkerTab2(marker_1);
}

BOOL CFormViewMarkerSymbolizer::CreateView(CWnd* pParent, CCreateContext* pContext)
{
	CRect rect(0, 0, 300, 300);
	if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, rect,
		pParent, AFX_IDW_PANE_FIRST, pContext))
	{
		TRACE0("Warning: couldn't create CFormViewPolygonSymbolizer!\n");
		return FALSE;
	}
	
	return TRUE;
}

BEGIN_MESSAGE_MAP(CFormViewMarkerSymbolizer, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_PLACEMENT, &CFormViewMarkerSymbolizer::OnCbnSelchangeComboMarkerPlacement)
	ON_BN_CLICKED(IDC_MARKER_BUTTON_APPLY, &CFormViewMarkerSymbolizer::OnBnClickedMarkerButtonApply)
	ON_BN_CLICKED(IDC_MARKER_BUTTON_CANCEL, &CFormViewMarkerSymbolizer::OnBnClickedMarkerButtonCancel)
	ON_WM_MOUSEACTIVATE()
	ON_BN_CLICKED(IDC_CHECK_MARKER_DEFAULT, &CFormViewMarkerSymbolizer::OnBnClickedCheckMarkerDefault)
	ON_EN_SETFOCUS(IDC_EDIT_SCRIPT_MARKER, &CFormViewMarkerSymbolizer::OnFocusScriptMarker)
END_MESSAGE_MAP()


// CFormViewMarkerSymbolizer diagnostics

#ifdef _DEBUG
void CFormViewMarkerSymbolizer::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewMarkerSymbolizer::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormViewMarkerSymbolizer message handlers
int CFormViewMarkerSymbolizer::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CFormViewMarkerSymbolizer::OnCbnSelchangeComboMarkerPlacement()
{
	// TODO: Add your control notification handler code here
}


void CFormViewMarkerSymbolizer::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_tabctrl_marker.InsertItem(0, _T("Tab One"));
	m_tabctrl_marker.InsertItem(1, _T("Tab Two"));
	
	m_tabctrl_marker.Init();


	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);
	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	
	int check_Create_Database = m_ToolTip.CreateDatabaseTooltip();
	
	m_ToolTip.ReadDatabaseTooltip();
	
	m_ToolTip.SetParams(&params);

	m_ToolTip.AddTool(GetDlgItem(IDC_TAB_MARKER_SYMBOLIZER), _T("This is Tab!"));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_MARKER_DEFAULT), _T(
		"Document"
	));
	
	// m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_SPACING), _T("This is Cancel button!"));
}


void CFormViewMarkerSymbolizer::OnBnClickedMarkerButtonApply()
{
	// TODO: Add your control notification handler code here
}


void CFormViewMarkerSymbolizer::OnBnClickedMarkerButtonCancel()
{
	// TODO: Add your control notification handler code here
}


BOOL CFormViewMarkerSymbolizer::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
		m_ToolTip.RelayEvent(pMsg);
		break;
	}
	return CBCGPFormView::PreTranslateMessage(pMsg);
}


void CFormViewMarkerSymbolizer::OnBnClickedCheckMarkerDefault()
{
	// TODO: Add your control notification handler code here
	if (m_button_check_marker_default.GetCheck() == 1)
	{
		CTabMarker1* tab1 = (CTabMarker1*)m_tabctrl_marker.m_tabPages[0];
		CTabMarker2* tab2 = (CTabMarker2*)m_tabctrl_marker.m_tabPages[1];
		tab1->SetDefault();
		tab2->SetDefault2();
	}
	SetTextScript();
}


void CFormViewMarkerSymbolizer::OnFocusScriptMarker()
{
	// TODO: Add your control notification handler code here
	SetTextScript();
}
