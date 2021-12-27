#include "stdafx.h"
#include <iostream>
#include "pch.h"
#include "CTree_File.h"
#include "SymbolizerProjectDoc.h"
#include "SymbolizerProjectView.h"
#include "SymbolizerProject.h"

CTree_File::CTree_File() noexcept
{

}
CTree_File::~CTree_File()
{

}

BEGIN_MESSAGE_MAP(CTree_File, CTreeCtrl)
    ON_NOTIFY_REFLECT(NM_CLICK, &CTree_File::OnNMClick)
    ON_NOTIFY_REFLECT(NM_RCLICK, &CTree_File::OnNMRClick)
END_MESSAGE_MAP()

void CTree_File::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    CFrameWnd* pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
    CSymbolizerProjectView* pView = (CSymbolizerProjectView*)pFrame->GetActiveView();
    CSymbolizerProjectDoc* pDoc = pView->GetDocument();
    TVHITTESTINFO ht = { 0 };
    DWORD dwpos = GetMessagePos();
    ht.pt.x = GET_X_LPARAM(dwpos);
    ht.pt.y = GET_Y_LPARAM(dwpos);
    ::MapWindowPoints(HWND_DESKTOP, pNMHDR->hwndFrom, &ht.pt, 1);
    TreeView_HitTest(pNMHDR->hwndFrom, &ht);
    if (TVHT_ONITEM & ht.flags)
    {
        if (pDoc->RenderAvailable())
        {

            BOOL check = GetCheck(ht.hItem);
            CSymbolizerProjectDoc::ViewP* data = (CSymbolizerProjectDoc::ViewP*)(GetItemData(ht.hItem));
            HTREEITEM f = GetChildItem(ht.hItem);
            if (typeview == TypeView::FILEVIEW)
            {
                if (f != NULL && data != NULL)
                    return;
                pDoc->JumpToPath(data);
                pView->Redraw();
            }
            if (typeview == TypeView::CLASSVIEW)
            {
                int _data = GetItemData(ht.hItem);
                UpdateUI(_data);
                if (f == NULL || _data == -1)
                    return;
                int index = _data;
                pDoc->SelectFloor(index);
                pView->Redraw();
            }
        }

    }
    *pResult = 0;
}

void CTree_File::OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    UINT nFlags;
    TVHITTESTINFO ht = { 0 };
    DWORD dwpos = GetMessagePos();
    ht.pt.x = GET_X_LPARAM(dwpos);
    ht.pt.y = GET_Y_LPARAM(dwpos);
    CPoint p(ht.pt.x, ht.pt.y);
    ::MapWindowPoints(HWND_DESKTOP, pNMHDR->hwndFrom, &ht.pt, 1);
    TreeView_HitTest(pNMHDR->hwndFrom, &ht);
    CFrameWnd* pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
    CSymbolizerProjectView* pView = (CSymbolizerProjectView*)pFrame->GetActiveView();
    CSymbolizerProjectDoc* pDoc = pView->GetDocument();
    if (TVHT_ONITEM && ht.flags)
    {
        if (typeview == TypeView::CLASSVIEW)
        {
            HTREEITEM f = GetChildItem(ht.hItem);
            int data = DWORD(GetItemData(ht.hItem));
            if (f != NULL)
            {
                OnContextMenu(this, p);
            }
            if (f == NULL)
            {
                pDoc->m_idrclick = data;
                OnContextMenu2(this, p);
            }
        }
    }
    *pResult = 0;
}

HTREEITEM CTree_File::GetCheckAllItem()
{
    HTREEITEM f = GetChildItem(GetFirstVisibleItem());
    int count = 0;
    while (f != NULL)
    {
        int idx = DWORD(GetItemData(f));
        ++count;
        f = GetNextItem(f, TVGN_NEXT);
    }
    return f;
}

void CTree_File::UpdateUI(int index)
{
    if (typeview == TypeView::CLASSVIEW)
    {
        HTREEITEM f = GetChildItem(GetFirstVisibleItem());
        while (f != NULL)
        {
            int _index = (DWORD_PTR)(GetItemData(f));
            if (_index == index)
            {
                SetItemState(f, UINT(TVIS_BOLD), UINT(TVIS_BOLD));
            }
            else
            {
                SetItemState(f, UINT(~TVIS_BOLD), UINT(TVIS_BOLD));
            }
            f = GetNextItem(f, TVGN_NEXT);
        }
    }
}

void CTree_File::OnContextMenu(CWnd* pWnd, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU1, point.x, point.y, (CWnd*)this, FALSE);
#endif
}

void CTree_File::OnContextMenu2(CWnd* pWnd, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU2, point.x, point.y, (CWnd*)this, FALSE);
#endif
}