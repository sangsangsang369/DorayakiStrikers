#include "pch.h"
#include "CMonster_Bullet.h"

CMonster_Bullet::CMonster_Bullet()
{
}

CMonster_Bullet::~CMonster_Bullet()
{
	Release();
}

void CMonster_Bullet::Initialize()
{
	m_tInfo.fCX = 15.f;  //총알 크기(플레이어 총알보단 큼) 
	m_tInfo.fCY = 15.f;
	m_fSpeed = 2.f;   //이동속도 
}

int CMonster_Bullet::Update()
{
	if (m_bDead)
		return DEAD;


	__super::Update_Rect();

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	return NOEVENT;

    
	return 0;
}

void CMonster_Bullet::Late_Update()
{
	if (100 >= m_tRect.top + 50) //메모리 누수 잡음
	{
		m_bDead = true;
	}
}

void CMonster_Bullet::Render(HDC hDC)
{  
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 55)); // 테두리
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 217, 227));   //  채우기

	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,  //총알 
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	if (g_bHitbox)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 191, 255)); // 1 pixel 펜 생성
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen); // hDC에 펜 저장
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH)); //NULL브러쉬로 안쪽 투명화

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); // m_tRect에서 좌표값받아와서 사각형 히트박스 생성

		SelectObject(hDC, hOldPen);

		DeleteObject(hPen); //펜 다쓰고 해제(메모리 누수 방지용)
	}
}

void CMonster_Bullet::Release()
{

}
