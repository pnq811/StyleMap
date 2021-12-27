// FormViewDataSourceGDAL.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "FormViewDataSourceGDAL.h"
#include "tinyxml2.h"
#include <sstream>
#include <fstream>
#include <string>
// CFormViewDataSourceGDAL

IMPLEMENT_DYNCREATE(CFormViewDataSourceGDAL, CBCGPFormView)

CFormViewDataSourceGDAL::CFormViewDataSourceGDAL()
	: CBCGPFormView(IDD_FORMVIEW_DATASOURCE_GDAL)
{

}

CFormViewDataSourceGDAL::~CFormViewDataSourceGDAL()
{
}

void CFormViewDataSourceGDAL::DoDataExchange(CDataExchange* pDX)
{
    CBCGPFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_GDAL_FILE, m_gdal_file_edit);
    DDX_Control(pDX, IDC_EDIT_GDAL_BASE, m_gdal_base_edit);
    DDX_Control(pDX, IDC_STATIC_GDAL_FILE_OPEN, m_gdal_file_open_static);
    DDX_Control(pDX, IDC_STATIC_GDAL_BASE_OPEN, m_gdal_base_open_static);
    DDX_Control(pDX, IDC_EDIT_GDAL_ENCODING, m_gdal_encoding_edit);
    DDX_Control(pDX, IDC_EDIT_GDAL_MAX_IMAGE_AREA, m_gdal_max_image_area_edit);
    DDX_Control(pDX, IDC_EDIT_GDAL_BAND, m_gdal_band_edit);
    DDX_Control(pDX, IDC_EDIT_GDAL_NODATA, m_gdal_nodata_edit);
    DDX_Control(pDX, IDC_EDIT_GDAL_NODATA_TOLERANCE, m_gdal_nodata_tolerance_edit);
    DDX_Control(pDX, IDC_CHECK_GDAL_SHARE, m_gdal_shared_button);
    DDX_Control(pDX, IDC_EDIT_GDAL_SCRIPT, m_gdal_script_edit);
    DDX_Control(pDX, IDC_STATIC_GDAL_RESET, m_gdal_reset_static);
}
void CFormViewDataSourceGDAL::SetDefault()
{
    m_gdal_file_edit.SetWindowTextW(CString(default_gdal_file.c_str()));
    m_gdal_base_edit.SetWindowTextW(CString(default_gdal_base.c_str()));
    m_gdal_encoding_edit.SetWindowTextW(CString(default_gdal_encoding.c_str()));
    m_gdal_max_image_area_edit.SetWindowTextW(CString(std::to_string(default_gdal_max_image_area).c_str()));
    m_gdal_band_edit.SetWindowTextW(CString(std::to_string(default_gdal_band).c_str()));
    m_gdal_nodata_edit.SetWindowTextW(CString(std::to_string(default_gdal_nodata).c_str()));
    m_gdal_nodata_tolerance_edit.SetWindowTextW(CString(std::to_string(default_gdal_nodata).c_str()));
}
std::string CFormViewDataSourceGDAL::SettingsXml()
{
    tinyxml2::XMLDocument doc;

    CString file_cstr, base_cstr, encoding_cstr, max_image_area_cstr, band_cstr, nodata_cstr, nodata_tolerance_cstr;


    m_gdal_file_edit.GetWindowTextW(file_cstr);
    m_gdal_base_edit.GetWindowTextW(base_cstr);
    m_gdal_encoding_edit.GetWindowTextW(encoding_cstr);
    m_gdal_max_image_area_edit.GetWindowTextW(max_image_area_cstr);
    m_gdal_band_edit.GetWindowTextW(band_cstr);
    m_gdal_nodata_edit.GetWindowTextW(nodata_cstr);
    m_gdal_nodata_tolerance_edit.GetWindowTextW(nodata_tolerance_cstr);


    tinyxml2::XMLElement* ds_gdal = doc.NewElement("Datasource");
    doc.InsertFirstChild(ds_gdal);

    // type
    tinyxml2::XMLElement* type = doc.NewElement("Parameter");
    type->SetAttribute("name", "type");
    tinyxml2::XMLText* text = doc.NewText("gdal");
    text->SetCData(true);
    type->InsertEndChild(text);
    ds_gdal->InsertEndChild(type);


    if (std::string(CT2A(file_cstr)).compare(default_gdal_file) != 0)
    {
        tinyxml2::XMLElement* file = doc.NewElement("Parameter");
        file->SetAttribute("name", "file");
        tinyxml2::XMLText* text = doc.NewText(std::string(CT2A(file_cstr)).c_str());
        text->SetCData(true);
        file->InsertEndChild(text);
        ds_gdal->InsertEndChild(file);
    }
    if (std::string(CT2A(base_cstr)).compare(default_gdal_base) != 0)
    {
        tinyxml2::XMLElement* base = doc.NewElement("Parameter");
        base->SetAttribute("name", "base");
        tinyxml2::XMLText* text = doc.NewText(std::string(CT2A(base_cstr)).c_str());
        text->SetCData(true);
        base->InsertEndChild(text);
        ds_gdal->InsertEndChild(base);
    }
    if (std::string(CT2A(encoding_cstr)).compare(default_gdal_encoding) != 0)
    {
        tinyxml2::XMLElement* encoding = doc.NewElement("Parameter");
        encoding->SetAttribute("name", "encoding");
        tinyxml2::XMLText* text = doc.NewText(std::string(CT2A(encoding_cstr)).c_str());
        text->SetCData(true);
        encoding->InsertEndChild(text);
        ds_gdal->InsertEndChild(encoding);
    }
    if (CheckValidNumberFromString(std::string(CT2A(max_image_area_cstr))))
    {
        int max_image_area_value = _tstoi(max_image_area_cstr);
        if (max_image_area_value != default_gdal_max_image_area)
        {
            tinyxml2::XMLElement* max_image_area = doc.NewElement("Parameter");
            max_image_area->SetAttribute("name", "max-image-area");
            tinyxml2::XMLText* text = doc.NewText(std::to_string(max_image_area_value).c_str());
            text->SetCData(true);
            max_image_area->InsertEndChild(text);
            ds_gdal->InsertEndChild(max_image_area);
        }
    }
    else
    {
        m_gdal_max_image_area_edit.SetWindowTextW(CString(std::to_string(default_gdal_max_image_area).c_str()));
        AfxMessageBox(_T("max_image_area is not a valid number"));
    }
    if (CheckValidNumberFromString(std::string(CT2A(band_cstr))))
    {
        int band_value = _tstoi(band_cstr);
        if (band_value != default_gdal_band)
        {
            tinyxml2::XMLElement* band = doc.NewElement("Parameter");
            band->SetAttribute("name", "band");
            tinyxml2::XMLText* text_band = doc.NewText(std::to_string(band_value).c_str());
            text_band->SetCData(true);
            band->InsertEndChild(text_band);
            ds_gdal->InsertEndChild(band);
        }
    }
    else
    {
        m_gdal_band_edit.SetWindowTextW(CString(std::to_string(default_gdal_band).c_str()));
        AfxMessageBox(_T("band is not a valid number"));
    }
    if (CheckValidNumberFromString(std::string(CT2A(nodata_cstr))))
    {
        float nodata_value = _tstof(nodata_cstr);
        if (nodata_value != default_gdal_nodata)
        {
            tinyxml2::XMLElement* nodata = doc.NewElement("Parameter");
            nodata->SetAttribute("name", "nodata");
            tinyxml2::XMLText* text_nodata = doc.NewText(std::to_string(nodata_value).c_str());
            text_nodata->SetCData(true);
            nodata->InsertEndChild(text_nodata);
            ds_gdal->InsertEndChild(nodata);
        }
    }
    else
    {
        m_gdal_nodata_edit.SetWindowTextW(CString(std::to_string(default_gdal_nodata).c_str()));
        AfxMessageBox(_T("Nodata is not a valid number"));
    }
    if (CheckValidNumberFromString(std::string(CT2A(nodata_tolerance_cstr))))
    {
        float nodata_tolerance_value = _tstof(nodata_tolerance_cstr);
        if (nodata_tolerance_value != default_gdal_nodata_tolerance)
        {
            tinyxml2::XMLElement* nodata_tolerance = doc.NewElement("Parameter");
            nodata_tolerance->SetAttribute("name", "nodata-tolerance");
            tinyxml2::XMLText* text_nodata_tolerance = doc.NewText(std::to_string(nodata_tolerance_value).c_str());
            text_nodata_tolerance->SetCData(true);
            nodata_tolerance->InsertEndChild(text_nodata_tolerance);
            ds_gdal->InsertEndChild(nodata_tolerance);
        }
    }
    else
    {
        m_gdal_nodata_tolerance_edit.SetWindowTextW(CString(std::to_string(default_gdal_nodata_tolerance).c_str()));
        AfxMessageBox(_T("Nodata-tolerance is not a valid number"));
    }
    if (m_gdal_shared_button.GetCheck() != default_gdal_shared)
    {
        tinyxml2::XMLElement* shared = doc.NewElement("Parameter");
        shared->SetAttribute("name", "shared");
        tinyxml2::XMLText* text = doc.NewText("true");
        text->SetCData(true);
        shared->InsertEndChild(text);
        ds_gdal->InsertEndChild(shared);
    }
    std::stringstream ss;
    tinyxml2::XMLPrinter printer;
    doc.SaveFile("gdal_ds.txt");
    std::fstream fs;
    fs.open("gdal_ds.txt", std::fstream::in | std::fstream::binary);

    std::string buf((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    return std::string(buf);
}
int CFormViewDataSourceGDAL::CheckValidNumberFromString(std::string strNum)
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
void CFormViewDataSourceGDAL::SettingsXml(std::string xml_string)
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
            if (name.compare("file") == 0)
            {
                m_gdal_file_edit.SetWindowTextW(CString(text.c_str()));
            }
            if (name.compare("base") == 0)
            {
                m_gdal_base_edit.SetWindowTextW(CString(text.c_str()));
            }
            if (name.compare("encoding") == 0)
            {
                m_gdal_encoding_edit.SetWindowTextW(CString(text.c_str()));
            }
            if (name.compare("max_image_area") == 0)
            {
                m_gdal_max_image_area_edit.SetWindowTextW(CString(text.c_str()));
            }

            if (name.compare("band") == 0)
            {
                m_gdal_band_edit.SetWindowTextW(CString(text.c_str()));
            }
            if (name.compare("nodata") == 0)
            {
                m_gdal_nodata_edit.SetWindowTextW(CString(text.c_str()));
            }
            if (name.compare("nodata_tolerance") == 0)
            {
                m_gdal_nodata_tolerance_edit.SetWindowTextW(CString(text.c_str()));
            }
            if (name.compare("strict") == 0)
            {
                m_gdal_shared_button.SetCheck(true);
            }
        }
    }
}

