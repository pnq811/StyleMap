// TabMarker1.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "TabMarker1.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CTabMarker1 dialog

IMPLEMENT_DYNAMIC(CTabMarker1, CBCGPDialog)

CTabMarker1::CTabMarker1(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_TAB_MARKER_1, pParent)
{

}

CTabMarker1::~CTabMarker1()
{
}

void CTabMarker1::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MARKER_FILE, m_marker_file_edit);
	DDX_Control(pDX, IDC_EDIT_MARKER_OPACITY, m_marker_opacity_edit);
	DDX_Control(pDX, IDC_EDIT_MARKER_FILL_OPACITY, m_marker_fill_opacity_edit);
	DDX_Control(pDX, IDC_STATIC_MARKER_FILL_OPACITY, m_marker_fill_opacity_static);
	DDX_Control(pDX, IDC_STATIC_MARKER_OPACITY, m_marker_opacity_static);
	DDX_Control(pDX, IDC_STATIC_MARKER_FILE, m_marker_file_static);
	DDX_Control(pDX, IDC_COMBO_MARKER_COMPOP, m_marker_compop_combo);
	DDX_Control(pDX, IDC_STATIC_MARKER_COMP_OP, m_marker_compop_static);
	DDX_Control(pDX, IDC_COMBO_MARKER_DIRECTION, m_marker_direction_combo);
	DDX_Control(pDX, IDC_STATIC_MARKER_DIRECTION, m_marker_direction_static);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_MARKER_STROKE, m_marker_stroke_colorbutton);
	DDX_Control(pDX, IDC_EDIT_MARKER_STROKE_WIDTH, m_marker_stroke_width_edit);
	DDX_Control(pDX, IDC_STATIC_MARKER_STROKE_WIDTH, m_marker_stroke_width_static);
	DDX_Control(pDX, IDC_EDIT_MARKER_WIDTH, m_marker_width_edit);
	DDX_Control(pDX, IDC_EDIT_MARKER_STROKE_OPACITY, m_marker_stroke_opacity);
	DDX_Control(pDX, IDC_EDIT_MARKER_HEIGHT, m_marker_height_edit);
	DDX_Control(pDX, IDC_COMBO_MARKER_PLACEMENT, m_marker_placement_combo);
	DDX_Control(pDX, IDC_COMBO_MARKER_MULTI_POLICY, m_marker_multi_policy_combo);
	DDX_Control(pDX, IDC_COMBO_MARKER_MARKER_TYPE, m_marker_type_combo);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_MARKER_FILL, m_marker_fill_colorbutton);

	DDX_Control(pDX, IDC_STATIC_OPEN_FOLDER, m_marker_open_file_button);
}


