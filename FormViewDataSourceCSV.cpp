// FormViewDataSourceCSV.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "FormViewDataSourceCSV.h"
#include <sstream>
#include <fstream>
#include <string>
// CFormViewDataSourceCSV

IMPLEMENT_DYNCREATE(CFormViewDataSourceCSV, CBCGPFormView)

CFormViewDataSourceCSV::CFormViewDataSourceCSV()
	: CBCGPFormView(IDD_FORMVIEW_DATASOURCE_CSV)
{
	/*std::string sstring = SettingsXml();
	sstring;*/
	
}

CFormViewDataSourceCSV::~CFormViewDataSourceCSV()
{
}

void CFormViewDataSourceCSV::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CSV_FILE, m_csv_file_edit);
	DDX_Control(pDX, IDC_STATIC_CSV_FILE_OPEN, m_csv_file_open_static);
	DDX_Control(pDX, IDC_EDIT_CSV_BASE, m_csv_base_edit);
	DDX_Control(pDX, IDC_STATIC_CSV_BASE_OPEN, m_csv_base_open_static);
	DDX_Control(pDX, IDC_EDIT_CSV_ENCODING, m_csv_encoding_edit);
	DDX_Control(pDX, IDC_EDIT_CSV_ROW_LIMIT, m_csv_row_limit_edit);
	DDX_Control(pDX, IDC_EDIT_CSV_ESCAPE, m_csv_escape_edit);
	DDX_Control(pDX, IDC_EDIT_CSV_QUOTE, m_csv_quote_edit);
	DDX_Control(pDX, IDC_EDIT_CSV_SEPARATER, m_csv_separator_edit);
	DDX_Control(pDX, IDC_EDIT_CSV_HEADERS, m_csv_headers_edit);
	DDX_Control(pDX, IDC_EDIT_CSV_FILE_SIZE_MAX, m_csv_file_size_max_edit);
	DDX_Control(pDX, IDC_CHECK_CSV_STRICT, m_csv_strict_button);
	DDX_Control(pDX, IDC_EDIT_CSV_SCRIPT, m_csv_script_edit);
	DDX_Control(pDX, IDC_STATIC_RESET_DEFAULT, m_csv_reset_button_static);
}