BEGIN_MESSAGE_MAP(CFormViewDataSourceGDAL, CBCGPFormView)
    ON_WM_MOUSEACTIVATE()
    ON_STN_CLICKED(IDC_STATIC_GDAL_FILE_OPEN, &CFormViewDataSourceGDAL::OnStnClickedStaticGdalFileOpen)
    ON_STN_CLICKED(IDC_STATIC_GDAL_BASE_OPEN, &CFormViewDataSourceGDAL::OnStnClickedStaticGdalBaseOpen)
    ON_EN_SETFOCUS(IDC_EDIT_GDAL_SCRIPT, &CFormViewDataSourceGDAL::OnSetFocusScriptGDAL)
    ON_EN_KILLFOCUS(IDC_EDIT_GDAL_FILE, &CFormViewDataSourceGDAL::OnKillFocusGDAL)
    ON_EN_KILLFOCUS(IDC_EDIT_GDAL_BASE, &CFormViewDataSourceGDAL::OnKillFocusGDAL)
    ON_EN_KILLFOCUS(IDC_EDIT_GDAL_ENCODING, &CFormViewDataSourceGDAL::OnKillFocusGDAL)
    ON_EN_KILLFOCUS(IDC_EDIT_GDAL_MAX_IMAGE_AREA, &CFormViewDataSourceGDAL::OnKillFocusGDAL)
    ON_EN_KILLFOCUS(IDC_EDIT_GDAL_BAND, &CFormViewDataSourceGDAL::OnKillFocusGDAL)
    ON_EN_KILLFOCUS(IDC_EDIT_GDAL_NODATA, &CFormViewDataSourceGDAL::OnKillFocusGDAL)
    ON_EN_KILLFOCUS(IDC_EDIT_GDAL_NODATA_TOLERANCE, &CFormViewDataSourceGDAL::OnKillFocusGDAL)
