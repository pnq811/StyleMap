#include "stdafx.h"
#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
#include "ClassView.h"
#include "Resource.h"
#include "SymbolizerProject.h"
#include "StringProcess.h"
#include "SymbolizerProjectView.h"

class CClassViewMenuButton : public CBCGPToolbarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = nullptr) noexcept : CBCGPToolbarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CBCGPToolBar::GetImages();

		CBCGPDrawState ds;
		pImages->PrepareDrawImage(ds);

		CBCGPToolbarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CBCGPToolbarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClassView::CClassView() noexcept
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CClassView::~CClassView()
{
}

BEGIN_MESSAGE_MAP(CClassView, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView message handlers

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	m_wndClassView.typeview = CTree_File::TypeView::CLASSVIEW;
	// Create views:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Failed to create Class View\n");
		return -1;      // fail to create
	}

	// Load images:
	m_wndToolBar.Create(this, dwDefaultToolbarStyle, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();
	//m_wndToolBar.;
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CClassViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CClassViewMenuButton* pButton = DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != nullptr)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(BCGPGetCmdMgr()->GetCmdImage(m_nCurrSort, FALSE));
		pButton->SetMessageWnd(this);
	}

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillClassView();

	return 0;
}

void CClassView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CClassView::FillClassView()
{
	m_wndClassView.DeleteAllItems();
	HTREEITEM hItem[3];
	//for ( i = 0; i < length; i++)
	//{

	//}
}

void CClassView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CBCGPDockingControlBar::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != nullptr)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CBCGPMDIFrameWnd)))
	{
		CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CBCGPMDIFrameWnd*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}
void CClassView::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassView.SetWindowPos(nullptr, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}
BOOL CClassView::PreTranslateMessage(MSG* pMsg)
{
	return CBCGPDockingControlBar::PreTranslateMessage(pMsg);
}
void CClassView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CClassViewMenuButton* pButton = DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != nullptr)
	{
		pButton->SetImage(BCGPGetCmdMgr()->GetCmdImage(id, FALSE));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}
void CClassView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}
void CClassView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("Add member function..."));
}
void CClassView::OnClassAddMemberVariable()
{
	// TODO: Add your command handler code here
}
void CClassView::OnClassDefinition()
{
	// TODO: Add your command handler code here
}
void CClassView::OnClassProperties()
{
	// TODO: Add your command handler code here
}
void CClassView::OnNewFolder()
{
	AfxMessageBox(_T("New Folder..."));
}
void CClassView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndClassView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}
void CClassView::OnSetFocus(CWnd* pOldWnd)
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);

	m_wndClassView.SetFocus();
}
void CClassView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ClassViewImages.Create(24, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndClassView.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* Locked */);
}
void CClassView::FillData(int floor)
{
	CFrameWnd* pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	CSymbolizerProjectView* pView = (CSymbolizerProjectView*)pFrame->GetActiveView();
	CSymbolizerProjectDoc* pDoc = pView->GetDocument();
	m_wndClassView.DeleteAllItems();

	HTREEITEM hRoot = m_wndClassView.InsertItem(_T("Building"), 0, 0);
	m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	m_wndClassView.SetItemData(hRoot, -1);
	int k = 0;
	for (int i = 1; i <= floor; ++i)
	{
		CString cs = _T("Floor ") + StringProcess::int2cstring(i);
		m_wndClassView.GetFont();
		HTREEITEM hClass = m_wndClassView.InsertItem(cs, 1, 1, hRoot);
		HTREEITEM WC = m_wndClassView.InsertItem(_T("WC"), 12, 12, hClass);
		m_wndClassView.SetItemData(WC, -1);
		CString cs1;
		for (int _id : pDoc->m_Building.POI)
		{
			Node* _node = pDoc->m_Building.m_pNode->at(_id - 1);
			int fall = false;
			if (_node->floor == i)
			{
				switch (_node->type)
				{
				case Node::Type::BAR:
					cs1 = _T("Bar ");
					fall = true;
					k = 4; 
					break;
				case Node::Type::RESTAURANT:
					cs1 = _T("Restaurant ");
					fall = true;
					k = 7; 
					break;
				case Node::Type::CINEMA:
					cs1 = _T("Cinema ");
					k = 9; 
					fall = true;
					break;
				case Node::Type::ICE_CREAM:
					cs1 = _T("Ice cream ");
					k = 6; 
					fall = true;
					break;
				case Node::Type::CAFE:
					cs1 = _T("Coffe ");
					fall = true;
					k = 5; 
					break;
				case Node::Type::CASINO:
					cs1 = _T("Casino ");
					k = 10; 
					fall = true;
					break;
				case Node::Type::WC_FEMALE:
					cs1 = _T("Woman ");
					k = 3;
					fall = true;
					break;
				case Node::Type::WC_MALE:
					cs1 = _T("Man ");
					k = 2;
					fall = true;
					break;
				case Node::Type::FAST_FOOD:
					cs1 = _T("Fast food");
					fall = true;
					k = 8; 
					break;
				case Node::Type::LIBRARY:
					cs1 = _T("Library");
					k = 11;
					fall = true;
					break;
				default:
					break;
				}
				if (fall)
				{
					if (k != 2 && k != 3)
					{
						HTREEITEM hC1 = m_wndClassView.InsertItem(cs1, k, k, hClass);
						m_wndClassView.SetItemData(hC1, _node->id);
					}
					else
					{
						HTREEITEM hC1 = m_wndClassView.InsertItem(cs1, k, k, WC);
						m_wndClassView.SetItemData(hC1, _node->id);
					}
				}

			}
		}

		m_wndClassView.SetItemData(hClass, i);
	}
}




