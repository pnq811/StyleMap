// FormViewPolygonSymbolizer.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "FormViewPolygonSymbolizer.h"
#include <string>
#include "tinyxml2.h"
#include <sstream>
#include <fstream>
// CFormViewPolygonSymbolizer

IMPLEMENT_DYNCREATE(CFormViewPolygonSymbolizer, CBCGPFormView)

CFormViewPolygonSymbolizer::CFormViewPolygonSymbolizer()
	: CBCGPFormView(IDD_CFormViewPolygonSymbolizer)
{

}

CFormViewPolygonSymbolizer::~CFormViewPolygonSymbolizer()
{
}

BOOL CFormViewPolygonSymbolizer::CreateView(CWnd* pParent, CCreateContext* pContext)
{
    CRect rect(0, 0, 300, 300);

    if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
        rect, pParent, AFX_IDW_PANE_FIRST, pContext))
    {
        TRACE0("Warning: couldn't create CFormViewPolygonSymbolizer!\n");
        return FALSE;
    }

	return TRUE;
}

void CFormViewPolygonSymbolizer::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_EDIT_POLYGON_FILL_OPACITY, m_edit_polygon_fill_opacity);
    DDX_Control(pDX, IDC_EDIT_POLYGON_GAMMA, m_edit_gamma);
    DDX_Control(pDX, IDC_EDIT_POLYGON_SIMPLIFY, m_edit_polygon_simplify);
    DDX_Control(pDX, IDC_EDIT_POLYGON_SMOOTH, m_edit_polygon_smooth);
    DDX_Control(pDX, IDC_COMBO_POLYGON_GAMMA_METHOD, m_combo_polygon_gamma_method);
    DDX_Control(pDX, IDC_CHECK_POLYGON_CLIP, m_check_polygon_clip);
    DDX_Control(pDX, IDC_COMBO_POLYGON_SYMPLIFY_ALGORITHM, m_combo_polygon_simplify_algorithm);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON_POLYGON_FILL, m_colorbutton_polygon_fill);
    DDX_Control(pDX, IDC_COMBO_POLYGON_GEOMETRY_TRANSFORM, m_combo_polygon_geometry_transform);
    DDX_Control(pDX, IDC_COMBO_POLYGON_COMPOP, m_combo_polygon_compop);
    DDX_Control(pDX, IDC_CHECK_POLYGON_DEFAULT, m_button_polygon_default);



    DDX_Control(pDX, IDC_SCRIPT_POLYGON_TEXT, m_script_polygon_text);
}

