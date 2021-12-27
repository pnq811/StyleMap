// TabMarker2.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "TabMarker2.h"
#include "afxdialogex.h"
#include <string>
#include "MainFrm.h"

// CTabMarker2 dialog

IMPLEMENT_DYNAMIC(CTabMarker2, CBCGPDialog)

CTabMarker2::CTabMarker2(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_TAB_MARKER_2, pParent)
{
	
}

CTabMarker2::~CTabMarker2()
{
}

void CTabMarker2::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_MARKER_ALLOW_OVERLAP, m_marker_allow_overlap_button_check);
	DDX_Control(pDX, IDC_CHECK_MARKER_IGNORE_PLACEMENT, m_marker_ignore_placement_checkbox);
	DDX_Control(pDX, IDC_CHECK_MARKER_AVOID_EDGES, m_marker_avoid_edges_checkbox);
	DDX_Control(pDX, IDC_COMBO_MARKER_SIMPLIFY_ALGORITHM, m_marker_simplify_algorithm_combo);
	DDX_Control(pDX, IDC_STATIC_MARKER_SIMPLIFY_ALGORITHM, m_marker_simplify_algorithm_static);
	DDX_Control(pDX, IDC_COMBO_MARKER_TRANSFORM, m_marker_transform_combo);
	DDX_Control(pDX, IDC_COMBO_MARKER_GEOMETRY_TRANSFORM, m_marker_geometry_transform_combo);
	DDX_Control(pDX, IDC_EDIT_MARKER_OFFSET, m_marker_offset_edit);
	DDX_Control(pDX, IDC_EDIT_MARKER_SIMPLIFY, m_marker_simplify_edit);
	DDX_Control(pDX, IDC_EDIT_MARKER_SMOOTH, m_marker_smooth_edit);
	DDX_Control(pDX, IDC_EDIT_MARKER_MAX_ERROR, m_marker_max_error_edit);
	DDX_Control(pDX, IDC_EDIT_MARKER_SPACING, m_marker_spacing_edit);
	DDX_Control(pDX, IDC_CHECK_MARKER_CLIP, m_marker_clip_button);
}




BEGIN_MESSAGE_MAP(CTabMarker2, CDialog)
	ON_STN_CLICKED(IDC_STATIC_MARKER_HEIGHT, &CTabMarker2::OnStnClickedStaticMarkerHeight)
	ON_BN_CLICKED(IDC_CHECK_MARKER_ALLOW_OVERLAP, &CTabMarker2::OnKillFocusTab2)
	ON_BN_KILLFOCUS(IDC_MFCCOLORBUTTON_MARKER_STROKE, &CTabMarker2::OnKillFocusTab2)
	ON_CBN_KILLFOCUS(IDC_COMBO_MARKER_SIMPLIFY_ALGORITHM, &CTabMarker2::OnKillFocusTab2)
	ON_BN_KILLFOCUS(IDC_CHECK_MARKER_ALLOW_OVERLAP, &CTabMarker2::OnKillFocusTab2)
	ON_BN_KILLFOCUS(IDC_CHECK_MARKER_IGNORE_PLACEMENT, &CTabMarker2::OnKillFocusTab2)
	ON_BN_KILLFOCUS(IDC_CHECK_MARKER_AVOID_EDGES, &CTabMarker2::OnKillFocusTab2)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_OFFSET, &CTabMarker2::OnKillFocusTab2)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_SIMPLIFY, &CTabMarker2::OnKillFocusTab2)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_TRANSFORM, &CTabMarker2::OnKillFocusTab2)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_GEOMETRY_TRANSFORM, &CTabMarker2::OnKillFocusTab2)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_SMOOTH, &CTabMarker2::OnKillFocusTab2)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_MAX_ERROR, &CTabMarker2::OnKillFocusTab2)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_SPACING, &CTabMarker2::OnKillFocusTab2)
	ON_BN_KILLFOCUS(IDC_CHECK_MARKER_CLIP, &CTabMarker2::OnKillFocusTab2)
	ON_CBN_KILLFOCUS(IDC_COMBO_MARKER_TRANSFORM, &CTabMarker2::OnKillFocusTab2)
	ON_CBN_KILLFOCUS(IDC_COMBO_MARKER_GEOMETRY_TRANSFORM, &CTabMarker2::OnKillFocusTab2)


	ON_STN_CLICKED(IDC_STATIC_MARKER_FILL, &CTabMarker2::OnStnClickedStaticMarkerFill)
	
	ON_BN_CLICKED(IDC_CHECK_MARKER_IGNORE_PLACEMENT, &CTabMarker2::OnKillFocusTab2)
	ON_BN_CLICKED(IDC_CHECK_MARKER_AVOID_EDGES, &CTabMarker2::OnKillFocusTab2)
	ON_BN_CLICKED(IDC_CHECK_MARKER_CLIP, &CTabMarker2::OnKillFocusTab2)
