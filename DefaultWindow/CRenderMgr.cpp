#include "pch.h"
#include "CRenderMgr.h"

void CRenderMgr::PlayerRender(HDC hDC, INFO _tInfo)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // 테두리
	HBRUSH hBrush = CreateSolidBrush(RGB(102, 255, 112));   //  채우기

	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	POINT PolygonPoint_Wing[5] = {
		{_tInfo.fX - _tInfo.fCX / 2, _tInfo.fY - _tInfo.fCY / 6},
		{_tInfo.fX + _tInfo.fCX / 2, _tInfo.fY - _tInfo.fCY / 6},
		{_tInfo.fX + _tInfo.fCX / 2 ,_tInfo.fY + _tInfo.fCY / 14},
		{_tInfo.fX,  _tInfo.fY + _tInfo.fCY / 6},
		{_tInfo.fX - _tInfo.fCX / 2, _tInfo.fY + _tInfo.fCY / 14}
	};
	POINT PolygonPoint_Tail[6] = {
		{_tInfo.fX, _tInfo.fY + _tInfo.fCY / 2 - _tInfo.fCY / 6 },
		{_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 7, _tInfo.fY + _tInfo.fCY / 2 - _tInfo.fCY / 12},
		{_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 7, _tInfo.fY + _tInfo.fCY / 2},
		{_tInfo.fX, _tInfo.fY + _tInfo.fCY / 2 - _tInfo.fCY / 30 },
		{_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 7 ,_tInfo.fY + _tInfo.fCY / 2},
		{_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 7, _tInfo.fY + _tInfo.fCY / 2 - _tInfo.fCY / 12}
	};
	POINT PolygonPoint_Body[4] = {
		{_tInfo.fX - _tInfo.fCX / 9, _tInfo.fY + _tInfo.fCY / 2},
		{_tInfo.fX + _tInfo.fCX / 9, _tInfo.fY + _tInfo.fCY / 2},
		{_tInfo.fX + _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2},
		{_tInfo.fX - _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2}
	};

	Polygon(hDC, PolygonPoint_Wing, 5);
	Polygon(hDC, PolygonPoint_Tail, 6);
	Polygon(hDC, PolygonPoint_Body, 4);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void CRenderMgr::NormalMonsterRender(HDC hDC, INFO _tInfo, float _index)
{

	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0,0,0)); // 테두리
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 149, 190));   //  채우기

	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	int index = (int)_index % 5;
	if (index == 0)
	{
		POINT PolygonPoint_Wing[5] = {
		   {_tInfo.fX - _tInfo.fCX / 2, _tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2, _tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2 ,_tInfo.fY - _tInfo.fCY / 14},
		   {_tInfo.fX,               _tInfo.fY - _tInfo.fCY / 6},
		   {_tInfo.fX - _tInfo.fCX / 2, _tInfo.fY - _tInfo.fCY / 14}
		};
		POINT PolygonPoint_Tail[6] = {
		   {_tInfo.fX,                            _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 6 },
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX,                            _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 30 },
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12}
		};
		POINT PolygonPoint_Body[4] = {
		   {_tInfo.fX - _tInfo.fCX / 7, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 7, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 8, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 8, _tInfo.fY - _tInfo.fCY / 2}
		};

		Polygon(hDC, PolygonPoint_Wing, 5);
		Polygon(hDC, PolygonPoint_Tail, 6);
		Polygon(hDC, PolygonPoint_Body, 4);
	}
	if (index == 1)
	{
		POINT PolygonPoint_Wing[5] = {
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 11, _tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 5, _tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 5 ,_tInfo.fY - _tInfo.fCY / 14},
		   {_tInfo.fX,              _tInfo.fY - _tInfo.fCY / 6},
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 11, _tInfo.fY - _tInfo.fCY / 14}
		};
		POINT PolygonPoint_Tail[6] = {
		   {_tInfo.fX,                   _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 6 },
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 4, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 4, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX,                   _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 30 },
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 6, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 6, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12}
		};
		POINT PolygonPoint_Body[4] = {
		   {_tInfo.fX - _tInfo.fCX / 7, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 7, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 8, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 8, _tInfo.fY - _tInfo.fCY / 2}
		};

		Polygon(hDC, PolygonPoint_Wing, 5);
		Polygon(hDC, PolygonPoint_Tail, 6);
		Polygon(hDC, PolygonPoint_Body, 4);
	}
	if (index == 2)
	{
		POINT PolygonPoint_Wing[5] = {
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 4, _tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 4,_tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 4,_tInfo.fY - _tInfo.fCY / 14},
		   {_tInfo.fX,                            _tInfo.fY - _tInfo.fCY / 6},
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 4, _tInfo.fY - _tInfo.fCY / 14}
		};
		POINT PolygonPoint_Tail[6] = {
		   {_tInfo.fX,                            _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 6 },
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 4, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 4, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX,                            _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 30 },
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 4, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 4, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12}
		};
		POINT PolygonPoint_Body[4] = {
		   {_tInfo.fX - _tInfo.fCX / 8, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 8, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2}
		};

		Polygon(hDC, PolygonPoint_Wing, 5);
		Polygon(hDC, PolygonPoint_Tail, 6);
		Polygon(hDC, PolygonPoint_Body, 4);
	}
	if (index == 3)
	{
		POINT PolygonPoint_Wing[5] = {
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 5, _tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 11, _tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 11,_tInfo.fY - _tInfo.fCY / 14},
		   {_tInfo.fX,               _tInfo.fY - _tInfo.fCY / 6},
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 5, _tInfo.fY - _tInfo.fCY / 14}
		};
		POINT PolygonPoint_Tail[6] = {
		   {_tInfo.fX,                            _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 6 },
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 6, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 6, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX,                            _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 30 },
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 4, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 4, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12}
		};
		POINT PolygonPoint_Body[4] = {
		   {_tInfo.fX - _tInfo.fCX / 8, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 8, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2}
		};

		Polygon(hDC, PolygonPoint_Wing, 5);
		Polygon(hDC, PolygonPoint_Tail, 6);
		Polygon(hDC, PolygonPoint_Body, 4);
	}
	if (index == 4)
	{
		POINT PolygonPoint_Wing[5] = {
		   {_tInfo.fX - _tInfo.fCX / 2, _tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2, _tInfo.fY + _tInfo.fCY / 6},
		   {_tInfo.fX + _tInfo.fCX / 2 ,_tInfo.fY - _tInfo.fCY / 14},
		   {_tInfo.fX,               _tInfo.fY - _tInfo.fCY / 6},
		   {_tInfo.fX - _tInfo.fCX / 2, _tInfo.fY - _tInfo.fCY / 14}
		};
		POINT PolygonPoint_Tail[6] = {
		   {_tInfo.fX,                            _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 6 },
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12},
		   {_tInfo.fX + _tInfo.fCX / 2 - _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX,                            _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 30 },
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 2 + _tInfo.fCX / 7, _tInfo.fY - _tInfo.fCY / 2 + _tInfo.fCY / 12}
		};
		POINT PolygonPoint_Body[4] = {
		   {_tInfo.fX - _tInfo.fCX / 7, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 7, _tInfo.fY + _tInfo.fCY / 2},
		   {_tInfo.fX + _tInfo.fCX / 8, _tInfo.fY - _tInfo.fCY / 2},
		   {_tInfo.fX - _tInfo.fCX / 8, _tInfo.fY - _tInfo.fCY / 2}
		};

		Polygon(hDC, PolygonPoint_Wing, 5);
		Polygon(hDC, PolygonPoint_Tail, 6);
		Polygon(hDC, PolygonPoint_Body, 4);
	}
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void CRenderMgr::BossMonsterRender(HDC hDC, INFO _tInfo, RECT _tRect)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // 테두리
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	// 브러시 생성
	HBRUSH hBrushBlue = CreateSolidBrush(RGB(0, 144, 199));
	HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hBrushPink = CreateSolidBrush(RGB(255, 197, 185));
	HBRUSH hBrushLightPink = CreateSolidBrush(RGB(255, 239, 235));

	//// 원래 브러시 백업
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushBlue);
	Ellipse(hDC, _tRect.left, _tRect.top, _tRect.right, _tRect.bottom);


	//// 흰색
	SelectObject(hDC, hBrushWhite);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 12, _tRect.top + _tInfo.fCY / 8, _tRect.right - _tInfo.fCX / 12, _tRect.bottom);

	Ellipse(hDC, _tRect.left + _tInfo.fCX / 4, _tRect.top + _tInfo.fCY / 12, _tRect.right - _tInfo.fCY / 2, _tRect.bottom - _tInfo.fCY / 2);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 2, _tRect.top + _tInfo.fCY / 12, _tRect.right - _tInfo.fCY / 4, _tRect.bottom - _tInfo.fCY / 2);

	//// 검정색
	SelectObject(hDC, hBrushBlack);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 3, _tRect.top + _tInfo.fCY / 8, _tRect.right - _tInfo.fCY / 1.9, _tRect.bottom - _tInfo.fCY / 1.5);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 1.9, _tRect.top + _tInfo.fCY / 8, _tRect.right - _tInfo.fCY / 3, _tRect.bottom - _tInfo.fCY / 1.5);

	//// 흰색 다시 사용
	SelectObject(hDC, hBrushWhite);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 2.7, _tRect.top + _tInfo.fCY / 6, _tRect.right - _tInfo.fCY / 1.8, _tRect.bottom - _tInfo.fCY / 1.4);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 1.8, _tRect.top + _tInfo.fCY / 6, _tRect.right - _tInfo.fCY / 2.7, _tRect.bottom - _tInfo.fCY / 1.4);

	//// 입 선
	MoveToEx(hDC, _tRect.left + _tInfo.fCX / 2, _tRect.top + _tInfo.fCY / 2.5, nullptr);
	LineTo(hDC, _tRect.left + _tInfo.fCX / 2, _tRect.top + _tInfo.fCY / 1.1);

	MoveToEx(hDC, _tRect.left + _tInfo.fCX / 2, _tRect.top + _tInfo.fCY / 1.1, nullptr);
	LineTo(hDC, _tRect.left + _tInfo.fCX / 5, _tRect.top + _tInfo.fCY / 1.4);

	MoveToEx(hDC, _tRect.left + _tInfo.fCX / 2, _tRect.top + _tInfo.fCY / 1.1, nullptr);
	LineTo(hDC, _tRect.right - _tInfo.fCX / 5, _tRect.top + _tInfo.fCY / 1.4);

	//// 코
	SelectObject(hDC, hBrushRed);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 1.7, _tRect.top + _tInfo.fCY / 2.5, _tRect.right - _tInfo.fCX / 1.7, _tRect.bottom - _tInfo.fCY / 2.3);


	//// 수염 선
	MoveToEx(hDC, _tRect.left + _tInfo.fCX / 4, _tRect.bottom - _tInfo.fCY / 2, nullptr);
	LineTo(hDC, _tRect.left + _tInfo.fCX / 12, _tRect.bottom - _tInfo.fCY / 1.5);
	MoveToEx(hDC, _tRect.left + _tInfo.fCX / 4, _tRect.bottom - _tInfo.fCY / 2 + _tInfo.fCY / 14, nullptr);
	LineTo(hDC, _tRect.left + _tInfo.fCX / 24, _tRect.bottom - _tInfo.fCY / 1.5 + _tInfo.fCY / 7);

	MoveToEx(hDC, _tRect.right - _tInfo.fCX / 4, _tRect.bottom - _tInfo.fCY / 2, nullptr);
	LineTo(hDC, _tRect.right - _tInfo.fCX / 12, _tRect.bottom - _tInfo.fCY / 1.5);
	MoveToEx(hDC, _tRect.right - _tInfo.fCX / 4, _tRect.bottom - _tInfo.fCY / 2 + _tInfo.fCY / 14, nullptr);
	LineTo(hDC, _tRect.right - _tInfo.fCX / 24, _tRect.bottom - _tInfo.fCY / 1.5 + _tInfo.fCY / 7);


	//// 브러시 복원 및 해제
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrushBlue);
	DeleteObject(hBrushWhite);
	DeleteObject(hBrushBlack);
	DeleteObject(hBrushRed);
	DeleteObject(hPen);
}