END_MESSAGE_MAP()


// CFormViewDataSourceGDAL diagnostics

#ifdef _DEBUG
void CFormViewDataSourceGDAL::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewDataSourceGDAL::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
BOOL CFormViewDataSourceGDAL::CreateView(CWnd* pParent, CCreateContext* pContext)
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


// CFormViewDataSourceGDAL message handlers

int CFormViewDataSourceGDAL::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
void CFormViewDataSourceGDAL::OnInitialUpdate()
{
    CBCGPFormView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class
    CBCGPToolBarImages imagesFolderButton;
    imagesFolderButton.SetImageSize(CSize(24, 24));
    imagesFolderButton.Load(IDB_PNG_FOLDER);

    m_gdal_file_open_static.ModifyStyle(0, SS_ICON);
    m_gdal_file_open_static.ModifyStyle(0, SS_NOTIFY);
    m_gdal_file_open_static.SetIcon(imagesFolderButton.ExtractIcon(0));
    // TODO: Add your specialized code here and/or call the base class
    m_gdal_base_open_static.ModifyStyle(0, SS_ICON);
    m_gdal_base_open_static.ModifyStyle(0, SS_NOTIFY);
    m_gdal_base_open_static.SetIcon(imagesFolderButton.ExtractIcon(0));
    CBCGPToolBarImages imageResetButton;
    imageResetButton.SetImageSize(CSize(40, 40));
    imageResetButton.Load(IDB_PNG_RESET_ICON);
    m_gdal_reset_static.ModifyStyle(0, SS_ICON);
    m_gdal_reset_static.ModifyStyle(0, SS_NOTIFY);
    m_gdal_reset_static.SetIcon(imageResetButton.ExtractIcon(0));
    SetDefault();

    m_Tooltip.Create(this);
    m_Tooltip.Activate(TRUE);
    CBCGPToolTipParams params;
    params.m_bVislManagerTheme = TRUE;

    m_Tooltip.SetParams(&params);

    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GDAL_FILE), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GDAL_BASE), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GDAL_ENCODING), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GDAL_NODATA), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GDAL_NODATA_TOLERANCE), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GDAL_BAND), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_GDAL_MAX_IMAGE_AREA), _T("Document"));
    m_Tooltip.AddTool(GetDlgItem(IDC_CHECK_GDAL_SHARE), _T("Document"));
}