BEGIN_MESSAGE_MAP(CFormViewDataSourceCSV, CBCGPFormView)
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
	ON_STN_CLICKED(IDC_STATIC_CSV_FILE_OPEN, &CFormViewDataSourceCSV::OnStnClickedStaticCsvFileOpen)
	ON_STN_CLICKED(IDC_STATIC_CSV_BASE_OPEN, &CFormViewDataSourceCSV::OnStnClickedStaticCsvBaseOpen)
	ON_EN_KILLFOCUS(IDC_EDIT_CSV_FILE, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_EN_KILLFOCUS(IDC_EDIT_CSV_BASE, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_EN_KILLFOCUS(IDC_EDIT_CSV_ENCODING, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_EN_KILLFOCUS(IDC_EDIT_CSV_ROW_LIMIT, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_EN_KILLFOCUS(IDC_EDIT_CSV_ESCAPE, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_EN_KILLFOCUS(IDC_EDIT_CSV_QUOTE, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_EN_KILLFOCUS(IDC_EDIT_CSV_SEPARATER, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_EN_KILLFOCUS(IDC_EDIT_CSV_HEADERS, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_EN_KILLFOCUS(IDC_EDIT_CSV_FILE_SIZE_MAX, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_BN_KILLFOCUS(IDC_CHECK_CSV_STRICT, &CFormViewDataSourceCSV::OnKillFocusCSV)
	ON_EN_SETFOCUS(IDC_EDIT_CSV_SCRIPT, &CFormViewDataSourceCSV::OnSetFocusScriptCSV)
	ON_STN_CLICKED(IDC_STATIC_RESET_DEFAULT, &CFormViewDataSourceCSV::OnStnClickedStaticResetDefault)
END_MESSAGE_MAP()


// CFormViewDataSourceCSV diagnostics

#ifdef _DEBUG
void CFormViewDataSourceCSV::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewDataSourceCSV::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormViewDataSourceCSV message handlers
BOOL CFormViewDataSourceCSV::CreateView(CWnd* pParent, CCreateContext* pContext)
{
    CRect rect(0, 0, 300, 300);

    if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
        rect, pParent, AFX_IDW_PANE_FIRST, pContext))
    {
        TRACE0("Warning: couldn't create CFormViewDataSourceCSV!\n");
        return FALSE;
    }

    return TRUE;
}


int CFormViewDataSourceCSV::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	return 0;
}
int CFormViewDataSourceCSV::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
void CFormViewDataSourceCSV::AddParameterTag(CString text_value, std::string name,
	std::string de_value, tinyxml2::XMLElement*& ds, tinyxml2::XMLDocument& doc)
{
	/// <summary>
	/// The function is used to add a parameter tag with the condition that the text is not the default value.
	/// </summary>
	/// <param name="text_value">The text of the tag</param>
	/// <param name="name">The parameter's name of the tag</param>
	/// <param name="de_value">The default value.</param>
	/// <param name="ds">The tinyxml Element of tag</param>
	/// <param name="doc">The tinyxml Document</param>
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
std::string CFormViewDataSourceCSV::SettingsXml()
{
	/// <summary>
	/// The function return the xml text from the value of all controls.
	/// </summary>
	/// <returns>The xml text</returns>
	tinyxml2::XMLDocument doc;

	CString file_cstr, base_cstr, encoding_cstr, row_limit_cstr, strict_cstr,
		escape_cstr, quote_cstr, separator_cstr, headers_cstr, file_size_max_cstr;

	m_csv_file_edit.GetWindowTextW(file_cstr);
	m_csv_base_edit.GetWindowTextW(base_cstr);
	m_csv_encoding_edit.GetWindowTextW(encoding_cstr);
	m_csv_row_limit_edit.GetWindowTextW(row_limit_cstr);
	m_csv_strict_button.GetCheck();
	m_csv_escape_edit.GetWindowTextW(escape_cstr);
	m_csv_quote_edit.GetWindowTextW(quote_cstr);
	m_csv_separator_edit.GetWindowTextW(separator_cstr);
	m_csv_headers_edit.GetWindowTextW(headers_cstr);
	m_csv_file_size_max_edit.GetWindowTextW(file_size_max_cstr);
	tinyxml2::XMLElement* ds_csv = doc.NewElement("Datasource");
	doc.InsertFirstChild(ds_csv);

	// type
	tinyxml2::XMLElement* type = doc.NewElement("Parameter");
	type->SetAttribute("name", "type");
	tinyxml2::XMLText* text_param = doc.NewText("csv");
	text_param->SetCData(true);
	type->InsertEndChild(text_param);
	ds_csv->InsertEndChild(type);
	//file
	AddParameterTag(file_cstr,"file", default_csv_file, ds_csv, doc);
	// base
	AddParameterTag(base_cstr,"base", default_csv_base, ds_csv, doc);
	// encoding
	AddParameterTag(encoding_cstr, "encoding", default_csv_encoding, ds_csv, doc);
	// escape
	AddParameterTag(escape_cstr, "escape", default_csv_escape, ds_csv, doc);
	// separator
	AddParameterTag(separator_cstr, "separator", default_csv_separator, ds_csv, doc);

	// row_limit
	if (CheckValidNumberFromString(std::string(CT2A(row_limit_cstr))))
	{
		int row_limit_value = _tstoi(row_limit_cstr);
		if (row_limit_value != default_csv_row_limit)
		{
			tinyxml2::XMLElement* row_limit = doc.NewElement("Parameter");
			row_limit->SetAttribute("name", "row_limit");
			tinyxml2::XMLText* text_row_limit = doc.NewText(std::string(CT2A(row_limit_cstr)).c_str());
			text_row_limit->SetCData(true);
			row_limit->InsertEndChild(text_row_limit);
			ds_csv->InsertEndChild(row_limit);
		}
	}
	else
	{
		m_csv_row_limit_edit.SetWindowTextW(CString(std::to_string(default_csv_row_limit).c_str()));
		AfxMessageBox(_T("Row limit is not a valid number!"));
	}
	// file_size_max
	if (CheckValidNumberFromString(std::string(CT2A(file_size_max_cstr))))
	{
		int file_size_max_value = _tstoi(file_size_max_cstr);
		if (file_size_max_value != default_csv_file_size_max)
		{
			tinyxml2::XMLElement* file_size_max = doc.NewElement("Parameter");
			file_size_max->SetAttribute("name", "file_size_max");
			tinyxml2::XMLText* text_file_size_max = doc.NewText(std::string(CT2A(file_size_max_cstr)).c_str());
			text_file_size_max->SetCData(true);
			file_size_max->InsertEndChild(text_file_size_max);
			ds_csv->InsertEndChild(file_size_max);
		}
	}
	else
	{
		m_csv_file_size_max_edit.SetWindowTextW(CString(std::to_string(default_csv_file_size_max).c_str()));
		AfxMessageBox(_T("file_size_max is not a valid number!"));
	}
	if (m_csv_strict_button.GetCheck() != default_csv_strict)
	{
		tinyxml2::XMLElement* strict = doc.NewElement("Parameter");
		strict->SetAttribute("name", "strict");
		tinyxml2::XMLText* text_strict = doc.NewText("true");
		text_strict->SetCData(true);
		strict->InsertEndChild(text_strict);
		ds_csv->InsertEndChild(strict);
	}
	// headers

	AddParameterTag(headers_cstr, "headers", default_csv_headers, ds_csv, doc);

	// quote
	AddParameterTag(quote_cstr, "quote", default_csv_quote, ds_csv, doc);

	std::stringstream ss;
	tinyxml2::XMLPrinter printer;
	doc.SaveFile("csv_ds.txt");
	std::fstream fs;
	fs.open("csv_ds.txt", std::fstream::in | std::fstream::binary);
	
	std::string buf((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

	return std::string(buf);
}

void CFormViewDataSourceCSV::SettingsXml(std::string xml_string)
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
			if (name.compare("type"))
			{
				std::string text = std::string((element->GetText()));
				if (text.compare("csv") != 0)
					break;
			}
			if (name.compare("file") == 0)
			{
				std::string text = std::string((element->GetText()));
				m_csv_file_edit.SetWindowTextW(CString(text.c_str()));
			}
			if (name.compare("base") == 0)
			{
				std::string text = std::string((element->GetText()));
				m_csv_base_edit.SetWindowTextW(CString(text.c_str()));
			}
			if (name.compare("encoding") == 0)
			{
				std::string text = std::string((element->GetText()));
				m_csv_encoding_edit.SetWindowTextW(CString(text.c_str()));
			}
			if (name.compare("escape") == 0)
			{
				std::string text = std::string((element->GetText()));
				m_csv_escape_edit.SetWindowTextW(CString(text.c_str()));
			}
			if (name.compare("row_limit") == 0)
			{
				std::string text = std::string((element->GetText()));
				m_csv_row_limit_edit.SetWindowTextW(CString(text.c_str()));
			}
			if (name.compare("quote") == 0)
			{
				std::string text = std::string((element->GetText()));
				m_csv_quote_edit.SetWindowTextW(CString(text.c_str()));
			}
			if (name.compare("separator") == 0)
			{
				std::string text = std::string((element->GetText()));
				m_csv_separator_edit.SetWindowTextW(CString(text.c_str()));
			}
			if (name.compare("headers") == 0)
			{
				std::string text = std::string((element->GetText()));
				m_csv_headers_edit.SetWindowTextW(CString(text.c_str()));
			}
			if (name.compare("file_size_max") == 0)
			{
				std::string text = std::string((element->GetText()));
				m_csv_file_size_max_edit.SetWindowTextW(CString(text.c_str()));
			}
			if (name.compare("strict") == 0)
			{
				m_csv_strict_button.SetCheck(true);
			}
		}
	}
}


void CFormViewDataSourceCSV::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();
	CBCGPToolBarImages imagesFolderButton;
	imagesFolderButton.SetImageSize(CSize(24, 24));
	imagesFolderButton.Load(IDB_PNG_FOLDER);

	m_csv_file_open_static.ModifyStyle(0, SS_ICON);
	m_csv_file_open_static.ModifyStyle(0, SS_NOTIFY);
	m_csv_file_open_static.SetIcon(imagesFolderButton.ExtractIcon(0));
	// TODO: Add your specialized code here and/or call the base class
	m_csv_base_open_static.ModifyStyle(0, SS_ICON);
	m_csv_base_open_static.ModifyStyle(0, SS_NOTIFY);
	m_csv_base_open_static.SetIcon(imagesFolderButton.ExtractIcon(0));

	CBCGPToolBarImages imageResetButton;
	imageResetButton.SetImageSize(CSize(40, 40));
	imageResetButton.Load(IDB_PNG_RESET_ICON);
	m_csv_reset_button_static.ModifyStyle(0, SS_ICON);
	m_csv_reset_button_static.ModifyStyle(0, SS_NOTIFY);
	m_csv_reset_button_static.SetIcon(imageResetButton.ExtractIcon(0));
	m_csv_reset_button_static.SetWindowTextW(_T("Default"));

	SetDefault();
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);
	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	m_ToolTip.SetParams(&params);
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CSV_FILE), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CSV_BASE), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CSV_ENCODING), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CSV_ROW_LIMIT), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CSV_FILE_SIZE_MAX), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CSV_HEADERS), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CSV_QUOTE), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CSV_SEPARATER), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_CSV_ESCAPE), _T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_CSV_STRICT), _T("Document"));
	
}


