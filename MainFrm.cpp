// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SymbolizerProject.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CBCGPMDIFrameWnd)
const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, &CMainFrame::OnToolbarReset)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_TOOLBOX, &CMainFrame::OnToolBox)
	ON_COMMAND(ID_MDI_MOVE_TO_NEXT_GROUP, &CMainFrame::OnMdiMoveToNextGroup)
	ON_COMMAND(ID_MDI_MOVE_TO_PREV_GROUP, &CMainFrame::OnMdiMoveToPrevGroup)
	ON_COMMAND(ID_MDI_NEW_HORZ_TAB_GROUP, &CMainFrame::OnMdiNewHorzTabGroup)
	ON_COMMAND(ID_MDI_NEW_VERT_GROUP, &CMainFrame::OnMdiNewVertGroup)
	ON_COMMAND(ID_MDI_CANCEL, &CMainFrame::OnMdiCancel)
	
	
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CBCGPToolBar::EnableQuickCustomization();
	CBCGPPopupMenu::SetForceMenuFocus(FALSE);
	CBCGPMDITabParams mdiTabParams;

	mdiTabParams.m_bTabIcons = TRUE;
	mdiTabParams.m_tabLocation = CBCGPTabWnd::LOCATION_TOP;
	mdiTabParams.m_bDocumentMenu = TRUE;
	mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_SCROLLED;
	mdiTabParams.m_closeButtonMode = CBCGPTabWnd::TAB_CLOSE_BUTTON_HIGHLIGHTED_COMPACT;

	EnableMDITabbedGroups(TRUE, mdiTabParams);

	EnableTearOffMDIChildren();
	// Menu will not take the focus on activation:
	

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, FALSE, 0, 0, IDB_TOOLBAR_HC))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// ID_VIEW_POLYGON;
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize(CSize(16, 16));
	imagesWorkspace.Load(IDB_WORKSPACE);
	globalUtils.ScaleByDPI(imagesWorkspace);

	const int nPaneSize = globalUtils.ScaleByDPI(300);
	if (!m_wndWorkSpace.Create(_T("View 1"), this, CRect(0, 0, 300, 300),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return FALSE;      // fail to create
	}

	m_wndWorkSpace.SetIcon(imagesWorkspace.ExtractIcon(0), FALSE);



	
	
	m_wndPolygonSymbolizer.SetIcon(imagesWorkspace.ExtractIcon(0), FALSE);
	
	
	
	m_wndPolygonPatternSymbolizer.SetIcon(imagesWorkspace.ExtractIcon(0), FALSE);


	m_wndDataSourceOCCI.SetIcon(imagesWorkspace.ExtractIcon(0), FALSE);
	m_wndMarkerSymbolizer.SetIcon(imagesWorkspace.ExtractIcon(0), FALSE);

	if (!m_wndWorkSpace2.Create(_T("View 2"),
		this, TRUE, MAKEINTRESOURCE(IDD_DIALOGBAR),
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI,
		ID_VIEW_WORKSPACE2))
	{
		TRACE0("Failed to create Workspace bar 2\n");
		return FALSE;      // fail to create
	}

	m_wndWorkSpace2.SetIcon(imagesWorkspace.ExtractIcon(2), FALSE);


	const int nOutputPaneSize = globalUtils.ScaleByDPI(150);

	//if (!m_wndOutput.Create(_T("Output"), this, CSize(nOutputPaneSize, nOutputPaneSize),
	//	TRUE /* Has gripper */, ID_VIEW_OUTPUT,
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("Failed to create output bar\n");
	//	return -1;      // fail to create
	//}
	// m_wndOutput.SetIcon(imagesWorkspace.ExtractIcon(3), FALSE);

	if (!m_wndPropGrid.Create(_T("Properties"), this, CRect(0, 0, nPaneSize, nPaneSize),
		TRUE,
		ID_VIEW_PROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties Bar\n");
		return FALSE;		// fail to create
	}

	m_wndPropGrid.SetIcon(imagesWorkspace.ExtractIcon(4), FALSE);


	if (!m_wndToolBox.Create(_T("ToolBox"), this, CRect(0, 0, nPaneSize, 2 * nPaneSize), TRUE, ID_TOOLBOX,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_BCGP_CLOSE | CBRS_BCGP_FLOAT))
	{
		TRACE0("Failed to create ToolBox Bar\n");
		return FALSE;      // fail to create
	}

	m_wndToolBox.SetIcon(imagesWorkspace.ExtractIcon(6), FALSE);

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString(IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText(strMainToolbarTitle);

	// TODO: delete these three lines if you don't want the toolbar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPolygonSymbolizer.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPolygonPatternSymbolizer.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMarkerSymbolizer.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPropGrid.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBox.EnableDocking(CBRS_ALIGN_ANY);
	
	m_wndDataSourceCSV.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDataSourceGDAL.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDataSourceGEOJSON.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDataSourceOCCI.EnableDocking(CBRS_ALIGN_ANY);
	
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndWorkSpace);
	DockControlBar(&m_wndPolygonPatternSymbolizer);
	DockControlBar(&m_wndPolygonSymbolizer);
	DockControlBar(&m_wndMarkerSymbolizer);
	DockControlBar(&m_wndDataSourceCSV);
	DockControlBar(&m_wndDataSourceGDAL);
	DockControlBar(&m_wndDataSourceGEOJSON);
	DockControlBar(&m_wndDataSourceOCCI);
	m_wndWorkSpace2.AttachToTabWnd(&m_wndWorkSpace, BCGP_DM_STANDARD, FALSE, NULL);
	//DockControlBar(&m_wndOutputBar);
	DockControlBar(&m_wndPropGrid);
	DockControlBar(&m_wndToolBox);
	
	m_wndToolBox.SetAutoHideMode(TRUE, CBRS_ALIGN_RIGHT);

	// Enable windows manager:
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE, FALSE, TRUE);

	// Enable windows navigator (activated by Ctrl+Tab/Ctrl+Shift+Tab):
	EnableWindowsNavigator();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

// CMainFrame message handlers


LRESULT CMainFrame::OnToolbarReset(WPARAM wp,LPARAM)
{
	// TODO: reset toolbar with id = (UINT) wp to its initial state:
	UINT uiToolBarId = (UINT)wp;
	if (uiToolBarId == IDR_MAINFRAME)
	{
		
	}

	return 0;
}

void CMainFrame::OnToolBox()
{
	int nPage = -1;
	int nTool = m_wndToolBox.GetLastClickedTool(nPage);

	const MSG* pMsg = CWnd::GetCurrentMessage();

	if (pMsg->lParam != (LPARAM)m_wndToolBox.GetSafeHwnd())
	{
		m_wndToolBox.ShowControlBar(!m_wndToolBox.IsVisible(), FALSE, TRUE);
		return;
	}

	TRACE(_T("Toolbox item clicked page = %d, item = %d\n"), nPage, nTool);
}


void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}
void CMainFrame::EnkillFocus_Datasources_Postgis()
{
	m_wndWorkSpace_Postgis.EnkillFocus_Datasources_Postgis();
}
void CMainFrame::OnViewCustomize()
{
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode(BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPVisualManagerVS2005));
		CBCGPDockManager::SetDockMode(BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode(BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode(BCGP_DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CBCGPVisualManager2007::SetStyle(CBCGPVisualManager2007::VS2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CBCGPVisualManager2007::SetStyle(CBCGPVisualManager2007::VS2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CBCGPVisualManager2007::SetStyle(CBCGPVisualManager2007::VS2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CBCGPVisualManager2007::SetStyle(CBCGPVisualManager2007::VS2007_Aqua);
			break;
		}

		CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode(BCGP_DT_SMART);
	}

	m_wndOutput.UpdateFonts();
	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::OnShowMDITabContextMenu(CPoint point, DWORD dwAllowedItems, BOOL bDrop)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(bDrop ? IDR_POPUP_DROP_MDITABS : IDR_POPUP_MDITABS));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	if ((dwAllowedItems & BCGP_MDI_CREATE_HORZ_GROUP) == 0)
	{
		pPopup->DeleteMenu(ID_MDI_NEW_HORZ_TAB_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CREATE_VERT_GROUP) == 0)
	{
		pPopup->DeleteMenu(ID_MDI_NEW_VERT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_NEXT) == 0)
	{
		pPopup->DeleteMenu(ID_MDI_MOVE_TO_NEXT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_PREV) == 0)
	{
		pPopup->DeleteMenu(ID_MDI_MOVE_TO_PREV_GROUP, MF_BYCOMMAND);
	}

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->SetAutoDestroy(FALSE);

	CWnd* pMenuOwner = GetActiveTearOffFrame() == NULL ? this : GetActiveTearOffFrame();
	pPopupMenu->Create(pMenuOwner, point.x, point.y, pPopup->GetSafeHmenu ());

	return TRUE;
}

void CMainFrame::OnMdiMoveToNextGroup()
{
	MDITabMoveToNextGroup();
}

void CMainFrame::OnMdiMoveToPrevGroup()
{
	MDITabMoveToNextGroup(FALSE);
}

void CMainFrame::OnMdiNewHorzTabGroup()
{
	MDITabNewGroup(FALSE);
}

void CMainFrame::OnMdiNewVertGroup()
{
	MDITabNewGroup();
}

void CMainFrame::OnMdiCancel()
{
	// TODO: add your command handler code here

}

CBCGPMDIChildWnd* CMainFrame::CreateDocumentWindow(LPCTSTR lpcszDocName, CObject* /*pObj*/)
{
	if (lpcszDocName != NULL && lpcszDocName [0] != '\0')
	{
		CDocument* pDoc = AfxGetApp()->OpenDocumentFile(lpcszDocName);
		if (pDoc != NULL)
		{
			POSITION pos = pDoc->GetFirstViewPosition();

			if (pos != NULL)
			{
				CView* pView = pDoc->GetNextView(pos);
				if (pView == NULL)
				{
					return NULL;
				}

				return DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, pView->GetParent());
			}
		}
	}

	return NULL;
}

void CMainFrame::OnClose()
{
	SaveMDIState(theApp.GetRegSectionPath());
	CBCGPMDIFrameWnd::OnClose();
}




BOOL CMainFrame::CreateClient(LPCREATESTRUCT lpCreateStruct, CMenu* pWindowMenu)
{
	// TODO: Add your specialized code here and/or call the base class

	return CBCGPMDIFrameWnd::CreateClient(lpCreateStruct, pWindowMenu);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	if (!CBCGPMDIFrameWnd::OnCreateClient(lpcs, pContext))
	{
		return FALSE;
	}
//	m_wndMarkerSymbolizer.SetContext(pContext);
	if (!m_wndMarkerSymbolizer.Create(_T("Marker"), this,
		CRect(0, 0, 300, 300),
		TRUE, ID_MARKER_SYMBOLIZER,
		WS_CHILD |
		WS_VISIBLE |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return FALSE;
	}
	m_wndPolygonPatternSymbolizer.SetContext(pContext);
	if (!m_wndPolygonPatternSymbolizer.Create(_T("Polygon pattern"), this,
		CRect(0, 0, 300, 300),
		TRUE, ID_POLYGON_PATTERN_SYMBOLIZER,
		WS_CHILD |
		WS_VISIBLE |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return FALSE;
	}
	m_wndPolygonSymbolizer.SetContext(pContext);
	if (!m_wndPolygonSymbolizer.Create(_T("Polygon"), this,
		CRect(0, 0, 300, 300),
		TRUE, ID_POLYGON_SYMBOLIZER,
		WS_CHILD |
		WS_VISIBLE |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Polygon bar\n");
		return FALSE;      // fail to create
	}
	m_wndDataSourceCSV.SetContext(pContext);
	if (!m_wndDataSourceCSV.Create(_T("Datasource CSV"), this,
		CRect(0, 0, 300, 300),
		TRUE, IDD_FORMVIEW_DATASOURCE_CSV,
		WS_CHILD |
		WS_VISIBLE |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Polygon bar\n");
		return FALSE;      // fail to create
	}
	m_wndDataSourceGEOJSON.SetContext(pContext);
	if (!m_wndDataSourceGEOJSON.Create(_T("Datasource GEOJSON"), this,
		CRect(0, 0, 300, 300),
		TRUE, IDD_FORMVIEW_DATASOURCE_GEOJSON,
		WS_CHILD |
		WS_VISIBLE |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Polygon bar\n");
		return FALSE;      // fail to create
	}
	m_wndDataSourceGDAL.SetContext(pContext);
	if (!m_wndDataSourceGDAL.Create(_T("Datasource GDAL"), this,
		CRect(0, 0, 300, 300),
		TRUE, IDD_FORMVIEW_DATASOURCE_GDAL,
		WS_CHILD |
		WS_VISIBLE |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Polygon bar\n");
		return FALSE;      // fail to create
	}
	m_wndDataSourceOCCI.SetContext(pContext);
	if (!m_wndDataSourceOCCI.Create(_T("Datasource OCCI"), this,
		CRect(0, 0, 300, 300),
		TRUE, IDD_FORMVIEW_DATASOURCE_OCCI,
		WS_CHILD |
		WS_VISIBLE |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Polygon bar\n");
		return FALSE;      // fail to create
	}
	return TRUE;
}




//BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
//{
//	// TODO: Add your specialized code here and/or call the base class
//	// enable customization button for all user toolbars
//	if (!CBCGPMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
//	{
//		return FALSE;
//	}
//	BOOL bNameValid;
//	CString strCustomize;
//	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
//	ASSERT(bNameValid);
//
//	for (int i = 0; i < iMaxUserToolbars; i++)
//	{
//		CBCGPToolBar* pUserToolbar = GetUserBarByIndex(i);
//		if (pUserToolbar != nullptr)
//		{
//			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//		}
//	}
//	return CBCGPMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
//}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CBCGPMDIFrameWnd::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
	// TODO: Add your message handler code here
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CBCGPMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}
