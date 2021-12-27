// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "WorkSpaceBar.h"
#include "WorkSpaceBar2.h"
#include "OutputBar.h"
#include "PropertiesViewBar.h"
#include "ToolBox.h"
#include "PaneDataSourceCSV.h"
#include "PaneDataSourceGDAL.h"
#include "PaneDataSourceGEOJSON.h"
#include "PaneDataSourceOCCI.h"
#include "PolygonPatternSymbolizer.h"
#include "PolygonSymbolizer.h"
#include "MarkerSymbolizer.h"

#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
// Symbolizer
#include "WorkSpaceBar_Line.h"
#include "WorkSpaceBar_Linepattern.h"
#include "WorkSpaceBar_Raster.h"
#include "WorkSpaceBar_Point.h"
#include "WorkSpaceBar_Dot.h"

// Datasource
#include "WorkSpaceBar_Ogr.h"
#include "WorkSpaceBar_Osm.h"
#include "WorkSpaceBar_Postgis.h"
#include "WorkSpaceBar_Python.h"
class CMainFrame : public CBCGPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:  // control bar embedded members
	CBCGPStatusBar				m_wndStatusBar;
	CBCGPMenuBar				m_wndMenuBar;
	CBCGPToolBar				m_wndToolBar;
	CWorkSpaceBar				m_wndWorkSpace;
	CWorkSpaceBar2				m_wndWorkSpace2;
	COutputBar					m_wndOutputBar;
	CBCGPPropBar				m_wndPropGrid;
	CToolBoxBarEx				m_wndToolBox;
	
public:
	CPaneDataSourceCSV			m_wndDataSourceCSV;
	CPaneDataSourceGDAL			m_wndDataSourceGDAL;
	CPaneDataSourceGEOJSON		m_wndDataSourceGEOJSON;
	CPaneDataSourceOCCI			m_wndDataSourceOCCI;
	CPolygonSymbolizer			m_wndPolygonSymbolizer;
	CPolygonPatternSymbolizer	m_wndPolygonPatternSymbolizer;
	CMarkerSymbolizer			m_wndMarkerSymbolizer;
	// Symbolizer
	CWorkSpaceBar_Line					m_wndWorkSpace_Line;
	CWorkSpaceBar_Linepattern			m_wndWorkSpace_Linepattern;
	CWorkSpaceBar_Raster				m_wndWorkSpace_Raster;
	CWorkSpaceBar_Point					m_wndWorkSpace_Point;
	CWorkSpaceBar_Dot					m_wndWorkSpace_Dot;

	// Datasources
	CWorkSpaceBar_Ogr					m_wndWorkSpace_Ogr;
	CWorkSpaceBar_Osm					m_wndWorkSpace_Osm;
	CWorkSpaceBar_Postgis				m_wndWorkSpace_Postgis;
	CWorkSpaceBar_Python				m_wndWorkSpace_Python;
	CClassView        m_wndClassView;
	CFileView         m_wndFileView;
	COutputWnd        m_wndOutput;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg void OnToolBox();
	afx_msg void OnWindowManager();
	
	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	afx_msg void OnMdiCancel();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnViewCustomize();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	virtual BOOL OnShowMDITabContextMenu(CPoint point, DWORD dwAllowedItems, BOOL bDrop);
	virtual CBCGPMDIChildWnd* CreateDocumentWindow(LPCTSTR lpcszDocName, CObject* /*pObj*/);
public:
	void EnkillFocus_Datasources_Postgis();
	virtual BOOL CreateClient(LPCREATESTRUCT lpCreateStruct, CMenu* pWindowMenu);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	// afx_msg void OnViewPolygon();
	// virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
};