void CFormViewDataSourceCSV::OnStnClickedStaticCsvFileOpen()
{
	// TODO: Add your control notification handler code here
	LPCTSTR typeFile = _T("CSV(*.csv)|*.csv|")
		_T("Text (*.txt)| *.txt|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("shp"), NULL, OFN_FILEMUSTEXIST,
		typeFile, AfxGetMainWnd());
	if (IDOK == dlgFile.DoModal())
	{
		std::string path = CT2A(dlgFile.GetPathName());
		m_csv_file_edit.SetWindowTextW(dlgFile.GetPathName());
		OnSetFocusScriptCSV();
	}
}


void CFormViewDataSourceCSV::OnStnClickedStaticCsvBaseOpen()
{
	// TODO: Add your control notification handler code here
	LPCTSTR typeFile = _T("CSV(*.csv)|*.csv|")
		_T("Text (*.txt)| *.txt|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("shp"), NULL, OFN_FILEMUSTEXIST,
		typeFile, AfxGetMainWnd());
	if (IDOK == dlgFile.DoModal())
	{
		std::string path = CT2A(dlgFile.GetPathName());
		m_csv_base_edit.SetWindowTextW(dlgFile.GetPathName());
		OnSetFocusScriptCSV();
	}
}


void CFormViewDataSourceCSV::OnKillFocusCSV()
{
	// TODO: Add your control notification handler code here
	OnSetFocusScriptCSV();
}


