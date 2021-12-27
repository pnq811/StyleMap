#pragma once


// CPaneDataSourceOCCI
#include "FormViewDataSourceOCCI.h"
class CPaneDataSourceOCCI : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CPaneDataSourceOCCI)

public:
	CPaneDataSourceOCCI();
	virtual ~CPaneDataSourceOCCI();
	CFormViewDataSourceOCCI* m_pFormViewOCCI;
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