BEGIN_MESSAGE_MAP(CTabMarker1, CBCGPDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_FILE, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_OPACITY, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_FILL_OPACITY, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_WIDTH, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_HEIGHT, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_STROKE_OPACITY, &CTabMarker1::OnKillFocusMarkerTab1)
	
	
	
	ON_BN_KILLFOCUS(IDC_MFCCOLORBUTTON_MARKER_FILL, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_BN_KILLFOCUS(IDC_MFCCOLORBUTTON_MARKER_STROKE, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_KILLFOCUS(IDC_COMBO_MARKER_MARKER_TYPE, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_KILLFOCUS(IDC_COMBO_MARKER_COMPOP, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_KILLFOCUS(IDC_COMBO_MARKER_MULTI_POLICY, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_KILLFOCUS(IDC_COMBO_MARKER_PLACEMENT, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_KILLFOCUS(IDC_COMBO_MARKER_DIRECTION, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE_MARKER, &CTabMarker1::OnBnClickedButtonOpenFileMarker)
	
	ON_EN_KILLFOCUS(IDC_EDIT_MARKER_STROKE_WIDTH, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON_MARKER_STROKE, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON_MARKER_FILL, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_PLACEMENT, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_MULTI_POLICY, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_MARKER_TYPE, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_COMPOP, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_DIRECTION, &CTabMarker1::OnKillFocusMarkerTab1)
	ON_STN_CLICKED(IDC_STATIC_OPEN_FOLDER, &CTabMarker1::OnStnClickedStaticOpenFolder)
END_MESSAGE_MAP()


// CTabMarker1 message handlers


int CTabMarker1::CheckValidNumberFromString(std::string strNum)
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

BOOL CTabMarker1::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	
	AddValuePlacement();
	AddMarkerType();
	AddMarkerMultiPolicy();
	AddMarkerDirection();
	AddMarkerCompOp();
	
	SetDefault();
	
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	m_ToolTip.SetParams(&params);
	
	m_ToolTip.AddTool(GetDlgItem(IDC_MFCCOLORBUTTON_MARKER_STROKE),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_MARKER_COMPOP),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_FILE),
		_T("Document"));
	
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_OPACITY),
		_T("Document"));
	
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_STROKE_WIDTH),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_STROKE_OPACITY),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_MARKER_PLACEMENT),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_MARKER_MULTI_POLICY),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_MARKER_MARKER_TYPE),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_WIDTH),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_HEIGHT),
		_T("Document"));
	m_ToolTip.AddTool(GetDlgItem(IDC_MFCCOLORBUTTON_MARKER_FILL),
		_T("Document"));
	
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_MARKER_DIRECTION),
		_T("Document"));
	
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_MARKER_FILL_OPACITY),
		_T("Document"));
	CBCGPToolBarImages imagesFolderButton;
	imagesFolderButton.SetImageSize(CSize(24, 24));
	imagesFolderButton.Load(IDB_PNG_FOLDER);

	m_marker_open_file_button.ModifyStyle(0, SS_ICON);
	m_marker_open_file_button.ModifyStyle(0, SS_NOTIFY);
	m_marker_open_file_button.SetIcon(imagesFolderButton.ExtractIcon(0));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CTabMarker1::PreTranslateMessage(MSG* pMsg)
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

void CTabMarker1::AddMarkerDirection()
{
	for (int i = 0; i < 8; i++)
	{
		m_marker_direction_combo.AddString(CString(
			marker_direction[i].c_str()
		));
	}
}

void CTabMarker1::AddMarkerCompOp()
{
	for (int i = 0; i < 37; i++)
	{
		m_marker_compop_combo.AddString(CString(marker_comop[i].c_str()));
	}
}


void CTabMarker1::AddMarkerMultiPolicy()
{
	for (int i = 0; i < 3; i++)
	{
		m_marker_multi_policy_combo.AddString(
			CString(marker_multi_policy[i].c_str())
		);
	}
}

void CTabMarker1::AddMarkerType()
{
	for (int i = 0; i < 2; i++)
	{
		m_marker_type_combo.AddString(
			CString(marker_marker_type[i].c_str())
		);
	}
}