void CRenderMgr::BossMonsterMadFaceRender(HDC hDC, INFO _tInfo, RECT _tRect)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // 테두리
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	// 브러시 생성
	HBRUSH hBrushBlue = CreateSolidBrush(RGB(0, 144, 199));
	HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hBrushPink = CreateSolidBrush(RGB(255, 197, 185));
	HBRUSH hBrushLightPink = CreateSolidBrush(RGB(255, 239, 235));

	//// 원래 브러시 백업
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushBlue);
	
	Ellipse(hDC, _tRect.left, _tRect.top, _tRect.right, _tRect.bottom);

	//// 흰색
	SelectObject(hDC, hBrushWhite);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 12, _tRect.top + _tInfo.fCY / 8, _tRect.right - _tInfo.fCX / 12, _tRect.bottom);

	// 핑크
	SelectObject(hDC, hBrushWhite);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 4, _tRect.top + _tInfo.fCY / 12, _tRect.right - _tInfo.fCY / 2, _tRect.bottom - _tInfo.fCY / 2);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 2, _tRect.top + _tInfo.fCY / 12, _tRect.right - _tInfo.fCY / 4, _tRect.bottom - _tInfo.fCY / 2);


	//// 검정색
	SelectObject(hDC, hBrushWhite);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 3, _tRect.top + _tInfo.fCY / 8, _tRect.right - _tInfo.fCY / 1.9, _tRect.bottom - _tInfo.fCY / 1.5);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 1.9, _tRect.top + _tInfo.fCY / 8, _tRect.right - _tInfo.fCY / 3, _tRect.bottom - _tInfo.fCY / 1.5);

	//// 흰색 다시 사용
	SelectObject(hDC, hBrushWhite);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 2.7, _tRect.top + _tInfo.fCY / 6, _tRect.right - _tInfo.fCY / 1.8, _tRect.bottom - _tInfo.fCY / 1.4);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 1.8, _tRect.top + _tInfo.fCY / 6, _tRect.right - _tInfo.fCY / 2.7, _tRect.bottom - _tInfo.fCY / 1.4);

	//// 입 선
	MoveToEx(hDC, _tRect.left + _tInfo.fCX / 2, _tRect.top + _tInfo.fCY / 2.5, nullptr);
	LineTo(hDC, _tRect.left + _tInfo.fCX / 2, _tRect.top + _tInfo.fCY / 1.1);

	//// 코
	SelectObject(hDC, hBrushRed);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 1.7, _tRect.top + _tInfo.fCY / 2.5, _tRect.right - _tInfo.fCX / 1.7, _tRect.bottom - _tInfo.fCY / 2.3);

	//// 수염 선
	MoveToEx(hDC, _tRect.left + _tInfo.fCX / 4, _tRect.bottom - _tInfo.fCY / 2, nullptr);
	LineTo(hDC, _tRect.left + _tInfo.fCX / 12, _tRect.bottom - _tInfo.fCY / 1.5);
	MoveToEx(hDC, _tRect.left + _tInfo.fCX / 4, _tRect.bottom - _tInfo.fCY / 2 + _tInfo.fCY / 14, nullptr);
	LineTo(hDC, _tRect.left + _tInfo.fCX / 24, _tRect.bottom - _tInfo.fCY / 1.5 + _tInfo.fCY / 7);

	MoveToEx(hDC, _tRect.right - _tInfo.fCX / 4, _tRect.bottom - _tInfo.fCY / 2, nullptr);
	LineTo(hDC, _tRect.right - _tInfo.fCX / 12, _tRect.bottom - _tInfo.fCY / 1.5);
	MoveToEx(hDC, _tRect.right - _tInfo.fCX / 4, _tRect.bottom - _tInfo.fCY / 2 + _tInfo.fCY / 14, nullptr);
	LineTo(hDC, _tRect.right - _tInfo.fCX / 24, _tRect.bottom - _tInfo.fCY / 1.5 + _tInfo.fCY / 7);


	//// 브러시 복원 및 해제
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrushBlue);
	DeleteObject(hBrushWhite);
	DeleteObject(hBrushBlack);
	DeleteObject(hBrushRed);
	DeleteObject(hBrushPink);
	DeleteObject(hBrushLightPink);
	DeleteObject(hPen);
}

