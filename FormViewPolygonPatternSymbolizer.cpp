// FormViewPolygonPatternSymbolizer.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "FormViewPolygonPatternSymbolizer.h"
#include <sstream>
#include "tinyxml2.h"
#include <fstream>
// CFormViewPolygonPatternSymbolizer

IMPLEMENT_DYNCREATE(CFormViewPolygonPatternSymbolizer, CBCGPFormView)

CFormViewPolygonPatternSymbolizer::CFormViewPolygonPatternSymbolizer()
	: CBCGPFormView(IDD_CFormViewPolygonPatternSymbolizer)
{

}

CFormViewPolygonPatternSymbolizer::~CFormViewPolygonPatternSymbolizer()
{
}

void CFormViewPolygonPatternSymbolizer::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_POLYGON_PATTERN_FILE, m_edit_polygon_pattern_file);
	DDX_Control(pDX, IDC_EDIT_POLYGON_PATTERN_GAMMA, m_edit_polygon_pattern_gamma);
	DDX_Control(pDX, IDC_EDIT_SIMPLIFY_POLYGON_PATTERN, m_edit_polygon_pattern_simplify);

	DDX_Control(pDX, IDC_EDIT_SMOOTH_POLYGON_PATTERN, m_edit_polygon_pattern_smooth);

	DDX_Control(pDX, IDC_CHECK_POLYGON_PATTERN_DEFAULT, m_button_polygon_pattern_default);
	DDX_Control(pDX, IDC_COMBO_POLYGON_PATTERN_ALIGNMENT, m_combo_polygon_pattern_alignment);
	DDX_Control(pDX, IDC_CHECK_POLYGON_PATTERN_CLIP, m_polygon_pattern_clip);
	DDX_Control(pDX, IDC_COMBO_POLYGON_PATTERN_SIMPLIFY_ALGORITHM, m_combo_polygon_pattern_simplify_algorithm);
	DDX_Control(pDX, IDC_COMBO_POLYGON_PATTERN_GEOMETRY_TRANSFORM, m_combo_polygon_pattern_geometry_transform);
	DDX_Control(pDX, IDC_COMBO_POLYGON_PATTERN_TRANSFORM, m_combo_polygon_pattern_transform);
	DDX_Control(pDX, IDC_COMBO_POLYGON_PATTERN_COMPOP, m_combo_polygon_pattern_compop);
	DDX_Control(pDX, IDC_EDIT_POLYGON_PATTERN_OPACITY, m_edit_polygon_pattern_opacity);

	DDX_Control(pDX, IDC_EDIT_TEXT_POLYGON_PATTERN, m_script_polygon_pattern);
	DDX_Control(pDX, IDC_STATIC_POLYGON_PATTEN_FOLDER, m_polygon_pattern_open_folder_static);
}

BOOL CFormViewPolygonPatternSymbolizer::CreateView(CWnd* pParent, CCreateContext* pContext)
{
	CRect rect(0, 0, 300, 300);

	if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		rect, pParent, AFX_IDW_PANE_FIRST, pContext))
	{
		TRACE0("Warning: couldn't create CFormViewPolygonPatternSymbolizer!\n");
		return FALSE;
	}
	
	return TRUE;
}

int CFormViewPolygonPatternSymbolizer::CheckValidNumberFromString(std::string strNum)
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



void CFormViewPolygonPatternSymbolizer::AddPolygonPatternAlignment()
{
	for (int i = 0; i < 2; i++)
	{
		m_combo_polygon_pattern_alignment.AddString(
			CString(polygon_pattern_alignment[i].c_str()
			));
	}
}

void CFormViewPolygonPatternSymbolizer::AddPolygonPatternSimplifyAlgorithm()
{
	for (int i = 0; i < 4; i++)
	{
		m_combo_polygon_pattern_simplify_algorithm.AddString(
			CString(polygon_pattern_simplify_algorithm[i].c_str())
		);
	}
}

