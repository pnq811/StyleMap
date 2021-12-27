#pragma once


// CPaneDataSourceGEOJSON
#include "FormViewDataSourceGEOJSON.h"
class CPaneDataSourceGEOJSON : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CPaneDataSourceGEOJSON)

public:
	CPaneDataSourceGEOJSON();
	virtual ~CPaneDataSourceGEOJSON();
	CFormViewDataSourceGEOJSON* m_pFormViewGEOJSON;
	CCreateContext* m_pContext;
	void SetContext(CCreateContext* pContext)
	{
		m_pContext = pContext;
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	std::string SettingsXml();
	void SettingsXml(std::string xml_string);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
};