BEGIN_MESSAGE_MAP(CFormViewPolygonSymbolizer, CBCGPFormView)
    ON_CBN_SELCHANGE(IDC_COMBO_POLYGON_COMPOP, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_BN_CLICKED(IDC_CHECK_POLYGON_DEFAULT, &CFormViewPolygonSymbolizer::OnBnClickedCheckPolygonDefault)
    ON_BN_CLICKED(IDC_BUTTON_POLYGON_APPLY, &CFormViewPolygonSymbolizer::OnBnClickedButtonPolygonApply)
    ON_WM_MOUSEACTIVATE()
    ON_EN_KILLFOCUS(IDC_EDIT_POLYGON_GAMMA, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_EN_KILLFOCUS(IDC_EDIT_POLYGON_SIMPLIFY, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_EN_KILLFOCUS(IDC_EDIT_POLYGON_SMOOTH, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_GAMMA_METHOD, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_BN_KILLFOCUS(IDC_CHECK_POLYGON_CLIP, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_SYMPLIFY_ALGORITHM, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_BN_KILLFOCUS(IDC_MFCCOLORBUTTON_POLYGON_FILL, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_GEOMETRY_TRANSFORM, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_COMPOP, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_BN_KILLFOCUS(IDC_CHECK_POLYGON_DEFAULT, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_EN_KILLFOCUS(IDC_EDIT_POLYGON_FILL_OPACITY, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_CBN_KILLFOCUS(IDC_COMBO_POLYGON_SYMPLIFY_ALGORITHM, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_CBN_SELCHANGE(IDC_COMBO_POLYGON_SYMPLIFY_ALGORITHM, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_EN_SETFOCUS(IDC_SCRIPT_POLYGON_TEXT, &CFormViewPolygonSymbolizer::OnFocusScriptPolygon)
    ON_STN_CLICKED(IDC_STATIC_POLYGON_SIMPLIFY_ALGORITHM, &CFormViewPolygonSymbolizer::OnStnClickedStaticPolygonSimplifyAlgorithm)
    ON_BN_CLICKED(IDC_MFCCOLORBUTTON_POLYGON_FILL, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_EN_CHANGE(IDC_EDIT_POLYGON_FILL_OPACITY, &CFormViewPolygonSymbolizer::OnEnChangeKill)
    ON_CBN_SELCHANGE(IDC_COMBO_POLYGON_GAMMA_METHOD, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
    ON_BN_CLICKED(IDC_CHECK_POLYGON_CLIP, &CFormViewPolygonSymbolizer::OnBnKillfocusPolygon)
END_MESSAGE_MAP()


// CFormViewPolygonSymbolizer diagnostics

#ifdef _DEBUG
void CFormViewPolygonSymbolizer::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewPolygonSymbolizer::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormViewPolygonSymbolizer message handlers

int CFormViewPolygonSymbolizer::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CFormViewPolygonSymbolizer::OnCbnSelchangeComboPolygonCompop()
{
    // TODO: Add your control notification handler code here
    std::string text_script = SettingsXML();
    SettingsXML(text_script);
    m_script_polygon_text.SetWindowTextW(CA2W(text_script.c_str()));
    if (m_button_polygon_default.GetCheck() == 1)
    {
        m_button_polygon_default.SetCheck(0);
    }
}

int CFormViewPolygonSymbolizer::CheckValidNumberFromString(std::string strNum)
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


void CFormViewPolygonSymbolizer::OnInitialUpdate()
{
    CBCGPFormView::OnInitialUpdate();
    AddPolygonSimplifyAlgorithm();
    AddPolygonGeometryTransform();
    AddPolygonCompop();
    AddPolygonGammaMethod();
    SetDefault();


    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);
    CBCGPToolTipParams params;
    params.m_bVislManagerTheme = TRUE;

    m_ToolTip.SetParams(&params);

    m_ToolTip.AddTool(GetDlgItem(IDC_MFCCOLORBUTTON_POLYGON_FILL), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_POLYGON_DEFAULT), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_POLYGON_FILL_OPACITY), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_POLYGON_GAMMA), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_POLYGON_GAMMA_METHOD), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_POLYGON_CLIP), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_POLYGON_SIMPLIFY), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_POLYGON_SYMPLIFY_ALGORITHM), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_POLYGON_GEOMETRY_TRANSFORM), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_POLYGON_SMOOTH), _T("Document"));
    m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_POLYGON_COMPOP), _T("Document"));
    // TODO: Add your specialized code here and/or call the base class
}

void CFormViewPolygonSymbolizer::SetDefault()
{
    m_combo_polygon_simplify_algorithm.SetCurSel(
        m_combo_polygon_simplify_algorithm.FindStringExact(
         0, CString(default_polygon_simplify_algorithm.c_str())
        )
    );
    m_combo_polygon_gamma_method.SetCurSel(
        m_combo_polygon_gamma_method.FindStringExact(
            0, CString(default_polygon_gamma_method.c_str())));
    m_combo_polygon_compop.SetCurSel(
        m_combo_polygon_compop.FindStringExact(
            0, CString(default_polygon_compop.c_str())));
    m_combo_polygon_geometry_transform.SetCurSel(
        m_combo_polygon_geometry_transform.FindStringExact(
            0, CString(default_polygon_geometry_transform.c_str())));

    std::string default_polygon_simplify_str =
        std::to_string(default_polygon_simplify);
    m_edit_polygon_simplify.SetWindowTextW(CString(default_polygon_simplify_str.c_str()));
    std::string default_polygon_gamma_str =
        std::to_string(default_polygon_gamma);
    m_edit_gamma.SetWindowTextW(CString(default_polygon_gamma_str.c_str()));
    std::string default_polygon_smooth_str =
        std::to_string(default_polygon_smooth);
    m_edit_polygon_smooth.SetWindowTextW(CString(default_polygon_smooth_str.c_str()));

    
    std::string default_polygon_fill_opacity_str =
        std::to_string(default_polygon_fill_opacity);
    m_edit_polygon_fill_opacity.SetWindowTextW(CString(default_polygon_fill_opacity_str.c_str()));

    m_colorbutton_polygon_fill.SetColor(default_polygon_fill);

    
    m_check_polygon_clip.SetCheck(default_polygon_clip);

}