void CTabMarker1::SetDefault()
{
	
	
	
	m_marker_file_edit.SetWindowTextW(CString(default_marker_file.c_str()));
	m_marker_compop_combo.SetCurSel(
		m_marker_compop_combo.FindStringExact(0,
			CString(default_marker_compop.c_str()))
	);
	m_marker_direction_combo.SetCurSel(
		m_marker_direction_combo.FindStringExact(0,
			CString(default_marker_direction.c_str())
		)
	);
	

	m_marker_fill_colorbutton.SetColor(default_marker_fill);

	

	std::string default_marker_fill_opacity_str = std::to_string(default_marker_fill_opacity);
	m_marker_fill_opacity_edit.SetWindowTextW(CString(
		default_marker_fill_opacity_str.c_str()));


	m_marker_stroke_colorbutton.SetColor(default_marker_stroke);

	std::string default_marker_height_str =
		std::to_string(default_marker_height);
	m_marker_height_edit.SetWindowTextW(
		CString(default_marker_height_str.c_str())
	);

	std::string default_marker_stroke_opacity_str =
		std::to_string(default_marker_stroke_opacity);
	m_marker_stroke_opacity.SetWindowTextW(
		CString(default_marker_stroke_opacity_str.c_str())
	);
	std::string default_marker_stroke_width_str =
		std::to_string(default_marker_stroke_width);
	
	m_marker_stroke_width_edit.SetWindowTextW(
		CString(default_marker_stroke_width_str.c_str())
	);


	std::string default_marker_opacity_str = std::to_string(default_marker_opacity);
	m_marker_opacity_edit.SetWindowTextW(CString(
		default_marker_opacity_str.c_str()));

	std::string default_marker_width_str =
		std::to_string(default_marker_width);
	m_marker_width_edit.SetWindowTextW(
		CString(default_marker_width_str.c_str())
	);

	m_marker_placement_combo.SetCurSel(
		m_marker_placement_combo.FindStringExact(
			0, CString(default_marker_placement.c_str())
		)
	);
	m_marker_type_combo.SetCurSel(
		m_marker_type_combo.FindStringExact(
			0, CString(default_marker_marker_type.c_str())
		)
	);
	m_marker_multi_policy_combo.SetCurSel(
		m_marker_multi_policy_combo.FindStringExact(
			0, CString(default_marker_multi_policy.c_str())
		)
	);
	
}
void CTabMarker1::AddValuePlacement()
{
	for (int i = 0; i < 5; i++)
	{
		m_marker_placement_combo.AddString(CString(marker_placement[i].c_str()));
	}
}
std::vector<std::string> CTabMarker1::TokenizeString(std::string in_str, const char delimeter)
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

void CTabMarker1::SetMarkerTab1(S_Marker& t_marker)
{
	
	if (t_marker.marker_file.compare(default_marker_file) != 0)
	{
		m_marker_file_edit.SetWindowTextW(CString(t_marker.marker_file.c_str()));
	}
	if (t_marker.marker_opacity  != default_marker_opacity)
	{
		m_marker_opacity_edit.SetWindowTextW(CString(std::to_string(t_marker.marker_opacity).c_str()));
	}
	if (t_marker.marker_fill_opacity != default_marker_fill_opacity)
	{
		m_marker_fill_opacity_edit.SetWindowTextW(CString(std::to_string(t_marker.marker_fill_opacity).c_str()));
	}
	if (t_marker.marker_stroke != default_marker_stroke)
	{
		m_marker_stroke_colorbutton.SetColor(t_marker.marker_stroke);
	}
	if (t_marker.marker_stroke_width != default_marker_stroke_width)
	{
		m_marker_stroke_width_edit.SetWindowTextW(CString(std::to_string(t_marker.marker_stroke_width).c_str()));
	}
	if (t_marker.marker_fill != default_marker_fill)
	{
		m_marker_fill_colorbutton.SetColor(t_marker.marker_fill);
	}
	if (t_marker.marker_placement.compare(default_marker_placement) != 0)
	{
		m_marker_placement_combo.SetCurSel(m_marker_placement_combo.FindStringExact(
			0, CString(t_marker.marker_placement.c_str())
		));
	}
	if (t_marker.marker_stroke_opacity != default_marker_stroke_opacity)
	{
		m_marker_stroke_opacity.SetWindowTextW(CString(std::to_string(
			t_marker.marker_stroke_opacity).c_str()));
	}
	if (t_marker.marker_width != default_marker_width)
	{
		m_marker_width_edit.SetWindowTextW(CString(std::to_string(
			t_marker.marker_width).c_str()));
	}
	if (t_marker.marker_height != default_marker_height)
	{
		m_marker_height_edit.SetWindowTextW(CString(std::to_string(
			t_marker.marker_height).c_str()));
	}
	if (t_marker.marker_multi_policy.compare(default_marker_multi_policy) != 0)
	{
		m_marker_multi_policy_combo.SetCurSel(m_marker_multi_policy_combo.FindStringExact(
			0, CString(t_marker.marker_multi_policy.c_str())
		));
	}
	if (t_marker.marker_type.compare(default_marker_marker_type) != 0)
	{
		m_marker_type_combo.SetCurSel(m_marker_type_combo.FindStringExact(
			0, CString(t_marker.marker_type.c_str())
		));
	}
	if (t_marker.marker_compop .compare(default_marker_compop)!=0)
	{
		m_marker_compop_combo.SetCurSel(m_marker_compop_combo.FindStringExact(
			0, CString(t_marker.marker_compop.c_str())
		));
	}
	if (t_marker.marker_direction.compare(default_marker_direction) != 0)
	{
		m_marker_direction_combo.SetCurSel(m_marker_direction_combo.FindStringExact(
			0, CString(t_marker.marker_direction.c_str())
		));
	}
	
	
}



