#pragma once


// CPolygonSymbolizer
#include "stdafx.h"
#include <iostream>
const UINT idEdit_Default = 0;
const UINT idEdit_Fill = 1;
const UINT idEdit_FillOpacity = 2;
const UINT idEdit_Gamma = 3;
const UINT idEdit_GammaMethod = 4;
const UINT idEdit_Clip = 5;
const UINT idEdit_Simplify = 6;
const UINT idEdit_SimplifyAlgorithm = 7;
const UINT idEdit_Smooth = 8;
const UINT idEdit_GeometryTransform = 9;
const UINT idEdit_CompOp = 10;


const std::string m_gamma_method[5] = {};

#include "FormViewPolygonSymbolizer.h"

class CPolygonSymbolizer : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CPolygonSymbolizer)
public:
	/*CBCGPStatic		m_wndStatic;*/
	
	
	
	CFont			m_Font;

	CFormViewPolygonSymbolizer* m_pFormViewPolygon;
	CCreateContext* m_pContext;


	int				m_nTextHeight;
public:
	CPolygonSymbolizer();
	virtual ~CPolygonSymbolizer();
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

	std::string SettingsXml();
	void SettingXml(std::string xmlString);
};