void CRenderMgr::CrashEffectRener(HDC hDC, INFO _tInfo, RECT _tRect)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 131, 13)); // 테두리
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 234, 178));   //  채우기

	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC, _tRect.left - _tInfo.fCX / 5.f, _tRect.top + _tInfo.fCY / 1.8f, _tRect.right - _tInfo.fCX / 1.9f, _tRect.bottom + _tInfo.fCY / 4.8f);
	Ellipse(hDC, _tRect.left, _tRect.top, _tRect.right, _tRect.bottom);
	Ellipse(hDC, _tRect.left - _tInfo.fCX / 2.9f, _tRect.top - _tInfo.fCY / 4.7f, _tRect.right - _tInfo.fCX / 2, _tRect.bottom - _tInfo.fCY / 3);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 1.7f, _tRect.top + _tInfo.fCY / 1.8f, _tRect.right + _tInfo.fCX / 4.7f, _tRect.bottom + _tInfo.fCY / 4.8f);

	// 원래 브러시, 펜으로 복원
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void CRenderMgr::DorayakiRender(HDC hDC, INFO _tInfo, RECT _tRect)
{
	HBRUSH hBrushBrown1 = CreateSolidBrush(RGB(135, 62, 35));
	HBRUSH hBrushYellow = CreateSolidBrush(RGB(241, 228, 157));
	HBRUSH hBrushBrown2 = CreateSolidBrush(RGB(135, 62, 35));
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	// 이전 브러시 저장
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushBrown1);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 10, _tRect.top + _tInfo.fCY / 3, _tRect.right - _tInfo.fCX / 10, _tRect.bottom - 6);

	// 두 번째 브러시 선택
	SelectObject(hDC, hBrushYellow);
	Ellipse(hDC, _tRect.left, _tRect.top + _tInfo.fCY / 4, _tRect.right, _tRect.bottom - _tInfo.fCY / 4);
	Ellipse(hDC, _tRect.left, _tRect.top + _tInfo.fCY / 6, _tRect.right, _tRect.bottom - _tInfo.fCY / 6);

	// 세 번째 브러시 선택
	SelectObject(hDC, hBrushBrown2);
	Ellipse(hDC, _tRect.left + _tInfo.fCX / 10, _tRect.top + _tInfo.fCY / 9, _tRect.right - _tInfo.fCX / 10, _tRect.bottom - _tInfo.fCY / 3);

	// 원래 브러시 복구
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);

	// 리소스 해제
	DeleteObject(hBrushBrown1);
	DeleteObject(hBrushYellow);
	DeleteObject(hBrushBrown2);
	DeleteObject(hPen);
}