void CFormViewPolygonPatternSymbolizer::AddPolygonPatternGeometryTransform()
{
	m_combo_polygon_pattern_geometry_transform.AddString(_T("none"));
	std::map<std::string, int>::iterator it;
	for (it = polygon_pattern_geometry_transform_map.begin();
		it != polygon_pattern_geometry_transform_map.end(); it++)
	{
		m_combo_polygon_pattern_geometry_transform.AddString(CString(it->first.c_str()));
	}
}

void CFormViewPolygonPatternSymbolizer::AddPolygonPatternTransform()
{
	m_combo_polygon_pattern_transform.AddString(_T("none"));
	std::map<std::string, int>::iterator it;
	for (it = polygon_pattern_transform_map.begin();
		it != polygon_pattern_transform_map.end(); it++)
	{
		m_combo_polygon_pattern_transform.AddString(CString(it->first.c_str()));
	}
}

void CFormViewPolygonPatternSymbolizer::AddPolygonPatternCompOp()
{
	for (int i = 0; i < 37; i++)
	{
		m_combo_polygon_pattern_compop.AddString(
			CString(m_polygon_pattern_compop_type[i].c_str())
		);
	}
}

void CFormViewPolygonPatternSymbolizer::SetDefault()
{
	m_combo_polygon_pattern_alignment.SetCurSel(
		m_combo_polygon_pattern_alignment.FindStringExact(
			0, CString(default_polygon_pattern_alignment.c_str())
	)
	);
	m_combo_polygon_pattern_compop.SetCurSel(
		m_combo_polygon_pattern_compop.FindStringExact(
			0, CString(default_polygon_pattern_compop.c_str())
		)
	);
	m_combo_polygon_pattern_geometry_transform.SetCurSel(
		m_combo_polygon_pattern_geometry_transform.FindStringExact(
			0, CString(default_polygon_pattern_geometry_transform.c_str())
		)
	);
	m_combo_polygon_pattern_transform.SetCurSel(
		m_combo_polygon_pattern_transform.FindStringExact(
			0, CString(default_polygon_pattern_transform.c_str())
		)
	);
	m_combo_polygon_pattern_simplify_algorithm.SetCurSel(
		m_combo_polygon_pattern_simplify_algorithm.FindStringExact(
			0, CString(default_polygon_pattern_simplify_algorithm.c_str())
		)
	);
	m_edit_polygon_pattern_file.SetWindowTextW(
		CString(default_polygon_pattern_file.c_str())
	);
	std::string default_polygon_pattern_gamma_str =
		std::to_string(default_polygon_pattern_gamma);
	m_edit_polygon_pattern_gamma.SetWindowTextW(
		CString(default_polygon_pattern_gamma_str.c_str())
	);

	std::string default_polygon_pattern_opacity_str =
		std::to_string(default_polygon_pattern_opacity);
	m_edit_polygon_pattern_opacity.SetWindowTextW(
		CString(default_polygon_pattern_opacity_str.c_str())
	);
	std::string default_polygon_pattern_simplify_str =
		std::to_string(default_polygon_pattern_simplify);
	m_edit_polygon_pattern_simplify.SetWindowTextW(
		CString(default_polygon_pattern_simplify_str.c_str())
	);
	std::string default_polygon_pattern_smooth_str =
		std::to_string(default_polygon_pattern_smooth);
	m_edit_polygon_pattern_smooth.SetWindowTextW(
		CString(default_polygon_pattern_smooth_str.c_str())
	);
	// m_button_polygon_pattern_default.SetCheck(0);
	m_polygon_pattern_clip.SetCheck(default_polygon_pattern_clip);
}