void CFormViewDataSourceCSV::OnSetFocusScriptCSV()
{
	// TODO: Add your control notification handler code here
	std::string xml_str = SettingsXml();
	SettingsXml(xml_str);
	m_csv_script_edit.SetWindowTextW(CString(xml_str.c_str()));
}
int CFormViewDataSourceCSV::CheckValidNumberFromString(std::string strNum)
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
void CFormViewDataSourceCSV::SetDefault()
{
	m_csv_file_edit.SetWindowTextW(CString(default_csv_file.c_str()));
	m_csv_base_edit.SetWindowTextW(CString(default_csv_base.c_str()));
	m_csv_encoding_edit.SetWindowTextW(CString(default_csv_encoding.c_str()));
	m_csv_quote_edit.SetWindowTextW(CString(default_csv_quote.c_str()));
	m_csv_separator_edit.SetWindowTextW(CString(default_csv_separator.c_str()));
	m_csv_escape_edit.SetWindowTextW(CString(default_csv_escape.c_str()));
	m_csv_headers_edit.SetWindowTextW(CString(default_csv_headers.c_str()));
	m_csv_row_limit_edit.SetWindowTextW(CString(std::to_string(default_csv_row_limit).c_str()));
	m_csv_file_size_max_edit.SetWindowTextW(CString(std::to_string(default_csv_file_size_max).c_str()));
	m_csv_strict_button.SetCheck(default_csv_strict);
}
void CFormViewDataSourceCSV::OnStnClickedStaticResetDefault()
{
	// TODO: Add your control notification handler code here
	SetDefault();
	OnSetFocusScriptCSV();
}


BOOL CFormViewDataSourceCSV::PreTranslateMessage(MSG* pMsg)
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
