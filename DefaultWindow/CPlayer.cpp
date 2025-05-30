#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"

CPlayer::CPlayer() : m_pBullet(nullptr), m_iPlayerLife(0), m_iScore(0), 
					m_bPosinDir(false), 
					m_bShieldExpired(false), m_dwShieldStartTime(0), m_bSKeyPressed(false)
{
	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
}

CPlayer::~CPlayer()
{
	Release();
}


void CPlayer::Initialize()
{
	m_tInfo = { WINCX >> 1, WINCY - WINCY/6, 50.f, 50.f };
	m_fSpeed = 10.f;
	m_fDistance = 60.f;
	m_iPlayerLife = 5000;
	m_fAngle = 90;
}

int CPlayer::Update()
{
	float fx1 = m_tInfo.fCX / 2.f;
	float fy1 = m_tInfo.fCY / 2.f;

	if (m_tInfo.fX < 10 + fx1) { // 가로 세로 영역 플레이어 ,벽 충돌처리
		m_tInfo.fX = 10 + fx1;
	}
	else if (m_tInfo.fX > WINCX - 10 - fx1) {
		m_tInfo.fX = WINCX - 10 - fx1;
	}
	if (m_tInfo.fY < 10 + fy1) {
		m_tInfo.fY = 10 + fy1;
	}
	else if (m_tInfo.fY > WINCY - 10 - fy1) {
		     m_tInfo.fY = WINCY - 10 - fy1;
	}

	Key_Input();

	__super::Update_Rect();

	return NOEVENT;
}

void CPlayer::Late_Update()
{
	m_tPosin.x = long(m_tInfo.fX + m_fDistance * cosf(m_fAngle * (PI / 180.f)));
	m_tPosin.y = long(m_tInfo.fY - m_fDistance * sinf(m_fAngle * (PI / 180.f)));

	if (m_fAngle >= 180.f)
	{
		m_bPosinDir = true;
	}
	if (m_fAngle <= 0.f)
	{
		m_bPosinDir = false;
	}
}

void CPlayer::Render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));  
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	// 포신 그리기
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, NULL);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	
	CRenderMgr::PlayerRender(hDC, m_tInfo);

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

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	// 오른쪽으로 이동
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}
	// 왼쪽으로 이동
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}
	// 위쪽으로 이동
	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}
	// 아래쪽으로 이동
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}
	// 불렛 발사
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_bReload == true)
		{
			m_pBullet->push_back(Create_Bullet(m_fAngle));
			m_bReload = false;
		}
	}
	else
	{
		m_bReload = true;
	}

	if (GetAsyncKeyState('A'))
	{
		m_pBullet->push_back(Create_SpiralBullet(m_fAngle, LEFT));
		m_pBullet->push_back(Create_SpiralBullet(m_fAngle, RIGHT));
	}

	// 포신 방향
	if (GetAsyncKeyState('D'))
	{
		if (!m_bPosinDir)
		{
			m_fAngle += 5.f;
		}
		else if(m_bPosinDir)
		{
			m_fAngle -= 5.f;
		}
	}

	// 쉴드 생성
	if (GetAsyncKeyState('S') & 0x8000)
	{
		if (!m_bSKeyPressed)
		{
			m_dwShieldStartTime = GetTickCount();
			m_bSKeyPressed = true;
			m_bShieldExpired = false;
		}
		if (!m_bShieldExpired)
		{
			DWORD shieldTime = GetTickCount() - m_dwShieldStartTime;

			if (shieldTime >= 10000)
			{
				for_each(m_pShield->begin(), m_pShield->end(), Safe_Delete<CObj*>);
				m_pShield->clear();
				m_bShieldExpired = true;
			}
			else
			{
				m_pShield->push_back(Create_Shield());
			}
		}
	}
	else
	{
		m_bSKeyPressed = false;
		m_bShieldExpired = false;
		for_each(m_pShield->begin(), m_pShield->end(), Safe_Delete<CObj*>);
		m_pShield->clear();
	}
}



CObj* CPlayer::Create_Bullet(float fAngle)
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create_Obj();
	dynamic_cast<CBullet*>(pBullet)->Set_CrashEffect(m_pCrashEffect);

	dynamic_cast<CBullet*>(pBullet)->Set_BulletType(BULLET_NORMAL);

	pBullet->Set_Pos(m_tPosin.x, m_tPosin.y);
	pBullet->Set_Angle(fAngle);

	return pBullet;
}

CObj* CPlayer::Create_SpiralBullet(float fAngle, int _iLR)
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create_Obj();
	dynamic_cast<CBullet*>(pBullet)->Set_CrashEffect(m_pCrashEffect);

	dynamic_cast<CBullet*>(pBullet)->Set_BulletType(BULLET_SPIRAL);
	dynamic_cast<CBullet*>(pBullet)->Set_Spiral_LR(_iLR);

	pBullet->Set_Pos(m_tPosin.x, m_tPosin.y);
	pBullet->Set_Angle(fAngle);

	return pBullet;
}

CObj* CPlayer::Create_Shield()
{
	CObj* pShield = CAbstractFactory<CShield>::Create_Obj();
	pShield->Set_target(this);

	return pShield;
}