BOOL CFormViewDataSourceGDAL::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    // TODO: Add your specialized code here and/or call the base class

    return CBCGPFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CFormViewDataSourceGDAL::OnStnClickedStaticGdalFileOpen()
{
    // TODO: Add your control notification handler code here
    LPCTSTR typeFile = _T("shp(*.shp)|*.shp|")
        _T("Text (*.json)| *.json|All Files (*.*)|*.*||");
    CFileDialog dlgFile(TRUE, _T("shp"), NULL, OFN_FILEMUSTEXIST,
        typeFile, AfxGetMainWnd());
    if (IDOK == dlgFile.DoModal())
    {
        std::string path = CT2A(dlgFile.GetPathName());
        m_gdal_file_edit.SetWindowTextW(dlgFile.GetPathName());
        OnSetFocusScriptGDAL();
    }
}


void CFormViewDataSourceGDAL::OnStnClickedStaticGdalBaseOpen()
{
    // TODO: Add your control notification handler code here
    LPCTSTR typeFile = _T("shp(*.shp)|*.shp|")
        _T("Text (*.json)| *.json|All Files (*.*)|*.*||");
    CFileDialog dlgFile(TRUE, _T("shp"), NULL, OFN_FILEMUSTEXIST,
        typeFile, AfxGetMainWnd());
    if (IDOK == dlgFile.DoModal())
    {
        std::string path = CT2A(dlgFile.GetPathName());
        m_gdal_base_edit.SetWindowTextW(dlgFile.GetPathName());
        OnSetFocusScriptGDAL();
    }
}
void CFormViewDataSourceGDAL::OnSetFocusScriptGDAL()
{
    // TODO: Add your control notification handler code here
    std::string text = SettingsXml();
    SettingsXml(text);
    m_gdal_script_edit.SetWindowTextW(CString(text.c_str()));
}


void CFormViewDataSourceGDAL::OnKillFocusGDAL()
{
    // TODO: Add your control notification handler code here
    OnSetFocusScriptGDAL();
}


BOOL CFormViewDataSourceGDAL::PreTranslateMessage(MSG* pMsg)
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
