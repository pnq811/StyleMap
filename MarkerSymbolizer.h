#pragma once


// CMarkerSymbolizer
#include "FormViewMarkerSymbolizer.h"


class CMarkerSymbolizer : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CMarkerSymbolizer)

public:
	CMarkerSymbolizer();
	virtual ~CMarkerSymbolizer();
	void SetContext(CCreateContext* pContext)
	{
		m_pContext = pContext;
	}
	void SettingsXml(std::string xmlString);
	std::string SettingsXml();
public:
	CFormViewMarkerSymbolizer*	m_pFormViewMarker;


	CCreateContext*				m_pContext;


	int							m_nTextHeight;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	
};