void CFormViewPolygonSymbolizer::AddPolygonSimplifyAlgorithm()
{
    for (int i = 0; i < 4; i++)
    {
        m_combo_polygon_simplify_algorithm.AddString(
            CString(polygon_simplify_algorithm[i].c_str())
        );
    }
}

void CFormViewPolygonSymbolizer::AddPolygonCompop()
{
    for (int i = 0; i < 37; i++)
    {
        m_combo_polygon_compop.AddString(
            CString(polygon_compop_type[i].c_str())
        );
    }
}

void CFormViewPolygonSymbolizer::AddPolygonGeometryTransform()
{
    m_combo_polygon_geometry_transform.AddString(_T("none"));
    std::map<std::string, int>::iterator it;
    for (it = polygon_geometry_transform_map.begin();
        it!= polygon_geometry_transform_map.end();it++)
    {
        m_combo_polygon_geometry_transform.AddString(
            CString(it->first.c_str())
        );
    }
}

void CFormViewPolygonSymbolizer::AddPolygonGammaMethod()
{
    for (int i = 0; i < 5; i++)
    {
        m_combo_polygon_gamma_method.AddString(
            CString(polygon_gamma_method[i].c_str()));
    }
}


void CFormViewPolygonSymbolizer::DisableControl(bool check)
{
    m_colorbutton_polygon_fill.EnableWindow(FALSE);
    m_edit_polygon_fill_opacity.EnableWindow(FALSE);
    m_edit_gamma.EnableWindow(FALSE);
    m_edit_polygon_simplify.EnableWindow(FALSE);

}

void CFormViewPolygonSymbolizer::OnBnClickedCheckPolygonDefault()
{
    // TODO: Add your control notification handler code here
    
    SetDefault();
    OnFocusScriptPolygon();
}