void CRenderMgr::Background(HDC hDC) { // 백그라운드
	for (int y = 0; y < WINCY; ++y) // 플레이 사각형 영역의 세로 만큼 반복 y씩증감시켜서 그라데이션
	{
		//50, 133, 168
		COLORREF color = RGB(61 + y * (184- 61) / WINCY,
							171 + y * (230- 171) / WINCY,
							225 + y * (247- 225) / WINCY); // 증감할때마다 rgb값 변화 

		SetDCBrushColor(hDC, color); //브러쉬 값 color로 설정

		HBRUSH brush = (HBRUSH)GetStockObject(DC_BRUSH); // hbrush로 브러쉬값 받아오고 DC브러쉬에 값저장

		RECT rc = { 0, y, WINCX, y + 1 }; // 색채움을위한 y값 추적해서 1픽셀 사각형 추가
		FillRect(hDC, &rc, brush); // 아까 셋째줄에서 저장한 값 불러와서 그값으로 색채움
	}

	HBRUSH hBrush = CreateSolidBrush(RGB(220, 238, 239));
	HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	//l t r b
	Ellipse(hDC, -10, WINCY/3,      40,  WINCY / 3 + 40);
	Ellipse(hDC, 16,  WINCY/3 - 30, 95, WINCY / 3 + 50);
	Ellipse(hDC, 55,  WINCY/3 - 40, 135, WINCY / 3 + 40);
	Ellipse(hDC, 95, WINCY / 3 - 10, 180, WINCY / 3 + 40);

	Ellipse(hDC, WINCX/ 2 + 30, WINCY / 5, WINCX / 2 + 90, WINCY / 5 + 50);
	Ellipse(hDC, WINCX/ 2 + 70, WINCY / 5 - 30, WINCX / 2 + 170, WINCY / 5 + 60);
	Ellipse(hDC, WINCX/ 2 + 140, WINCY / 5 - 40, WINCX / 2 + 260, WINCY / 5 + 50);
	Ellipse(hDC, WINCX / 2 + 220, WINCY / 5 - 25, WINCX / 2 + 320, WINCY / 5 + 55);
	Ellipse(hDC, WINCX/ 2 + 210 , WINCY / 5 + 7 , WINCX / 2 + 370, WINCY / 5 + 50);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hBrush);
}
