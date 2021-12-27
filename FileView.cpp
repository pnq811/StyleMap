#include "stdafx.h"
#include "pch.h"
#include "framework.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "SymbolizerProject.h"
#include "StringProcess.h"
#include "SymbolizerProjectView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView() noexcept
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	m_wndFileView.typeview = CTree_File::TypeView::FILEVIEW;
	// Create view:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("Failed to create file view\n");
		return -1;      // fail to create
	}

	// Load view images:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillFileView();
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::FillFileView()
{
	m_wndFileView.DeleteAllItems();
	HTREEITEM hFloor1 = m_wndFileView.InsertItem(_T("Not Found "),9,9);
	m_wndFileView.SetItemData(hFloor1, (DWORD_PTR)(new CSymbolizerProjectDoc::ViewP(-1, 0, CSymbolizerProjectDoc::ViewP::Direction::GOSTRAIGHT, 0, 0)));
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndFileView;
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
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(nullptr, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("Properties...."));

}

void CFileView::OnFileOpen()
{
	// TODO: Add your command handler code here
}

void CFileView::OnFileOpenWith()
{
	// TODO: Add your command handler code here
}

void CFileView::OnDummyCompile()
{
	// TODO: Add your command handler code here
}

void CFileView::OnEditCut()
{
	// TODO: Add your command handler code here
}

void CFileView::OnEditCopy()
{
	// TODO: Add your command handler code here
}

void CFileView::OnEditClear()
{
	// TODO: Add your command handler code here
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

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

	m_FileViewImages.Create(24, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

void CFileView::SetData(Edge::Type type)
{
	CFrameWnd* pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	CSymbolizerProjectView* pView = (CSymbolizerProjectView*)pFrame->GetActiveView();
	CSymbolizerProjectDoc* pDoc = pView->GetDocument();
	std::vector<CSymbolizerProjectDoc::ViewP*> _path;
	_path = pDoc->PathSelect;
	int numPath = _path.size();
	m_wndFileView.DeleteAllItems();
	int floor = _path[0]->floor;
	HTREEITEM hFloor1 = m_wndFileView.InsertItem(_T("Floor ") + StringProcess::int2cstring(floor), 2, 2);
	m_wndFileView.SetItemData(hFloor1, (DWORD_PTR)(new CSymbolizerProjectDoc::ViewP(-1, 0, CSymbolizerProjectDoc::ViewP::Direction::GOSTRAIGHT, 0, 0)));
	HTREEITEM hStartP = m_wndFileView.InsertItem(_T("Starting position"), 8, 8, hFloor1);
	m_wndFileView.SetItemData(hStartP, (DWORD_PTR)_path[0]);
	int k;
	for (int i = 1; i < numPath - 1; i++)
	{
		CString value;
		int numImg = 0;
		if (_path[i]->floor != floor)
		{
			k = i;
			break;
		}
		switch (_path[i]->direction)
		{
		case CSymbolizerProjectDoc::ViewP::Direction::GOSTRAIGHT:
		{
			value = _T("Continue straight ") + value;
			numImg = 6;
			break;
		}
		case CSymbolizerProjectDoc::ViewP::Direction::TURNLEFT:
		{
			value = _T("Turn left and continue ") + value;
			numImg = 0;
			break;
		}
		case CSymbolizerProjectDoc::ViewP::Direction::TURNRIGHT:
		{
			value = _T("Turn right and continue ") + value;
			numImg = 1;
			break;
		}
		default:
			break;
		}
		HTREEITEM hSrc = m_wndFileView.InsertItem(value, numImg, numImg, hFloor1);
		m_wndFileView.SetItemData(hSrc, (DWORD_PTR)_path[i]);
	}

	if (type != Edge::Type::EDGE)
	{
		if (type == Edge::Type::EVELATOR)
		{
			CString value = _T("Take elevator to level ") + StringProcess::int2cstring(_path[numPath - 1]->floor);
			HTREEITEM hRoot = m_wndFileView.InsertItem(value, 5, 5);
			m_wndFileView.SetItemData(hRoot, (DWORD_PTR)(new CSymbolizerProjectDoc::ViewP(-1, 0, CSymbolizerProjectDoc::ViewP::Direction::GOSTRAIGHT, 0, 0)));
		}
		else
		{
			CString value = _T("Take stairs to level ") + StringProcess::int2cstring(_path[numPath - 1]->floor);
			HTREEITEM hRoot = m_wndFileView.InsertItem(value, 3, 3);
			m_wndFileView.SetItemData(hRoot, (DWORD_PTR)(new CSymbolizerProjectDoc::ViewP(-1, 0, CSymbolizerProjectDoc::ViewP::Direction::GOSTRAIGHT, 0, 0)));
		}
	}

	if (_path[0]->floor != _path[numPath - 1]->floor)
	{
		HTREEITEM hFloor2 = m_wndFileView.InsertItem(_T("Floor ") + StringProcess::int2cstring(_path[numPath - 1]->floor), 2, 2);
		m_wndFileView.SetItemData(hFloor2, (DWORD_PTR)(new CSymbolizerProjectDoc::ViewP(-1, 0, CSymbolizerProjectDoc::ViewP::Direction::GOSTRAIGHT, 0, 0)));
		for (int i = k; i < numPath - 1; i++)
		{
			if (_path[i]->floor == _path[numPath - 1]->floor)
			{
				k = i;
				break;
			}
		}
		_path[k - 1]->floor = _path[numPath - 1]->floor;
		HTREEITEM hGo = m_wndFileView.InsertItem(_T("Continue straight "), 6, 6, hFloor2);
		m_wndFileView.SetItemData(hGo, (DWORD_PTR)(_path[k - 1]));
		for (int i = k; i < numPath - 1; i++)
		{
			CString value;
			int numImg = 0;
			if (_path[i]->floor != _path[numPath - 1]->floor)
			{
				k = i;
				break;
			}

			switch (_path[i]->direction)
			{
			case CSymbolizerProjectDoc::ViewP::Direction::GOSTRAIGHT:
			{
				value = _T("Continue straight ") + value;
				numImg = 6;
				break;
			}
			case CSymbolizerProjectDoc::ViewP::Direction::TURNLEFT:
			{
				value = _T("Turn left and continue ") + value;
				numImg = 0;
				break;
			}
			case CSymbolizerProjectDoc::ViewP::Direction::TURNRIGHT:
			{
				value = _T("Turn right and continue ") + value;
				numImg = 1;
				break;
			}
			default:
				break;
			}
			HTREEITEM hSrc = m_wndFileView.InsertItem(value, numImg, numImg, hFloor2);
			m_wndFileView.SetItemData(hSrc, (DWORD_PTR)_path[i]);
		}
		CString value = _T("Target");
		HTREEITEM hTargetP = m_wndFileView.InsertItem(value, 7, 7, hFloor2);
		m_wndFileView.SetItemData(hTargetP, (DWORD_PTR)_path[numPath - 1]);
	}
	else
	{
		CString value = _T("Target");
		HTREEITEM hTargetP = m_wndFileView.InsertItem(value, 7, 7, hFloor1);
		m_wndFileView.SetItemData(hTargetP, (DWORD_PTR)_path[numPath - 1]);
	}

}