void CTabMarker1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CBCGPDialog::OnPaint() for painting messages
}
HCURSOR CTabMarker1::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return CBCGPDialog::OnQueryDragIcon();
}


void CTabMarker1::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CBCGPDialog::OnSysCommand(nID, lParam);
}

S_Marker CTabMarker1::GetMarkerSymbolizer()
{
	S_Marker t_marker;

	CString file_cstr, opacity_cstr, fill_opacity_cstr, width_cstr,
		height_cstr, stroke_opacity_cstr, marker_type_cstr,
		stroke_width_cstr, placement_cstr, compop_cstr, direction_cstr;
	//m_marker_file_edit.GetWindowTextW(file_cstr);
	m_marker_stroke_width_edit.GetWindowTextW(stroke_width_cstr);

	CString multi_policy_cstr;
	m_marker_stroke_opacity.GetWindowTextW(stroke_opacity_cstr);
	t_marker.marker_stroke = m_marker_stroke_colorbutton.GetColor();
	m_marker_file_edit.GetWindowTextW(file_cstr);
	m_marker_opacity_edit.GetWindowTextW(opacity_cstr);
	m_marker_fill_opacity_edit.GetWindowTextW(fill_opacity_cstr);
	m_marker_height_edit.GetWindowTextW(height_cstr);
	m_marker_type_combo.GetWindowTextW(marker_type_cstr);
	m_marker_placement_combo.GetWindowTextW(placement_cstr);
	m_marker_multi_policy_combo.GetWindowTextW(multi_policy_cstr);
	
	m_marker_width_edit.GetWindowTextW(width_cstr);
	m_marker_compop_combo.GetWindowTextW(compop_cstr);
	m_marker_direction_combo.GetWindowTextW(direction_cstr);
	
	t_marker.marker_fill = m_marker_fill_colorbutton.GetColor();
	
	t_marker.marker_file = CW2A(file_cstr);
	std::string opacity = CT2A(opacity_cstr);
	if(!CheckValidNumberFromString(opacity))
	{
		m_marker_opacity_edit.SetWindowTextW(CString(
			std::to_string(default_marker_opacity).c_str()
		));
		t_marker.marker_opacity = default_marker_opacity;
		AfxMessageBox(_T("Opacity is not a valid number!"));
	}
	else
	{
		t_marker.marker_opacity = _tstof(opacity_cstr);
	}
	if (!CheckValidNumberFromString(std::string(CT2A(fill_opacity_cstr))))
	{
		m_marker_fill_opacity_edit.SetWindowTextW(CString(
			std::to_string(default_marker_fill_opacity).c_str()));
		t_marker.marker_fill_opacity = default_marker_fill_opacity;
		AfxMessageBox(_T("Fill opacity is not a valid number!"));
		
	}
	else
	{
		t_marker.marker_fill_opacity = _tstof(fill_opacity_cstr);
	}
	if (!CheckValidNumberFromString(std::string(CT2A(stroke_opacity_cstr))))
	{
		m_marker_stroke_opacity.SetWindowTextW(CString(
			std::to_string(default_marker_stroke_opacity).c_str()));
		AfxMessageBox(_T("Stroke opacity is not a valid number!!"));
		t_marker.marker_stroke_opacity = default_marker_stroke_opacity;
	}
	else t_marker.marker_stroke_opacity = _tstof(stroke_opacity_cstr);
	
	if (!CheckValidNumberFromString(std::string(CT2A(stroke_width_cstr))))
	{
		m_marker_stroke_width_edit.SetWindowTextW(CString(
			std::to_string(default_marker_stroke_width).c_str()));
		AfxMessageBox(_T("Stroke width is not a valid number!!"));
		t_marker.marker_stroke_width = default_marker_stroke_width;
	}
	else t_marker.marker_stroke_width = _tstof(stroke_width_cstr);

	
	if (!CheckValidNumberFromString(std::string(CT2A(width_cstr))))
	{
		m_marker_width_edit.SetWindowTextW(CString(
			std::to_string(default_marker_width).c_str()));
		AfxMessageBox(_T("Width is not a valid number!!"));
		t_marker.marker_width = default_marker_width;
	}
	else t_marker.marker_width = _tstof(width_cstr);
	
	
	if (!CheckValidNumberFromString(std::string(CT2A(height_cstr))))
	{
		m_marker_height_edit.SetWindowTextW(CString(
			std::to_string(default_marker_height).c_str()));
		AfxMessageBox(_T("Height is not a valid number!!"));
		t_marker.marker_height = default_marker_height;
	}
	else t_marker.marker_height = _tstof(height_cstr);
	t_marker.marker_multi_policy = CW2A(multi_policy_cstr);
	t_marker.marker_type = CW2A(marker_type_cstr);
	t_marker.marker_placement = CW2A(placement_cstr);
	
	t_marker.marker_compop = CW2A(compop_cstr);
	t_marker.marker_direction = CW2A(direction_cstr);
	
	return S_Marker(t_marker);
}