std::string CFormViewPolygonSymbolizer::SettingsXML()
{
    /// <summary>
    /// The function is used to get string of tinyxml for attribute in polygon symbolizer formview
    /// from the controls.
    /// </summary>
    /// <returns>The string </returns>
    tinyxml2::XMLDocument doc;


    auto polygon_symbolizer = doc.NewElement("PolygonSymbolizer");
    

    // fill
    COLORREF Fill = m_colorbutton_polygon_fill.GetColor();
    if (Fill != default_polygon_fill)
    {
        CString color;
        color.Format(_T("#%02X%02X%02X"), GetRValue(Fill), GetGValue(Fill),
            GetBValue(Fill));
        polygon_symbolizer->SetAttribute("fill",
            std::string(CT2A(color)).c_str());
    }

    // comp - op
    CString compop;
    m_combo_polygon_compop.GetWindowTextW(compop);
    std::string compop_str = CT2A(compop);
    if (compop_str.compare(default_polygon_compop) != 0)
    {
        polygon_symbolizer->SetAttribute("comp-op", compop_str.c_str());
    }

    // gamma - method
    CString gamma_method;
    m_combo_polygon_gamma_method.GetWindowTextW(gamma_method);
    std::string gamma_method_str = CT2A(gamma_method);
    if (gamma_method_str.compare(default_polygon_gamma_method) != 0)
    {
        polygon_symbolizer->SetAttribute("gamma-method",
            gamma_method_str.c_str());
    }
    // geometry-transform
    CString geometry_transform, geometry_transform_params;
    m_combo_polygon_geometry_transform.GetWindowTextW(geometry_transform);
    std::string geometry_transform_str = CT2A(geometry_transform );
    if (geometry_transform_str.compare(default_polygon_geometry_transform) != 0)
    {
        geometry_transform_str = CT2A(geometry_transform);
        polygon_symbolizer->SetAttribute("geometry-transform",
            geometry_transform_str.c_str());
    }
    // simplify - algorithm
    CString simplify_algorithm;
    m_combo_polygon_simplify_algorithm.GetWindowTextW(simplify_algorithm);
    std::string simplify_algorithm_str = CT2A(simplify_algorithm);
    if (simplify_algorithm_str.compare(default_polygon_simplify_algorithm) != 0)
    {
        polygon_symbolizer->SetAttribute("simplify-algorithm",
            simplify_algorithm_str.c_str());
    }
   

    // gamma
    CString gamma_cstr;
    m_edit_gamma.GetWindowTextW(gamma_cstr);
    if (!CheckValidNumberFromString(std::string(CT2A(gamma_cstr))))
    {
        m_edit_gamma.SetWindowTextW(CString(std::to_string(default_polygon_gamma).c_str()));
        AfxMessageBox(_T("Gamma is not a valid number"));
    }
    else
    {
        float gamma = _tstof(gamma_cstr);
        if (gamma != default_polygon_gamma)
        {
            polygon_symbolizer->SetAttribute("gamma", std::to_string(gamma).c_str());
        }
    }
   
    // simplify
    CString simplify_cstr;
    m_edit_polygon_simplify.GetWindowTextW(simplify_cstr);
    if (!CheckValidNumberFromString(std::string(CT2A(simplify_cstr))))
    {
        m_edit_polygon_simplify.SetWindowTextW(CString(std::to_string(default_polygon_simplify).c_str()));

        AfxMessageBox(_T("Simplify is not a valid number"));
    }
    else {
        float simplify = _tstof(simplify_cstr);
        if (simplify != default_polygon_simplify)
        {
            polygon_symbolizer->SetAttribute("simplify", std::to_string(simplify).c_str());
        }
    }
    

    // smooth
    CString smooth_cstr;
    m_edit_polygon_smooth.GetWindowTextW(smooth_cstr);
    if (!CheckValidNumberFromString(std::string(CT2A(smooth_cstr))))
    {
        m_edit_polygon_smooth.SetWindowTextW(CString(
            std::to_string(default_polygon_smooth).c_str()
        ));
        AfxMessageBox(_T("Smooth is not a valid number"));
    }
    else {
        float smooth = _tstof(smooth_cstr);
        if (smooth != default_polygon_smooth)
        {
            polygon_symbolizer->SetAttribute("smooth", std::to_string(smooth).c_str());
        }
    }
    
    // fill-opacity
    CString fill_opacity_cstr;
    m_edit_polygon_fill_opacity.GetWindowTextW(fill_opacity_cstr);
    if (!CheckValidNumberFromString(std::string(CT2A(fill_opacity_cstr))))
    {
        m_edit_polygon_fill_opacity.SetWindowTextW(CString(
            std::to_string(default_polygon_fill_opacity).c_str()
        ));
        AfxMessageBox(_T("Fill Opacity is not a valid number"));
    }
    else
    {
        float fill_opacity = _tstof(fill_opacity_cstr);
        if (fill_opacity != default_polygon_fill_opacity)
        {
            polygon_symbolizer->SetAttribute("fill-opacity", std::to_string(fill_opacity).c_str());
        }
    }
   
    // clip
    if (m_check_polygon_clip.GetCheck() == true)
    {
        polygon_symbolizer->SetAttribute("clip", "true");
    }
    
    doc.LinkEndChild(polygon_symbolizer);
    
    doc.SaveFile("polygon_text.txt");
    
    std::fstream fs;
    fs.open("polygon_text.txt", std::fstream::in | std::fstream::binary);
    //read all contents of file into string buf
    std::string buf((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    

    return buf;
}

std::string CFormViewPolygonSymbolizer::GetValueAttribute(const tinyxml2::XMLAttribute* att)
{
    /// <summary>
    /// The function is used to get the value from tinyxml2::XMLAttribute variable if it is not NULL.
    /// </summary>
    /// <param name="att">The tinyxml2::XMLAttribute variable</param>
    /// <returns>the string value of attribute.</returns>
    if (att != NULL)
    {
        return att->Value();
    }
    return std::string();
}


void CFormViewPolygonSymbolizer::SettingsXML(std::string xml_string)
{
    /// <summary>
    /// The function is used to set values for controls from the string xml.
    /// </summary>
    /// <param name="xml_string">The string xml.</param>
    SetDefault();
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_string.c_str());

    tinyxml2::XMLElement* polygonsymbolizer = doc.FirstChildElement();

    std::string default_str, fill, clip, fill_opacity, gamma, gamma_method, simplify, simplify_algorithm,
        smooth, geometry_transform, comp_op;
    // default
    const tinyxml2::XMLAttribute* att_default = polygonsymbolizer->FindAttribute("default");
    default_str = GetValueAttribute(att_default);
    if (default_str.compare("") != 0)
    {
        m_button_polygon_default.SetCheck(true);
    }
    
    //fill
    const tinyxml2::XMLAttribute* att_fill = polygonsymbolizer->FindAttribute("fill");
    fill = GetValueAttribute(att_fill);

    if (fill.compare("") != 0)
    {
        COLORREF color = HexStringToColor(fill);
        m_colorbutton_polygon_fill.SetColor(color);
    }

    // clip
    const tinyxml2::XMLAttribute* att_clip = polygonsymbolizer->FindAttribute("clip");
    clip = GetValueAttribute(att_clip);
    if (clip.compare("") != 0)
    {
        m_check_polygon_clip.SetCheck(true);
    }
    
    // fill_opacity
    const tinyxml2::XMLAttribute* att_fill_opacity = polygonsymbolizer->FindAttribute("fill-opacity");
    fill_opacity = GetValueAttribute(att_fill_opacity);
    if (fill_opacity.compare("") != 0)
    {
        m_edit_polygon_fill_opacity.SetWindowTextW(CString(fill_opacity.c_str()));
    }
    
    // gamma
    const tinyxml2::XMLAttribute* att_gamma = polygonsymbolizer->FindAttribute("gamma");
    gamma = GetValueAttribute(att_gamma);
    if (gamma.compare("") != 0)
    {
        m_edit_gamma.SetWindowTextW(CString(gamma.c_str()));
    }
    // gamma_method
    const tinyxml2::XMLAttribute* att_gamma_method = polygonsymbolizer->FindAttribute("gamma-method");
    gamma_method = GetValueAttribute(att_gamma_method);
    if (gamma_method.compare("") != 0)
    {
        m_combo_polygon_gamma_method.SetCurSel(m_combo_polygon_gamma_method.FindStringExact(0, CString(
            gamma_method.c_str())));
    }

    // simplify
    const tinyxml2::XMLAttribute* att_simplify = polygonsymbolizer->FindAttribute("simplify");
    simplify = GetValueAttribute(att_simplify);
    if (simplify.compare("") != 0)
    {
        m_edit_polygon_simplify.SetWindowTextW(CString(simplify.c_str()));
    }
    // simplify_algorithm
    const tinyxml2::XMLAttribute* att_simplify_algorithm = polygonsymbolizer->FindAttribute("simplify-algorithm");
    simplify_algorithm = GetValueAttribute(att_simplify_algorithm);
    if (simplify_algorithm.compare("") != 0)
    {
        m_combo_polygon_simplify_algorithm.SetCurSel(m_combo_polygon_simplify_algorithm.FindStringExact(
            0, CString(simplify_algorithm.c_str())));
    }

    // smooth
    const tinyxml2::XMLAttribute* att_smooth = polygonsymbolizer->FindAttribute("smooth");
    smooth = GetValueAttribute(att_smooth);
    if (smooth.compare("") != 0)
    {
        m_edit_polygon_smooth.SetWindowTextW(CString(smooth.c_str()));
    }
    // geometry_transform
    const tinyxml2::XMLAttribute* att_geometry_transform = polygonsymbolizer->FindAttribute("geometry-transform");

    geometry_transform = GetValueAttribute(att_geometry_transform);
    if (geometry_transform.compare("") != 0)
    {
        m_combo_polygon_geometry_transform.SetWindowTextW(CString(geometry_transform.c_str()));
    }

    // compop
    const tinyxml2::XMLAttribute* att_compop = polygonsymbolizer->FindAttribute("comp-op");
    comp_op = GetValueAttribute(att_compop);
    if (comp_op.compare("") != 0)
    {
        m_combo_polygon_compop.SetCurSel(m_combo_polygon_compop.FindStringExact(
            0, CString(comp_op.c_str())));
    }
}

void CFormViewPolygonSymbolizer::OnBnClickedButtonPolygonApply()
{
    // TODO: Add your control notification handler code here
    /*std::string output_string = SettingsXML();
    AfxMessageBox(CString(output_string.c_str()));*/
}


void CFormViewPolygonSymbolizer::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
    // TODO: Add your specialized code here and/or call the base class
    // UpdateData(FALSE);
}