END_MESSAGE_MAP()


// CTabMarker2 message handlers


BOOL CTabMarker2::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	AddMarkerTransform();
	
	AddMarkerGeometryTransform();
	AddMarkerSimplifyAlgorithm();
	m_marker_geometry_transform_combo.AddString(_T("none"));
	m_marker_transform_combo.AddString(_T("none"));
	SetDefault2();
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);
	
	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	
	m_ToolTip.SetParams(&params);
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_MARKER_SIMPLIFY_ALGORITHM),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_MARKER_TRANSFORM),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_MARKER_GEOMETRY_TRANSFORM),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_MAX_ERROR),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_SIMPLIFY),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_SPACING),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_MARKER_CLIP),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_SMOOTH),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_OFFSET),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_MARKER_IGNORE_PLACEMENT),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_MARKER_ALLOW_OVERLAP),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_MARKER_AVOID_EDGES),
		_T("Document"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CTabMarker2::OnStnClickedStaticMarkerHeight()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker2::OnCbnSelchangeComboMarkerMarkerType()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker2::OnBnClickedCheckMarkerAllowOverlap()
{
	// TODO: Add your control notification handler code here
}

void CTabMarker2::AddMarkerSimplifyAlgorithm()
{
	for (int i = 0; i < 4; i++)
	{
		m_marker_simplify_algorithm_combo.AddString(
			CString(marker_simplify_algorithm[i].c_str())
		);
	}
}

void CTabMarker2::AddMarkerGeometryTransform()
{
	std::map<std::string, int>::iterator it;
	for (it = marker_geometry_transform_map.begin();
		it != marker_geometry_transform_map.end(); it++)
	{
		m_marker_geometry_transform_combo.AddString(CString(it->first.c_str()));
	}
}

void CTabMarker2::AddMarkerTransform()
{
	std::map<std::string, int>::iterator it;
	for (it = marker_transform_map.begin();
		it != marker_transform_map.end(); it++)
	{
		m_marker_transform_combo.AddString(CString(it->first.c_str()));
	}
}

void CTabMarker2::SetDefault2()
{
	m_marker_clip_button.SetCheck(default_marker_clip);
	m_marker_simplify_algorithm_combo.SetCurSel(
		m_marker_simplify_algorithm_combo.FindStringExact(
			0, CString(default_marker_simplify_algorithm.c_str())
		)
	);
	m_marker_allow_overlap_button_check.SetCheck(
		default_marker_allow_overlap
	);
	m_marker_avoid_edges_checkbox.SetCheck(
		default_marker_avoid_edges
	);
	m_marker_geometry_transform_combo.SetCurSel(
		m_marker_geometry_transform_combo.FindStringExact(0,
			CString(default_marker_geometry_transform.c_str()))
	);
	m_marker_transform_combo.SetCurSel(
		m_marker_transform_combo.FindStringExact(0, CString(
			default_marker_transform.c_str()))
	);
	m_marker_ignore_placement_checkbox.SetCheck(
		default_marker_ignore_placement
	);
	std::string default_marker_max_error_str = std::to_string(default_marker_max_error);
	m_marker_max_error_edit.SetWindowTextW(CString(
		default_marker_max_error_str.c_str()));
	std::string default_marker_smooth_str = std::to_string(default_marker_smooth);
	m_marker_smooth_edit.SetWindowTextW(CString(
		default_marker_smooth_str.c_str()));
	

	std::string default_marker_simplify_str = std::to_string(default_marker_simplify);
	m_marker_simplify_edit.SetWindowTextW(CString(
		default_marker_simplify_str.c_str()));
	std::string default_marker_offset_str = std::to_string(default_marker_offset);
	m_marker_offset_edit.SetWindowTextW(
		CString(default_marker_offset_str.c_str())
	);
	std::string default_marker_spacing_str = std::to_string(default_marker_spacing);
	m_marker_spacing_edit.SetWindowTextW(CString(
		default_marker_spacing_str.c_str()));
	
	

	

	
	
	
}
std::vector<std::string> CTabMarker2::TokenizeString(std::string in_str, const char delimeter)
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
void CTabMarker2::SetMarkerTab2(S_Marker& t_marker)
{
	if (t_marker.marker_simplify_algorithm.compare(default_marker_simplify_algorithm) != 0)
	{
		m_marker_simplify_algorithm_combo.SetCurSel(m_marker_simplify_algorithm_combo.FindStringExact(
			0, CString(t_marker.marker_simplify_algorithm.c_str())
		));
	}
	if (t_marker.marker_spacing != default_marker_spacing)
	{
		m_marker_spacing_edit.SetWindowTextW(CString(std::to_string(t_marker.marker_spacing).c_str()));
	}
	if (t_marker.marker_max_error != default_marker_max_error)
	{
		m_marker_max_error_edit.SetWindowTextW(CString(std::to_string(t_marker.marker_max_error).c_str()));
	}
	
	if (t_marker.marker_transform.compare(default_marker_transform) != 0)
	{
		
		m_marker_transform_combo.SetWindowTextW(
			CString(t_marker.marker_transform.c_str()));

	}
	if (t_marker.marker_geomtry_transform.compare(default_marker_geometry_transform) != 0)
	{
		m_marker_geometry_transform_combo.SetWindowTextW(
			CString(t_marker.marker_geomtry_transform.c_str()));
		
	}
	if (t_marker.marker_simplify != default_marker_simplify)
	{
		m_marker_simplify_edit.SetWindowTextW(CString(std::to_string(
			t_marker.marker_simplify).c_str()));
	}
	if (t_marker.marker_smooth != default_marker_smooth)
	{
		m_marker_smooth_edit.SetWindowTextW(CString(std::to_string(
			t_marker.marker_smooth).c_str()));
	}
	if (t_marker.marker_offset != default_marker_offset)
	{
		m_marker_offset_edit.SetWindowTextW(CString(std::to_string(
			t_marker.marker_offset).c_str()));
	}
	
	if (t_marker.ignore_placement != default_marker_ignore_placement)
	{
		m_marker_ignore_placement_checkbox.SetCheck(true);
	}
	if (t_marker.avoid_edges != default_marker_avoid_edges)
	{
		m_marker_avoid_edges_checkbox.SetCheck(true);
	}
	if (t_marker.allow_overlap != default_marker_allow_overlap)
	{
		m_marker_allow_overlap_button_check.SetCheck(true);
	}
	if (t_marker.marker_clip != default_marker_clip)
	{
		m_marker_clip_button.SetCheck(true);
	}
}


S_Marker CTabMarker2::GetMarkerSymbolizer()
{
	S_Marker t_marker;
	CString stroke_width_cstr, smooth_cstr, offset_cstr, spacing_cstr, marker_type_cstr, geo_transform_cstr,
		max_error_cstr, transform_cstr, multi_policy_cstr, simplify_algorithm_cstr, simplify_cstr;
	CString param_transform;
	
	m_marker_spacing_edit.GetWindowTextW(spacing_cstr);
	m_marker_simplify_algorithm_combo.GetWindowTextW(simplify_algorithm_cstr);
	m_marker_smooth_edit.GetWindowTextW(smooth_cstr);
	m_marker_transform_combo.GetWindowTextW(transform_cstr);
	m_marker_offset_edit.GetWindowTextW(offset_cstr);
	CString param_geo_transform;
	m_marker_geometry_transform_combo.GetWindowTextW(geo_transform_cstr);
	m_marker_simplify_edit.GetWindowTextW(simplify_cstr);
	m_marker_max_error_edit.GetWindowTextW(max_error_cstr);
	
	t_marker.marker_simplify_algorithm = CW2A(simplify_algorithm_cstr);
	
	t_marker.marker_clip = m_marker_clip_button.GetCheck();
	t_marker.allow_overlap = m_marker_allow_overlap_button_check.GetCheck();
	t_marker.avoid_edges = m_marker_avoid_edges_checkbox.GetCheck();
	t_marker.ignore_placement = m_marker_ignore_placement_checkbox.GetCheck();
	if (!CheckValidNumberFromString(std::string(CT2A(spacing_cstr))))
	{
		m_marker_spacing_edit.SetWindowTextW(CString(
			std::to_string(default_marker_spacing).c_str()));
		t_marker.marker_spacing = default_marker_spacing;
		AfxMessageBox(_T("Spacing is not a valid number!"));
	}
	else
	{
		t_marker.marker_spacing = _tstof(spacing_cstr);
	}
	if (!CheckValidNumberFromString(std::string(CT2A(max_error_cstr))))
	{
		m_marker_max_error_edit.SetWindowTextW(CString(
			std::to_string(default_marker_max_error).c_str()));
		t_marker.marker_max_error = default_marker_max_error;
		AfxMessageBox(_T("Max error opacity is not a valid number!"));
	}
	else
	{
		t_marker.marker_max_error = _tstof(max_error_cstr);
	}
	if (std::string(CT2A(transform_cstr)).compare(default_marker_transform) != 0)
	{
		t_marker.marker_transform = CW2A(transform_cstr);
	}
	else
	{
		t_marker.marker_transform = CW2A(transform_cstr);
	}
	if (!CheckValidNumberFromString(std::string(CT2A(smooth_cstr))))
	{
		m_marker_smooth_edit.SetWindowTextW(CString(
			std::to_string(default_marker_smooth).c_str()));
		t_marker.marker_smooth = default_marker_smooth;
		AfxMessageBox(_T("Smooth is not a valid number!"));
	}
	else
	{
		t_marker.marker_smooth = _tstof(smooth_cstr);
	}
	
	
	
	if (std::string(CT2A(geo_transform_cstr)).compare(default_marker_geometry_transform) != 0)
	{
		t_marker.marker_geomtry_transform = CW2A(geo_transform_cstr);
	}
	else
	{
		t_marker.marker_geomtry_transform = CW2A(geo_transform_cstr);
	}
	if (!CheckValidNumberFromString(std::string(CT2A(offset_cstr))))
	{
		m_marker_offset_edit.SetWindowTextW(CString(
			std::to_string(default_marker_offset).c_str()));
		t_marker.marker_offset = default_marker_offset;
		AfxMessageBox(_T("Offset is not a valid number!"));
	}
	else {
		t_marker.marker_offset = _tstof(offset_cstr);
	}
	if (!CheckValidNumberFromString(std::string(CT2A(simplify_cstr))))
	{
		m_marker_simplify_edit.SetWindowTextW(CString(
			std::to_string(default_marker_simplify).c_str()));
		t_marker.marker_simplify = default_marker_simplify;
		AfxMessageBox(_T("Simplify is not a valid number!"));
	}
	else {
		t_marker.marker_simplify = _tstof(simplify_cstr);
	}
	return S_Marker(t_marker);
}

BOOL CTabMarker2::PreTranslateMessage(MSG* pMsg)
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
	return CBCGPDialog::PreTranslateMessage(pMsg);
}

