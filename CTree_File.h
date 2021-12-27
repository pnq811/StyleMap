#pragma once

#ifndef CTREEFILE_H

#define  CTREEFILE_H

#include <afxcmn.h>
class CTree_File :
    public CTreeCtrl
{
public:
    typedef enum class TypeView {
        FILEVIEW,
        CLASSVIEW
    };
public:
    TypeView typeview;
public:
    CTree_File() noexcept;
    virtual ~CTree_File();
    HTREEITEM GetCheckAllItem();
    void UpdateUI(int index);
    void OnContextMenu(CWnd* pWnd, CPoint point);
    void CTree_File::OnContextMenu2(CWnd* pWnd, CPoint point); 
protected:
    afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};

#endif //CTREEFILE_H