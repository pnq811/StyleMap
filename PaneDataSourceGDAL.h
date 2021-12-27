#pragma once


// CPaneDataSourceGDAL
#include "stdafx.h"
#include "FormViewDataSourceGDAL.h"
class CPaneDataSourceGDAL : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CPaneDataSourceGDAL)

public:
	CPaneDataSourceGDAL();
	virtual ~CPaneDataSourceGDAL();
	CFormViewDataSourceGDAL* m_pFormViewGDAL;
	CCreateContext* m_pContext;
	void SetContext(CCreateContext* pContext)
	{
		m_pContext = pContext;
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	std::string SettingsXml();
	void SettingsXml(std::string xml_string);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


