#pragma once


// CPaneDataSourceCSV
#include "FormViewDataSourceCSV.h"
class CPaneDataSourceCSV : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CPaneDataSourceCSV)

public:
	CPaneDataSourceCSV();
	virtual ~CPaneDataSourceCSV();


	CFormViewDataSourceCSV* m_pFormViewCSV;
	CCreateContext* m_pContext;
	void SetContext(CCreateContext* pContext)
	{
		m_pContext = pContext;
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	std::string SettingsXml();
	void SettingsXml(std::string xml_string);
	void OnPaint();
};


