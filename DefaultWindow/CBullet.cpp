#include "pch.h"
#include "CBullet.h"
#include "CAbstractFactory.h"

CBullet::CBullet()
{
	m_pCrashEffect = nullptr;
	m_iBulletType = BULLET_NORMAL;
	m_iSpiral_LR = LEFT;
	ZeroMemory(&m_tCenter, sizeof(POINT));
	m_fSinWidth = 0.f;
	m_fSinAngle = 0.f;
	m_bStart = false;
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 3.f;
	m_fSinWidth = 0.f;
	m_fSinAngle = 0.f; //  회전 속도
	m_pCrashEffect = nullptr;
	m_bStart = true;
}

int CBullet::Update()
{
	if (m_bDead)
		return DEAD;


	__super::Update_Rect();

	if (m_bStart)
	{
		m_tCenter.x = (long)m_tInfo.fX;
		m_tCenter.y = (long)m_tInfo.fY;

		m_bStart = false;
	}

	m_fSinWidth += 2.f;

	return NOEVENT;
}

void CBullet::Late_Update()
{
	if (100 >= m_tRect.top + 50)
	{
		m_bDead = true;
	}

	if (m_iBulletType == BULLET_NORMAL)
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	else if (m_iBulletType == BULLET_SPIRAL)
	{
		m_fSinAngle += 10.f;

		// 사인파 오프셋
		float fSinOffset = m_fSinWidth * sinf(m_fSinAngle * (PI / 180.f));

		// 탄의 각도의 수직 방향인 법선 방향을 90도 더해줘서 구함
		float normalAngle = m_fAngle + 90.f;

		m_tCenter.x += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tCenter.y -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

		if (m_iSpiral_LR == LEFT)
		{
			m_tInfo.fY = m_tCenter.y - fSinOffset * sinf(normalAngle * (PI / 180.f));
			m_tInfo.fX = m_tCenter.x + fSinOffset * cosf(normalAngle * (PI / 180.f));
		}
		else if (m_iSpiral_LR == RIGHT)
		{
			m_tInfo.fY = m_tCenter.y + fSinOffset * sinf(normalAngle * (PI / 180.f));
			m_tInfo.fX = m_tCenter.x - fSinOffset * cosf(normalAngle * (PI / 180.f));
		}
	}
}

void CBullet::Render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(96, 255, 108)); // 테두리
	HBRUSH hBrush = CreateSolidBrush(RGB(245, 255, 240));   //  채우기

	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,
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
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 1 pixel 펜 생성
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen); // hDC에 펜 저장
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH)); //NULL브러쉬로 안쪽 투명화

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); // m_tRect에서 좌표값받아와서 사각형 히트박스 생성

		SelectObject(hDC, hOldPen);

		DeleteObject(hPen); //펜 다쓰고 해제(메모리 누수 방지용)
	}
}

void CBullet::Release()
{
	m_pCrashEffect->push_back(Create_CrashEffect());
}

CObj* CBullet::Create_CrashEffect()
{
	CObj* pEffect = CAbstractFactory<CCrashEffect>::Create_Obj();
	pEffect->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	pEffect->Initialize();
	return pEffect;
}