BOOL CFormViewPolygonSymbolizer::PreTranslateMessage(MSG* pMsg)
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

COLORREF CFormViewPolygonSymbolizer::HexStringToColor(std::string hex)
{
    LPCSTR color_cstr = hex.c_str();
    color_cstr++;
    COLORREF ref;
    
    ref = strtol(color_cstr, NULL, 16);
    return COLORREF(RGB(GetBValue(ref), GetGValue(ref), GetRValue(ref)));
}


void CFormViewPolygonSymbolizer::OnBnKillfocusPolygon()
{
    
    // TODO: Add your control notification handler code here
    
    std::string text_script = SettingsXML();
    SettingsXML(text_script);
    m_script_polygon_text.SetWindowTextW(CA2W(text_script.c_str()));
    if (m_button_polygon_default.GetCheck() == 1)
    {
        m_button_polygon_default.SetCheck(0);
    }
    UpdateData(FALSE);
}




void CFormViewPolygonSymbolizer::OnCbnKillfocusComboPolygonSymplifyAlgorithm()
{
    // TODO: Add your control notification handler code here
}


void CFormViewPolygonSymbolizer::OnCbnSelchangeComboPolygonSymplifyAlgorithm()
{
    // TODO: Add your control notification handler code here
}


void CFormViewPolygonSymbolizer::OnFocusScriptPolygon()
{
    // TODO: Add your control notification handler code here
    std::string text_script = SettingsXML();
    SettingsXML(text_script);
    m_script_polygon_text.SetWindowTextW(CA2W(text_script.c_str()));
}


void CFormViewPolygonSymbolizer::OnStnClickedStaticPolygonSimplifyAlgorithm()
{
    // TODO: Add your control notification handler code here
}

std::vector<std::string> CFormViewPolygonSymbolizer::TokenizeString(std::string in_str, const char delimeter)
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


void CFormViewPolygonSymbolizer::OnBnClickedMfccolorbuttonPolygonFill()
{
    // TODO: Add your control notification handler code here
}


void CFormViewPolygonSymbolizer::OnEnChangeKill()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CBCGPFormView::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    
    
}


void CFormViewPolygonSymbolizer::OnCbnSelchangeComboPolygonGammaMethod()
{
    // TODO: Add your control notification handler code here
}


void CFormViewPolygonSymbolizer::OnBnClickedCheckPolygonClip()
{
    // TODO: Add your control notification handler code here
}
