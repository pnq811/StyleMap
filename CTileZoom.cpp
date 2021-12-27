#include "stdafx.h"
#include "CTileZoom.h"
#include "pch.h"
#include "UserAction.h"
#include "CTileZoom.h"

CTileZoomManager::CTileZoomManager()
{
	//m_pUserAction = new CUserAction();
}
CTileZoomManager::CTileZoomManager(int viewWidth, int viewHeight)
{
	TileSize = 256;
	MaxLevel = 19;
	MinLevel = 0;
	ViewWidth = viewWidth;
	ViewHeight = viewHeight;
	ZoomLocation = TRUE;
	m_pUserAction = new CUserAction();
}

CTileZoomManager::CTileZoomManager(int viewWidth, int viewHeight, UINT tileSize)
{
	TileSize = tileSize;
	MaxLevel = 19;
	MinLevel = 0;
	ViewWidth = viewWidth;
	ViewHeight = viewHeight;
	ZoomLocation = TRUE;
	m_pUserAction = new CUserAction();

}

void CTileZoomManager::ZoomAll(CRect client)
{
	double lechPixel;
	View.LeftTile = View.TopTile = 0;
	lechPixel = (pow(2.0, 1) * 256) / 2;
	View.Left = client.right / 2 - lechPixel;
	View.Top = client.bottom / 2 - lechPixel;
	View.LevelOfDetail = 1;
}
void CTileZoomManager::Pan(int pxFromX, int pxFromY, int pxToX, int pxToY)
{
	double lechX, lechY;					// keo thay doi
	lechX = pxToX - pxFromX;
	lechY = pxToY - pxFromY;

	View.Left += lechX;
	View.Top += lechY;

	while (View.Left > 0 && View.LeftTile > 0)
	{
		View.Left -= 256;
		View.LeftTile--;
	}
	while (View.Top > 0 && View.TopTile > 0)
	{
		View.Top -= 256;
		View.TopTile--;
	}
}
void CTileZoomManager::ZoomIn(int pX, int pY)
{
	double pixelX, pixelY, nX, nY;				// toa do pixel
	double lechX, lechY;							 // chenh lech pixel
	int tileX, tileY, tileX2, tileY2;	// tile
	int ltX, ltY;

	if (View.LevelOfDetail == 19)
	{
		return;
	}

	//----------------------------------------------chenh lech pixel cu
	lechX = pX - View.Left;
	lechY = pY - View.Top;
	//----------------------------------------------------------------------------------
	pixelX = View.LeftTile * 256 + lechX;											// pixel cu 
	pixelY = View.TopTile * 256 + lechY;
	TileSystem.PixelXYToTileXY(pixelX, pixelY, tileX, tileY);					// tile cu 

	//----------------------------------------------------------------------------------
	nX = pixelX * 2;												    // pixel moi 
	nY = pixelY * 2;

	ltX = tileX - View.LeftTile;
	ltY = tileY - View.TopTile;

	TileSystem.PixelXYToTileXY(nX, nY, tileX2, tileY2);					// tile moi
	View.LeftTile = tileX2 - ltX;					// tile goc moi
	View.TopTile = tileY2 - ltY;

	lechX = nX - View.LeftTile * 256;				// lech pixel moi
	lechY = nY - View.TopTile * 256;

	View.Left = pX - lechX;					//  gocX Y moi 
	View.Top = pY - lechY;

	if (View.LevelOfDetail < 3)
	{
		View.Left = pX - nX;
		View.Top = pY - nY;
		View.LeftTile = View.TopTile = 0;
	}

	while (View.TopTile > 0 && View.Top > 0)
	{
		View.Top -= 256;
		View.TopTile--;
	}
	while (View.LeftTile > 0 && View.Left > 0)
	{
		View.Left -= 256;
		View.LeftTile--;
	}

	View.LevelOfDetail++;
}

