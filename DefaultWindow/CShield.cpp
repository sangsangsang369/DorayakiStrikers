#include "pch.h"
#include "CShield.h"

CShield::CShield() : m_fSinRadius(0.f), m_fSinAngle(0.f)
{
	ZeroMemory(&m_tCenter, sizeof(POINT));
}

CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	// 반지름 100
	m_fDistance = 60.f;
	m_fSpeed = 4.f;

	m_fSinRadius = 90.f;  // 회전 각도
	m_fSinAngle = 0.f; //  회전 속도

	m_fAngle = 270.f;
}

int CShield::Update()
{
	__super::Update_Rect();

	// 스피드값 만큼 각도 자동으로 증가하게
	m_fAngle += m_fSpeed;
	
	return NOEVENT;
}

void CShield::Late_Update()
{
	m_fSinAngle += 40.f;
	m_fSinRadius = m_fDistance + 3 * sinf(m_fSinAngle * (PI / 180.f));

	m_tInfo.fX = m_pTarget->Get_Info().fX + m_fSinRadius * sinf(m_fAngle * (PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - m_fSinRadius * cosf(m_fAngle * (PI / 180.f));
}

void CShield::Render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_SOLID,1,RGB(41, 249, 164)); // 테두리
	HBRUSH hBrush = CreateSolidBrush(RGB(235, 255, 245));   //  채우기

	// 이전 펜과 브러시 저장
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// 원래 브러시, 펜으로 복원
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


void CShield::Release()
{
}