int CTabMarker2::CheckValidNumberFromString(std::string strNum)
{
	int i = 0, j = strNum.length() - 1;
	while (i < strNum.length() && strNum[i] == ' ')
		i++;
	while (j >= 0 && strNum[j] == ' ')
		j--;
	if (i > j)
		return 0;
	if (i == j && !(strNum[i] >= '0' && strNum[i] <= '9'))
		return 0;
	if (strNum[i] != '.' && strNum[i] != '+' && strNum[i] != '-' && !(strNum[i] >= '0' && strNum[i] <= '9'))
		return 0;
	bool flagDotOrE = false;
	for (i; i <= j; i++) {
		// If any of the char does not belong to
		// {digit, +, -, ., e}
		if (strNum[i] != 'e' && strNum[i] != '.'
			&& strNum[i] != '+' && strNum[i] != '-'
			&& !(strNum[i] >= '0' && strNum[i] <= '9'))
			return 0;
		if (strNum[i] == '.') {
			if (flagDotOrE == true)
				return 0;
			if (i + 1 > strNum.length())
				return 0;
			if (!(strNum[i + 1] >= '0' && strNum[i + 1] <= '9'))
				return 0;
		}
		else if (strNum[i] == 'e') {
			flagDotOrE = true;
			if (!(strNum[i - 1] >= '0' && strNum[i - 1] <= '9'))
				return 0;
			if (i + 1 > strNum.length())
				return 0;
			if (strNum[i + 1] != '+' && strNum[i + 1] != '-'
				&& (strNum[i + 1] >= '0' && strNum[i] <= '9'))
				return 0;
		}
	}
	return 1;
}


void CTabMarker2::OnKillFocusTab2()
{
	// TODO: Add your control notification handler code here
	CMainFrame* mainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	
	if (mainFrame != NULL)
	{
		mainFrame->m_wndMarkerSymbolizer.m_pFormViewMarker->SetTextScript();
	}
}


void CTabMarker2::OnStnClickedStaticMarkerFill()
{
	// TODO: Add your control notification handler code here
}




void CTabMarker2::OnBnClickedCheckMarkerIgnorePlacement()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker2::OnBnClickedCheckMarkerAvoidEdges()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker2::OnBnClickedCheckMarkerClip()
{
	// TODO: Add your control notification handler code here
}
