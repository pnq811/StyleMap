#pragma once


// CPolygonPatternSymbolizer
#include "stdafx.h"
#include "FormViewPolygonPatternSymbolizer.h"
class CPolygonPatternSymbolizer : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CPolygonPatternSymbolizer)

public:
	CPolygonPatternSymbolizer();
	virtual ~CPolygonPatternSymbolizer();
	void SetContext(CCreateContext* pContext)
	{
		m_pContext = pContext;
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	void SettingsXml(std::string xmlString);
	std::string SettingsXml();
public:
	CFont								m_Font;

	CFormViewPolygonPatternSymbolizer*	m_pFormViewPolygonPattern;
	CCreateContext*						m_pContext;
	int									m_nTextHeight;
};