void CTabMarker1::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	/*CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;
	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX = itemRect.left;
	nY = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 1;
	nYc = tabRect.bottom - nY - 1;

	SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);*/
}


void CTabMarker1::OnSetFocus(CWnd* pOldWnd)
{
	CBCGPDialog::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
}


void CTabMarker1::OnKillFocusMarkerTab1()
{
	// TODO: Add your control notification handler code here
	
	CMainFrame* mainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if (mainFrame != NULL)
	{
		if (mainFrame->m_wndMarkerSymbolizer.m_pFormViewMarker->m_button_check_marker_default.GetCheck() == 1)
		{
			mainFrame->m_wndMarkerSymbolizer.m_pFormViewMarker->m_button_check_marker_default
				.SetCheck(0);
		}
		mainFrame->m_wndMarkerSymbolizer.m_pFormViewMarker->SetTextScript();
	}
}


void CTabMarker1::OnBnClickedButtonOpenFileMarker()
{
	// TODO: Add your control notification handler code here
	LPCTSTR typeFile = _T("svg(*.svg)|*.jpg|"
		"(PNG)*.png|*.tiff|*.webp|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("png"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		typeFile, AfxGetMainWnd());
	if (IDOK == dlgFile.DoModal())
	{
		CStdioFile file(dlgFile.GetPathName(), CFile::modeRead | CFile::typeText);
		bool successful{ false };
		std::string path = CT2A(dlgFile.GetPathName());
		m_marker_file_edit.SetWindowTextW(dlgFile.GetPathName());
	}
}






void CTabMarker1::OnBnClickedMfccolorbuttonMarkerStroke()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker1::OnBnClickedMfccolorbuttonMarkerFill()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker1::OnCbnSelchangeComboMarkerPlacement()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker1::OnCbnSelchangeComboMarkerMultiPolicy()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker1::OnCbnSelchangeComboMarkerMarkerType()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker1::OnCbnSelchangeComboMarkerCompop()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker1::OnCbnSelchangeComboMarkerDirection()
{
	// TODO: Add your control notification handler code here
}


void CTabMarker1::OnStnClickedStaticOpenFolder()
{
	// TODO: Add your control notification handler code here

	LPCTSTR typeFile = _T("svg(*.svg)|*.jpg|"
		"(PNG)*.png|*.tiff|*.webp|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("png"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		typeFile, AfxGetMainWnd());
	if (IDOK == dlgFile.DoModal())
	{
		CStdioFile file(dlgFile.GetPathName(), CFile::modeRead | CFile::typeText);
		bool successful{ false };
		std::string path = CT2A(dlgFile.GetPathName());
		m_marker_file_edit.SetWindowTextW(dlgFile.GetPathName());
	}
}
