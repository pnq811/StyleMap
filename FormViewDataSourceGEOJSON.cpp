// CFormViewDataSourceGEOJSON.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "FormViewDataSourceGEOJSON.h"


// CFormViewDataSourceGEOJSON

IMPLEMENT_DYNCREATE(CFormViewDataSourceGEOJSON, CBCGPFormView)

CFormViewDataSourceGEOJSON::CFormViewDataSourceGEOJSON()
	: CBCGPFormView(IDD_FORMVIEW_DATASOURCE_GEOJSON)
{

}

CFormViewDataSourceGEOJSON::~CFormViewDataSourceGEOJSON()
{
}

void CFormViewDataSourceGEOJSON::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_GEOJSON_FILE, m_geojson_file_edit);
    DDX_Control(pDX, IDC_STATIC_GEOJSON_FILE_OPEN, m_geojson_file_open_static);
    DDX_Control(pDX, IDC_EDIT_GEOJSON_BASE, m_geojson_base_edit);
    DDX_Control(pDX, IDC_STATIC_GEOJSON_BASE_OPEN, m_geojson_base_open_static);
    DDX_Control(pDX, IDC_EDIT_GEOJSON_ENCODING, m_geojson_encoding_edit);
    DDX_Control(pDX, IDC_EDIT_GEOJSON_INLINE, m_geojson_inline_edit);
    DDX_Control(pDX, IDC_EDIT_GEOJSON_SCRIPT, m_geojson_script_edit);
    DDX_Control(pDX, IDC_STATIC_GEOJSON_RESET, m_geojson_reset_static);
}

BEGIN_MESSAGE_MAP(CFormViewDataSourceGEOJSON, CBCGPFormView)
    ON_WM_MOUSEACTIVATE()
    ON_STN_CLICKED(IDC_STATIC_GEOJSON_FILE_OPEN, &CFormViewDataSourceGEOJSON::OnStnClickedStaticGeojsonFileOpen)
    ON_STN_CLICKED(IDC_STATIC_GEOJSON_BASE_OPEN, &CFormViewDataSourceGEOJSON::OnStnClickedStaticGeojsonBaseOpen)
    ON_EN_SETFOCUS(IDC_EDIT_GEOJSON_SCRIPT, &CFormViewDataSourceGEOJSON::OnSetFocusScriptGEOJSON)
    ON_EN_KILLFOCUS(IDC_EDIT_GEOJSON_FILE, &CFormViewDataSourceGEOJSON::OnKillFocusGEOJSON)
    ON_EN_KILLFOCUS(IDC_EDIT_GEOJSON_BASE, &CFormViewDataSourceGEOJSON::OnKillFocusGEOJSON)
    ON_EN_KILLFOCUS(IDC_EDIT_GEOJSON_INLINE, &CFormViewDataSourceGEOJSON::OnKillFocusGEOJSON)
    ON_EN_KILLFOCUS(IDC_EDIT_GEOJSON_ENCODING, &CFormViewDataSourceGEOJSON::OnKillFocusGEOJSON)
    ON_STN_CLICKED(IDC_STATIC_GEOJSON_RESET, &CFormViewDataSourceGEOJSON::OnStnClickedStaticGeojsonReset)
END_MESSAGE_MAP()


// CFormViewDataSourceGEOJSON diagnostics
BOOL CFormViewDataSourceGEOJSON::CreateView(CWnd* pParent, CCreateContext* pContext)
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
#ifdef _DEBUG
void CFormViewDataSourceGEOJSON::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewDataSourceGEOJSON::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormViewDataSourceGEOJSON message handlers


void CFormViewDataSourceGEOJSON::OnInitialUpdate()
{
    CBCGPFormView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class
    CBCGPToolBarImages imagesFolderButton;
    imagesFolderButton.SetImageSize(CSize(24, 24));
    imagesFolderButton.Load(IDB_PNG_FOLDER);

    m_geojson_file_open_static.ModifyStyle(0, SS_ICON);
    m_geojson_file_open_static.ModifyStyle(0, SS_NOTIFY);
    m_geojson_file_open_static.SetIcon(imagesFolderButton.ExtractIcon(0));
    // TODO: Add your specialized code here and/or call the base class
    m_geojson_base_open_static.ModifyStyle(0, SS_ICON);
    m_geojson_base_open_static.ModifyStyle(0, SS_NOTIFY);
    m_geojson_base_open_static.SetIcon(imagesFolderButton.ExtractIcon(0));

    SetDefault();
    CBCGPToolBarImages imageResetButton;
    imageResetButton.SetImageSize(CSize(40, 40));
    imageResetButton.Load(IDB_PNG_RESET_ICON);
    m_geojson_reset_static.ModifyStyle(0, SS_ICON);
    m_geojson_reset_static.ModifyStyle(0, SS_NOTIFY);
    m_geojson_reset_static.SetIcon(imageResetButton.ExtractIcon(0));

    m_Tooltip.Create(this);
    m_Tooltip.Activate(TRUE);
    CBCGPToolTipParams params;
    params.m_bVislManagerTheme = TRUE;

    m_Tooltip.SetParams(&params);
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GEOJSON_FILE), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GEOJSON_BASE), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GEOJSON_INLINE), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GEOJSON_ENCODING), _T("Document"));
}
void CFormViewDataSourceGEOJSON::AddParameterTag(CString text_value, std::string name,
    std::string de_value, tinyxml2::XMLElement*& ds, tinyxml2::XMLDocument& doc)
{
    if (std::string(CT2A(text_value)).compare(de_value) != 0)
    {
        tinyxml2::XMLElement* tag_param = doc.NewElement("Parameter");
        tag_param->SetAttribute("name", name.c_str());
        tinyxml2::XMLText* text_param = doc.NewText(std::string(CT2A(text_value)).c_str());
        text_param->SetCData(true);
        tag_param->InsertEndChild(text_param);
        ds->InsertEndChild(tag_param);
    }
}
std::string CFormViewDataSourceGEOJSON::SettingsXml()
{
    tinyxml2::XMLDocument doc;

    CString file_cstr, base_cstr, encoding_cstr, inline_cstr;

    m_geojson_file_edit.GetWindowTextW(file_cstr);
    m_geojson_base_edit.GetWindowTextW(base_cstr);
    m_geojson_encoding_edit.GetWindowTextW(encoding_cstr);
    m_geojson_inline_edit.GetWindowTextW(inline_cstr);
    tinyxml2::XMLElement* ds_geojson = doc.NewElement("Datasource");
    doc.InsertFirstChild(ds_geojson);

    // type
    tinyxml2::XMLElement* type = doc.NewElement("Parameter");
    type->SetAttribute("name", "type");
    tinyxml2::XMLText* text_param = doc.NewText("geojson");
    text_param->SetCData(true);
    type->InsertEndChild(text_param);
    ds_geojson->InsertEndChild(type);
    //file
    AddParameterTag(file_cstr, "file", default_geojson_file, ds_geojson, doc);
    //base
    AddParameterTag(base_cstr, "base", default_geojson_base, ds_geojson, doc);
    //encoding
    AddParameterTag(encoding_cstr, "encoding", default_geojson_encoding, ds_geojson, doc);
    //inline
    AddParameterTag(inline_cstr, "inline", default_geojson_inline, ds_geojson, doc);
    std::stringstream ss;
    tinyxml2::XMLPrinter printer;
    doc.SaveFile("geojson_ds.txt");
    std::fstream fs;
    fs.open("geojson_ds.txt", std::fstream::in | std::fstream::binary);
    std::string buf((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    return std::string(buf);
}

void CFormViewDataSourceGEOJSON::SettingsXml(std::string xml_string)
{
    if (xml_string.compare("") == 0)
    {

    }
    else
    {
        tinyxml2::XMLDocument doc;

        doc.Parse(xml_string.c_str());
        auto data_source = doc.FirstChildElement("Datasource");

        std::string file_str, base_str, encoding_str, row_limit_str, escape_str,
            quote_str, separator_str, headers_str, file_size_max_str;
        for (const tinyxml2::XMLElement* element = data_source->FirstChildElement("Parameter");
            element != nullptr; element = element->NextSiblingElement("Parameter"))
        {
            // The name of parameter
            std::string name = element->Attribute("name");
            std::string text = element->GetText();
            if (name.compare("file")==0)
            {
                m_geojson_file_edit.SetWindowTextW(CString(text.c_str()));
            }
            if (name.compare("base") == 0)
            {
                m_geojson_base_edit.SetWindowTextW(CString(text.c_str()));
            }
            if (name.compare("encoding") == 0)
            {
                m_geojson_encoding_edit.SetWindowTextW(CString(text.c_str()));
            }
            if (name.compare("inline") == 0)
            {
                m_geojson_inline_edit.SetWindowTextW(CString(text.c_str()));
            }
        }
    }
}

void CFormViewDataSourceGEOJSON::SetDefault()
{
    m_geojson_file_edit.SetWindowTextW(CString(default_geojson_file.c_str()));
    m_geojson_base_edit.SetWindowTextW(CString(default_geojson_base.c_str()));
    m_geojson_encoding_edit.SetWindowTextW(CString(default_geojson_encoding.c_str()));
    m_geojson_inline_edit.SetWindowTextW(CString(default_geojson_inline.c_str()));
}
void CFormViewDataSourceGEOJSON::OnStnClickedStaticGeojsonFileOpen()
{
    // TODO: Add your control notification handler code here
    LPCTSTR typeFile = _T("Text (*.json)| *.json|All Files (*.*)|*.*||");
    CFileDialog dlgFile(TRUE, _T("shp"), NULL, OFN_FILEMUSTEXIST,
        typeFile, AfxGetMainWnd());
    if (IDOK == dlgFile.DoModal())
    {
        std::string path = CT2A(dlgFile.GetPathName());
        m_geojson_file_edit.SetWindowTextW(dlgFile.GetPathName());
        OnSetFocusScriptGEOJSON();
    }
}


void CFormViewDataSourceGEOJSON::OnStnClickedStaticGeojsonBaseOpen()
{
    // TODO: Add your control notification handler code here
    LPCTSTR typeFile = _T("Text (*.json)| *.json|All Files (*.*)|*.*||");
    CFileDialog dlgFile(TRUE, _T("shp"), NULL, OFN_FILEMUSTEXIST,
        typeFile, AfxGetMainWnd());
    if (IDOK == dlgFile.DoModal())
    {
        std::string path = CT2A(dlgFile.GetPathName());
        m_geojson_base_edit.SetWindowTextW(dlgFile.GetPathName());
        OnSetFocusScriptGEOJSON();
    }
}


void CFormViewDataSourceGEOJSON::OnSetFocusScriptGEOJSON()
{
    // TODO: Add your control notification handler code here
    std::string xml_str = SettingsXml();
    SettingsXml(xml_str);
    m_geojson_script_edit.SetWindowTextW(CString(xml_str.c_str()));
}


void CFormViewDataSourceGEOJSON::OnKillFocusGEOJSON()
{
    // TODO: Add your control notification handler code here
    OnSetFocusScriptGEOJSON();
}
int CFormViewDataSourceGEOJSON::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CFormViewDataSourceGEOJSON::OnStnClickedStaticGeojsonReset()
{
    // TODO: Add your control notification handler code here
    SetDefault();
    OnSetFocusScriptGEOJSON();
}


BOOL CFormViewDataSourceGEOJSON::PreTranslateMessage(MSG* pMsg)
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