std::string CFormViewPolygonPatternSymbolizer::SettingsXml()
{
	
	/// <summary>
   /// The function is used to get string of tinyxml for attribute in polygon symbolizer formview
   /// from the controls.
   /// </summary>
   /// <returns>The string </returns>
	
	tinyxml2::XMLDocument doc;

	
	tinyxml2::XMLElement* polygon_pattern_symbolizer =
		doc.NewElement("PolygonPatternSymbolizer");

	
	std::string alignment, gamma, opacity, clip, simplify,
		simplify_algorithm, smooth, geometry_transform, transform,
		comp_op, file_str;
	std::string result ="<PolygonPatternSymbolizer ";
	CString alignment_cstr;
	m_combo_polygon_pattern_alignment.GetWindowTextW(alignment_cstr);
	alignment = CT2A(alignment_cstr);

	if (alignment.compare(default_polygon_pattern_alignment) != 0)
	{
		result = result + "alignment=\"" + alignment + "\"";
		polygon_pattern_symbolizer->SetAttribute("alignment", alignment.c_str());
	}
	
	CString gamma_cstr; m_edit_polygon_pattern_gamma.GetWindowTextW(gamma_cstr);
	gamma = CT2A(gamma_cstr);
	if (!CheckValidNumberFromString(gamma))
	{
		m_edit_polygon_pattern_gamma.SetWindowTextW(
			CString(std::to_string(default_polygon_pattern_gamma).c_str()));
		AfxMessageBox(_T("Gamma is not a valid number!!"));
		
		UpdateData(FALSE);
	}
	else
	{
		float value_gamma;
		value_gamma = atof(gamma.c_str());
		if (value_gamma != default_polygon_pattern_gamma)
		{
			if (value_gamma >= 0 && value_gamma <= 1)
			{
				polygon_pattern_symbolizer->SetAttribute("gamma", std::to_string(value_gamma).c_str());
			}
		}
	}
	CString opacity_cstr; m_edit_polygon_pattern_opacity.GetWindowTextW(opacity_cstr);
	opacity = CT2A(opacity_cstr);
	if (!CheckValidNumberFromString(opacity))
	{
		m_edit_polygon_pattern_opacity.SetWindowTextW(
			CString(std::to_string(default_polygon_pattern_opacity).c_str()));
		AfxMessageBox(_T("Opacity is not a valid number!!"));
		UpdateData(FALSE);
	}
	else
	{
		float value_opacity;
		value_opacity = atof(opacity.c_str());
		if (value_opacity != default_polygon_pattern_opacity)
		{
			result = result + " opacity=\"" + std::to_string(value_opacity) + "\"";
			polygon_pattern_symbolizer->SetAttribute("opacity", std::to_string(value_opacity).c_str());
		}
	}
	CString simplify_cstr;
	m_edit_polygon_pattern_simplify.GetWindowTextW(simplify_cstr);
	simplify = CT2A(simplify_cstr);
	if (!CheckValidNumberFromString(simplify))
	{
		m_edit_polygon_pattern_simplify.SetWindowTextW(
			CString(std::to_string(default_polygon_pattern_simplify).c_str()));
		AfxMessageBox(_T("Simplify is not a valid number!!"));
		UpdateData(FALSE);
	}
	else
	{
		float value_simplify;
		value_simplify = atof(simplify.c_str());
		if (value_simplify != default_polygon_pattern_simplify)
		{
			result = result + " simplify=\"" + std::to_string(value_simplify) + "\"";
			polygon_pattern_symbolizer->SetAttribute("simplify", std::to_string(value_simplify).c_str());
		}
	}
	CString smooth_cstr;
	m_edit_polygon_pattern_smooth.GetWindowTextW(smooth_cstr);
	smooth = CT2A(smooth_cstr);
	if(!CheckValidNumberFromString(smooth))
	{
		m_edit_polygon_pattern_smooth.SetWindowTextW(
			CString(std::to_string(default_polygon_pattern_smooth).c_str()));
		AfxMessageBox(_T("Smooth is not a valid number!!"));
		UpdateData(FALSE);
	}
	else
	{
		float value_smooth;
		value_smooth = atof(smooth.c_str());
		if (value_smooth != default_polygon_pattern_smooth)
		{
			result = result + " smooth=\"" + std::to_string(value_smooth) + "\"";
			polygon_pattern_symbolizer->SetAttribute("smooth", std::to_string(value_smooth).c_str());
		}
	}
	CString simplify_algorithm_cstr;
	m_combo_polygon_pattern_simplify_algorithm.GetWindowTextW(simplify_algorithm_cstr);
	simplify_algorithm = CT2A(simplify_algorithm_cstr);
	if (simplify_algorithm.compare(default_polygon_pattern_simplify_algorithm) != 0)
	{
		result = result + " simplify-algorithm=\"" + simplify_algorithm + "\"";
		polygon_pattern_symbolizer->SetAttribute("simplify-algorithm", simplify_algorithm.c_str());
	}
	CString geo_transform_cstr, geo_transform_params;
	m_combo_polygon_pattern_geometry_transform.GetWindowTextW(
		geo_transform_cstr
	);
	geometry_transform = CT2A(geo_transform_cstr);
	if (geometry_transform.compare(default_polygon_pattern_geometry_transform) != 0)
	{
		geometry_transform = CT2A(geo_transform_cstr);
		result = result + " geometry_transform=\"" + geometry_transform
			+ "\"";
		polygon_pattern_symbolizer->SetAttribute("geometry-transform", geometry_transform.c_str());
	}

	CString transform_cstr, transform_params;
	m_combo_polygon_pattern_transform.GetWindowTextW(
		transform_cstr
	);
	

	transform = CT2A(transform_cstr);
	if (transform.compare(default_polygon_pattern_transform) != 0)
	{
		transform = CT2A(transform_cstr);
		result = result + " transform=\"" + transform
			+ "\"";
		polygon_pattern_symbolizer->SetAttribute("transform", transform.c_str());
	}
	CString file_cstr;
	m_edit_polygon_pattern_file.GetWindowTextW(file_cstr);
	file_str = CT2A(file_cstr);
	if (file_str.compare(default_polygon_pattern_file) != 0)
	{
		result = result + " file=\"" + file_str
			+ "\"";
		polygon_pattern_symbolizer->SetAttribute("file", file_str.c_str());
	}

	CString compop_cstr;
	m_combo_polygon_pattern_compop.GetWindowTextW(
		compop_cstr
	);
	comp_op = CT2A(compop_cstr);
	if (comp_op.compare(default_polygon_pattern_compop) != 0)
	{
		result = result + " comp-op=\"" + comp_op
			+ "\"";
		polygon_pattern_symbolizer->SetAttribute("comp-op", comp_op.c_str());
	}

	if (m_polygon_pattern_clip.GetCheck() != default_polygon_pattern_clip)
	{
		result = result + " clip=\"" + "true"
			+ "\"";
		polygon_pattern_symbolizer->SetAttribute("clip", "true");
	}
	result = result + "/>";
	doc.LinkEndChild(polygon_pattern_symbolizer);

	doc.SaveFile("polygonpattern_text.txt");

	std::fstream fs;
	fs.open("polygonpattern_text.txt", std::fstream::in | std::fstream::binary);
	//read all contents of file into string buf
	std::string buf((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
	// m_combo_polygon_pattern_alignment.GetCurSel();
	return buf;
}

std::string CFormViewPolygonPatternSymbolizer::GetValueAttribute(const tinyxml2::XMLAttribute* att)
{
	if (att != NULL)
	{
		return att->Value();
	}
	return std::string();
}

BEGIN_MESSAGE_MAP(CFormViewPolygonPatternSymbolizer, CBCGPFormView)
	ON_BN_CLICKED(IDC_POLYGON_PATTERN_APPLY_BUTTON, &CFormViewPolygonPatternSymbolizer::OnBnClickedPolygonPatternApplyButton)
	ON_WM_MOUSEACTIVATE()
	ON_EN_KILLFOCUS(IDC_EDIT_POLYGON_PATTERN_FILE, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_PATTERN_ALIGNMENT, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_EN_KILLFOCUS(IDC_EDIT_POLYGON_PATTERN_GAMMA, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_EN_KILLFOCUS(IDC_EDIT_SIMPLIFY_POLYGON_PATTERN, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_EN_KILLFOCUS(IDC_EDIT_SMOOTH_POLYGON_PATTERN, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_BN_KILLFOCUS(IDC_CHECK_POLYGON_PATTERN_DEFAULT, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_BN_KILLFOCUS(IDC_CHECK_POLYGON_PATTERN_CLIP, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_PATTERN_SIMPLIFY_ALGORITHM, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_PATTERN_GEOMETRY_TRANSFORM, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_PATTERN_TRANSFORM, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_PATTERN_COMPOP, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_EN_KILLFOCUS(IDC_EDIT_POLYGON_PATTERN_OPACITY, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_CBN_KILLFOCUS(IDC_BUTTON_POLYGON_PATTERN_FILE, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_BN_CLICKED(IDC_BUTTON_POLYGON_PATTERN_FILE, &CFormViewPolygonPatternSymbolizer::OnBnClickedButtonPolygonPatternFile)
	ON_BN_CLICKED(IDC_CHECK_POLYGON_PATTERN_DEFAULT, &CFormViewPolygonPatternSymbolizer::OnBnClickedCheckPolygonPatternDefault)
	ON_EN_SETFOCUS(IDC_EDIT_TEXT_POLYGON_PATTERN, &CFormViewPolygonPatternSymbolizer::OnFocusScriptPolygonPattern)
	ON_CBN_SELCHANGE(IDC_COMBO_POLYGON_PATTERN_ALIGNMENT, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_CBN_SELCHANGE(IDC_COMBO_POLYGON_PATTERN_SIMPLIFY_ALGORITHM, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_BN_CLICKED(IDC_CHECK_POLYGON_PATTERN_CLIP, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_CBN_SELCHANGE(IDC_COMBO_POLYGON_PATTERN_COMPOP, &CFormViewPolygonPatternSymbolizer::OnKillFocus)
	ON_STN_CLICKED(IDC_STATIC_POLYGON_PATTEN_FOLDER, &CFormViewPolygonPatternSymbolizer::OnStnClickedStaticPolygonPattenFolder)
END_MESSAGE_MAP()


// CFormViewPolygonPatternSymbolizer diagnostics

#ifdef _DEBUG
void CFormViewPolygonPatternSymbolizer::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewPolygonPatternSymbolizer::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormViewPolygonPatternSymbolizer message handlers


int CFormViewPolygonPatternSymbolizer::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
void CFormViewPolygonPatternSymbolizer::SettingsXml(std::string xml_string)
{
	/// <summary>
	/// The function is used to set values for controls from the string xml.
	/// </summary>
	/// <param name="xml_string">The xml string</param>
	if (xml_string.compare("") == 0)
	{

	}
	else
	{
		SetDefault();
		tinyxml2::XMLDocument doc;
		doc.Parse(xml_string.c_str());
		tinyxml2::XMLElement* symbolizer = doc.FirstChildElement("PolygonPatternSymbolizer");
		std::string default_str, file, opacity, alignment, gamma, transform, geometry_transform, clip, simplify,
			smooth, compop, simplify_algorithm;

		const tinyxml2::XMLAttribute* att_default = symbolizer->FindAttribute("default");
		default_str = GetValueAttribute(att_default);
		if (default_str.compare("") != 0)
		{
			m_button_polygon_pattern_default.SetCheck(true);
		}

		const tinyxml2::XMLAttribute* att_file = symbolizer->FindAttribute("file");
		file = GetValueAttribute(att_file);
		if (file.compare("") != 0)
		{
			m_edit_polygon_pattern_file.SetWindowTextW(CString(file.c_str()));
		}

		const tinyxml2::XMLAttribute* att_opacity = symbolizer->FindAttribute("opacity");

		opacity = GetValueAttribute(att_opacity);
		if (opacity.compare("") != 0)
		{
			m_edit_polygon_pattern_opacity.SetWindowTextW(CString(opacity.c_str()));

		}

		const tinyxml2::XMLAttribute* att_alignment = symbolizer->FindAttribute("alignment");
		alignment = GetValueAttribute(att_alignment);
		if (alignment.compare("") != 0)
		{
			m_combo_polygon_pattern_alignment.SetCurSel(
				m_combo_polygon_pattern_alignment.FindStringExact(
					0, CString(alignment.c_str())));
		}

		const tinyxml2::XMLAttribute* att_gamma = symbolizer->FindAttribute("gamma");
		gamma = GetValueAttribute(att_gamma);
		if (gamma.compare("") != 0)
		{
			m_edit_polygon_pattern_gamma.SetWindowTextW(CString(gamma.c_str()));
		}

		const tinyxml2::XMLAttribute* att_transform = symbolizer->FindAttribute("transform");
		transform = GetValueAttribute(att_transform);

		if (transform.compare("") != 0)
		{
			m_combo_polygon_pattern_transform.SetWindowTextW(
					CString(transform.c_str()));
		}


		// geometry_transform
		const tinyxml2::XMLAttribute* att_geometry_transform = symbolizer->FindAttribute("geometry-transform");

		geometry_transform = GetValueAttribute(att_geometry_transform);
		if (geometry_transform.compare("") != 0)
		{
			m_combo_polygon_pattern_geometry_transform.SetWindowTextW( 
				CString(geometry_transform.c_str()));
		}


		/// clip
		const tinyxml2::XMLAttribute* att_clip = symbolizer->FindAttribute("clip");
		clip = GetValueAttribute(att_clip);
		if (clip.compare("") != 0)
		{
			m_polygon_pattern_clip.SetCheck(true);
		}

		// simplify
		const tinyxml2::XMLAttribute* att_simplify = symbolizer->FindAttribute("simplify");
		simplify = GetValueAttribute(att_simplify);
		if (simplify.compare("") != 0)
		{
			m_edit_polygon_pattern_simplify.SetWindowTextW(CString(simplify.c_str()));
		}

		// smooth
		const tinyxml2::XMLAttribute* att_smooth = symbolizer->FindAttribute("smooth");
		smooth = GetValueAttribute(att_smooth);
		if (smooth.compare("") != 0)
		{
			m_edit_polygon_pattern_smooth.SetWindowTextW(CString(smooth.c_str()));
		}


		// compop
		const tinyxml2::XMLAttribute* att_compop = symbolizer->FindAttribute("comp-op");
		compop = GetValueAttribute(att_compop);
		if (compop.compare("") != 0)
		{
			m_combo_polygon_pattern_compop.SetCurSel(m_combo_polygon_pattern_compop.FindStringExact(
				0, CString(compop.c_str())));
		}

		// simplify_algorithm
		const tinyxml2::XMLAttribute* att_simplify_algorithm = symbolizer->FindAttribute("simplify-algorithm");
		simplify_algorithm = GetValueAttribute(att_simplify_algorithm);
		if (simplify_algorithm.compare("") != 0)
		{
			m_combo_polygon_pattern_simplify_algorithm.SetCurSel(
				m_combo_polygon_pattern_simplify_algorithm.FindStringExact(
					0, CString(simplify_algorithm.c_str())));
		}

	}
}
void CFormViewPolygonPatternSymbolizer::OnBnClickedPolygonPatternApplyButton()
{
	// TODO: Add your control notification handler code here
	std::string output_string = SettingsXml();
	// AfxMessageBox(CString(output_string.c_str()));
	
	m_script_polygon_pattern.SetWindowTextW(CString(output_string.c_str()));
}


void CFormViewPolygonPatternSymbolizer::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();
	AddPolygonPatternSimplifyAlgorithm();
	AddPolygonPatternCompOp();
	AddPolygonPatternGeometryTransform();
	AddPolygonPatternAlignment();
	AddPolygonPatternTransform();

	SetDefault();
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);
	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	m_ToolTip.SetParams(&params);
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_POLYGON_PATTERN_DEFAULT), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_POLYGON_PATTERN_FILE), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_POLYGON_PATTERN_ALIGNMENT), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_POLYGON_PATTERN_GAMMA), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_POLYGON_PATTERN_OPACITY), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_POLYGON_PATTERN_CLIP), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SIMPLIFY_POLYGON_PATTERN), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_POLYGON_PATTERN_SIMPLIFY_ALGORITHM), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SMOOTH_POLYGON_PATTERN), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_POLYGON_PATTERN_GEOMETRY_TRANSFORM), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_POLYGON_PATTERN_TRANSFORM), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_POLYGON_PATTERN_COMPOP), _T("Document"));



	CBCGPToolBarImages imagesFolderButton;
	imagesFolderButton.SetImageSize(CSize(24, 24));
	imagesFolderButton.Load(IDB_PNG_FOLDER);
	m_polygon_pattern_open_folder_static.ModifyStyle(0, SS_ICON);
	m_polygon_pattern_open_folder_static.ModifyStyle(0, SS_NOTIFY);
	m_polygon_pattern_open_folder_static.SetIcon(imagesFolderButton.ExtractIcon(0));
	// TODO: Add your specialized code here and/or call the base class
}


