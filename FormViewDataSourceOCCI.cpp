// FormViewDataSourceOCCI.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "FormViewDataSourceOCCI.h"


// CFormViewDataSourceOCCI

IMPLEMENT_DYNCREATE(CFormViewDataSourceOCCI, CBCGPFormView)

CFormViewDataSourceOCCI::CFormViewDataSourceOCCI()
	: CBCGPFormView(IDD_FORMVIEW_DATASOURCE_OCCI)
{

}

CFormViewDataSourceOCCI::~CFormViewDataSourceOCCI()
{
}

void CFormViewDataSourceOCCI::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_OCCI_ENCODING, m_occi_encoding_edit);
    DDX_Control(pDX, IDC_EDIT_OCCI_SCRIPT, m_occi_script_edit);
    DDX_Control(pDX, IDC_STATIC_OCCI_RESET, m_occi_reset_button);
}

BEGIN_MESSAGE_MAP(CFormViewDataSourceOCCI, CBCGPFormView)
    ON_WM_MOUSEACTIVATE()
    ON_EN_SETFOCUS(IDC_EDIT_OCCI_SCRIPT, &CFormViewDataSourceOCCI::OnSetFocusScriptOCCI)
    ON_EN_KILLFOCUS(IDC_EDIT_OCCI_ENCODING, &CFormViewDataSourceOCCI::OnKillFocusOCCI)
    ON_STN_CLICKED(IDC_STATIC_OCCI_RESET, &CFormViewDataSourceOCCI::OnStnClickedStaticOcciReset)
END_MESSAGE_MAP()


// CFormViewDataSourceOCCI diagnostics

#ifdef _DEBUG
void CFormViewDataSourceOCCI::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewDataSourceOCCI::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}

BOOL CFormViewDataSourceOCCI::CreateView(CWnd* pParent, CCreateContext* pContext)
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
#endif
#endif //_DEBUG


// CFormViewDataSourceOCCI message handlers


void CFormViewDataSourceOCCI::OnInitialUpdate()
{
    CBCGPFormView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class
    m_Tooltip.Create(this);
    m_Tooltip.Activate(TRUE);
    CBCGPToolTipParams params;
    params.m_bVislManagerTheme = TRUE;
    m_Tooltip.SetParams(&params);

    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_OCCI_ENCODING), _T("Document"));
    SetDefault(); 
    CBCGPToolBarImages imageResetButton;
    imageResetButton.SetImageSize(CSize(40, 40));
    imageResetButton.Load(IDB_PNG_RESET_ICON);
    m_occi_reset_button.ModifyStyle(0, SS_ICON);
    m_occi_reset_button.ModifyStyle(0, SS_NOTIFY);
    m_occi_reset_button.SetIcon(imageResetButton.ExtractIcon(0));
    m_occi_reset_button.SetWindowTextW(_T("Default"));
}

void CFormViewDataSourceOCCI::SetDefault()
{
    m_occi_encoding_edit.SetWindowTextW(CString(default_occi_encoding.c_str()));
}
std::string CFormViewDataSourceOCCI::SettingsXml()
{
    tinyxml2::XMLDocument doc;

    CString encoding_cstr;

    m_occi_encoding_edit.GetWindowTextW(encoding_cstr);
    tinyxml2::XMLElement* ds = doc.NewElement("Datasource");
    doc.InsertFirstChild(ds);

    tinyxml2::XMLElement* type = doc.NewElement("Parameter");
    type->SetAttribute("name", "type");
    tinyxml2::XMLText* text_param = doc.NewText("occi");
    text_param->SetCData(true);
    type->InsertEndChild(text_param);
    ds->InsertEndChild(type);
    if (std::string(CT2A(encoding_cstr)).compare(default_occi_encoding) != 0)
    {
        tinyxml2::XMLElement* encoding = doc.NewElement("Parameter");
        encoding->SetAttribute("name", "encoding");
        tinyxml2::XMLText* text_param = doc.NewText(std::string(CT2A(encoding_cstr)).c_str());
        text_param->SetCData(true);
        encoding->InsertEndChild(text_param);
        ds->InsertEndChild(encoding);
    }
    std::stringstream ss;
    tinyxml2::XMLPrinter printer;
    doc.SaveFile("csv_occi.txt");
    std::fstream fs;
    fs.open("csv_occi.txt", std::fstream::in | std::fstream::binary);

    std::string buf((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    return std::string(buf);
}
void CFormViewDataSourceOCCI::SettingsXml(std::string xml_string)
{
    if (xml_string.compare("") == 0)
    {

    }
    else
    {
        tinyxml2::XMLDocument doc;

        doc.Parse(xml_string.c_str());
        auto data_source = doc.FirstChildElement("Datasource");

        std::string file_str, base_str, encoding_str;
        for (const tinyxml2::XMLElement* element = data_source->FirstChildElement("Parameter");
            element != nullptr; element = element->NextSiblingElement("Parameter"))
        {
            // The name of parameter
            std::string name = element->Attribute("name");
            std::string text = element->GetText();
            if (name.compare("encoding") == 0)
            {
                m_occi_encoding_edit.SetWindowTextW(CString(text.c_str()));
            }
        }
    }
}
int CFormViewDataSourceOCCI::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
void CFormViewDataSourceOCCI::OnSetFocusScriptOCCI()
{
    // TODO: Add your control notification handler code here
    std::string text = SettingsXml();
    SettingsXml(text);
    m_occi_script_edit.SetWindowTextW(CString(text.c_str()));
}


void CFormViewDataSourceOCCI::OnKillFocusOCCI()
{
    // TODO: Add your control notification handler code here
    OnSetFocusScriptOCCI();
}


BOOL CFormViewDataSourceOCCI::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    switch (pMsg->message)
    {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_LBUTTONDOWN:
        m_Tooltip.RelayEvent(pMsg);
        break;
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_MOUSEMOVE:
        m_Tooltip.RelayEvent(pMsg);
        break;
    }
    return CBCGPFormView::PreTranslateMessage(pMsg);
}


void CFormViewDataSourceOCCI::OnStnClickedStaticOcciReset()
{
    // TODO: Add your control notification handler code here
    SetDefault();
    OnSetFocusScriptOCCI();
}