void CTileZoomManager::ZoomOut(int pX, int pY)
{
	double pixelX, pixelY, nX, nY, oX, oY;				// toa do pixel
	double lechX, lechY;							 // chenh lech pixel
	int tileX, tileY, tileX2, tileY2;	// tile
	int ltX, ltY;

	if (View.LevelOfDetail == 1)
	{
		return;
	}

	//----------------------------------------------chenh lech pixel cu
	lechX = pX - View.Left;
	lechY = pY - View.Top;
	//----------------------------------------------------------------------------------
	pixelX = View.LeftTile * 256 + lechX;											// pixel cu 
	pixelY = View.TopTile * 256 + lechY;

	//----------------------------------------------------------------------------------

	View.LeftTile = int(View.LeftTile / 2);
	View.TopTile = int(View.TopTile / 2);

	lechX = int(pixelX / 2 - View.LeftTile * 256);
	lechY = int(pixelY / 2 - View.TopTile * 256);

	View.Left = pX - (lechX);					//  gocX Y moi 
	View.Top = pY - (lechY);

	while (View.TopTile > 0 && View.Top > 0)
	{
		View.Top -= 256;
		View.TopTile--;
	}
	while (View.LeftTile > 0 && View.Left > 0)
	{
		View.Left -= 256;
		View.LeftTile--;
	}
	View.LevelOfDetail--;
}
void CTileZoomManager::ZoomRealTime(CPoint up, CPoint down, CRect client)
{
	int Px, Py, kTile;
	if (up.x == down.x || up.y == down.y) return;

	Px = abs(up.x - down.x) / 2 + down.x;
	Py = abs(up.y - down.y) / 2 + down.y;

	kTile = int(log2(client.bottom / (up.y - down.y))) + 1;
	if (up.y > down.y)
	{
		for (int i = 0; i < kTile - 1; i++)
			ZoomIn(Px, Py);
		return;
	}
	else
	{
		for (int i = 0; i < kTile - 1; i++)
			ZoomOut(Px, Py);
		return;
	}

}

void CTileZoomManager::SetTop(int nZoom, int type, CRect client, CPoint up, CPoint down, CPoint Mouse)
{
	if (type == -2) return;
	if (type == 0 || nZoom == 32772)
	{
		ZoomAll(client);
		return;
	}
	if (type == 1 && nZoom == 32777) Pan(down.x, down.y, up.x, up.y);
	if (type == 2 && nZoom == 32778) ZoomIn(Mouse.x, Mouse.y);
	if (type == 3 && nZoom == 32779) ZoomOut(Mouse.x, Mouse.y);
	if (type == 4 && nZoom == 32780) Pan(Mouse.x, Mouse.y, int(client.right / 2), int(client.bottom / 2));
	if (type == 5 && nZoom == 32775) ZoomRealTime(up, down, client);
	if (View.Left <= -256)
	{
		int k = -1 * int(View.Left / 256);
		View.Left += 256 * k;
		View.LeftTile += k;
	}
	if (View.Top <= -256)
	{
		int k = -1 * int(View.Top / 256);
		View.Top += 256 * k;
		View.TopTile += k;
	}
}

void CTileZoomManager::MoveTo(double lat, double lon, int LevelOfDetail)
{
	/*int pixelX, pixelY;
	int nSemiW this->ViewWidth >> 1;
	int nSemiH this->ViewHeight >> 1;

	TileSystem.LatLongToPixelXY(lat, lon, LevelOfDetail, pixelX, pixelY);

	WindowMinX = pixelX - nSemiW;
	WindowMaxX = pixelX + nSemiW;
	WindowMinY = pixelY - nSemiH;
	WindowMaxY = pixelY + nSemiH;

	it nMapSize (int)TileSystem.MapSize(LevelOfDetail);

	View.Left  = (nMapSize + (WindowMinX % nMapSize))% nMapSize;
	View.Top   = max(0, WindowMinY);
	View.Top   = min(View.Top, nMapSize - 1);
	TileSystem.PixelXYToTileXY(View.Left, View.Top, View.LeftTile, View.TopTile);

	pixelX = (nMapsize + (WindowMax % nMapSize))% nMapSize;
	pixelY = max(0, WindowMaxY);
	pixelY = min(pixelY, nMapSize - 1);
	TileSystem.PixelXYToTileXY(pixelX, pixelY, View.RightTile, View.BottomTile);

	View.Left %= this->TileSize;
	View.Top %= this->TileSize;

	this->View.LevelOfDetail LevelOfDetail; */
}
void CTileZoomManager::Resize(UINT w, UINT h)
{
	//if (m_pUserAction != NULL) 
	//{
	//	CWnd* pParent = m_pUserAction->SetParent(); 
	//	if (pParent != NULL) 
	//	{
	//		double dbLatitude, dbLongitude; 
	//		int nCenterX = (this->WindowMaxX + this->WindowMinX) >> 1; 
	//		int nCenterY = (this->WindowMaxY + this->WindowMinY) >> 1; 
	//		this->TileSystem.PixelXYToLatLong(nCenterX, nCenterY, this->View.LevelOfDetail, dbLatitude, dbLongitude); 
	//		
	//		CRect rcClient; 
	//		pParent->GetClientRect(&rcClient); 
	//		this->ViewWidth = w;//rcClient.Width; 
	//		this->ViewHeight = h;//rcClient.Height; 
	//		
	//		this->MoveTo(dbLatitude, dbLongitude, this->View.LevelOfDetail); 
	//	}
	//}
}