BOOL CFormViewPolygonPatternSymbolizer::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONDOWN:
		m_ToolTip.RelayEvent(pMsg);
		break;
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


void CFormViewPolygonPatternSymbolizer::OnKillFocus()
{
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	std::string text = SettingsXml();
	 SettingsXml(text);
	m_script_polygon_pattern.SetWindowTextW(CString(text.c_str()));
	if (m_button_polygon_pattern_default.GetCheck() == 1)
	{
		m_button_polygon_pattern_default.SetCheck(0);
	}
	UpdateData();
}


void CFormViewPolygonPatternSymbolizer::OnBnClickedButtonPolygonPatternFile()
{
	// TODO: Add your control notification handler code here
	LPCTSTR typeFile = _T("svg(*.svg)|*.jpg|"
		"png (*.png)| *.tiff|""webp(*.webp)|*.webp|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("png"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		typeFile, AfxGetMainWnd());
	if (IDOK == dlgFile.DoModal())
	{
		CStdioFile file(dlgFile.GetPathName(), CFile::modeRead | CFile::typeText);
		bool successful{ false };
		std::string path = CT2A(dlgFile.GetPathName());
		m_edit_polygon_pattern_file.SetWindowTextW(dlgFile.GetPathName());
	}
}


void CFormViewPolygonPatternSymbolizer::OnBnClickedCheckPolygonPatternDefault()
{
	// TODO: Add your control notification handler code here
	if (m_button_polygon_pattern_default.GetCheck() == 1)
	{
		SetDefault();
		
	}
	OnFocusScriptPolygonPattern();
}


void CFormViewPolygonPatternSymbolizer::OnFocusScriptPolygonPattern()
{
	// TODO: Add your control notification handler code here
	std::string text = SettingsXml();
	m_script_polygon_pattern.SetWindowTextW(CString(text.c_str()));
}

std::vector<std::string> CFormViewPolygonPatternSymbolizer::TokenizeString(std::string in_str, const char delimeter)
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




void CFormViewPolygonPatternSymbolizer::OnCbnSelchangeComboPolygonPatternAlignment()
{
	// TODO: Add your control notification handler code here
}


void CFormViewPolygonPatternSymbolizer::OnCbnSelchangeComboPolygonPatternSimplifyAlgorithm()
{
	// TODO: Add your control notification handler code here
}


void CFormViewPolygonPatternSymbolizer::OnBnClickedCheckPolygonPatternClip()
{
	// TODO: Add your control notification handler code here
}


void CFormViewPolygonPatternSymbolizer::OnCbnSelchangeComboPolygonPatternCompop()
{
	// TODO: Add your control notification handler code here
}


void CFormViewPolygonPatternSymbolizer::OnStnClickedStaticPolygonPattenFolder()
{
	// TODO: Add your control notification handler code here
	LPCTSTR typeFile = _T("svg(*.svg)|*.jpg|"
		"png (*.png)| *.tiff|""webp(*.webp)|*.webp|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("png"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		typeFile, AfxGetMainWnd());
	if (IDOK == dlgFile.DoModal())
	{
		CStdioFile file(dlgFile.GetPathName(), CFile::modeRead | CFile::typeText);
		bool successful{ false };
		std::string path = CT2A(dlgFile.GetPathName());
		m_edit_polygon_pattern_file.SetWindowTextW(dlgFile.GetPathName());
	}
}
