#include "pch.h"
#include "CScrewBullet.h"

CScrewBullet::CScrewBullet()
{
    ZeroMemory(&m_tCenter, sizeof(POINT));   // 중심점 초기화
    m_fRotAngle = 0.f;                       // 회전 각도 0도부터 시작
    m_fRotSpeed = 0.f;                       // 회전 속도 (Initialize에서 설정)
    m_fDistance = 0.f;                       // 회전 반지름 (Initialize에서 설정)
    m_bStart = true;                         // 시작 플래그 (첫 프레임에 중심점 설정)
	m_pTarget = nullptr;
}

CScrewBullet::~CScrewBullet()
{
    Release();
}	


void CScrewBullet::Initialize()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_fSpeed = 6.f;


	m_fRotAngle = 0.f;
	m_fRotSpeed = 30.f;

	m_fDistance = 20.f;

	m_bStart = true;
}


int CScrewBullet::Update()
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

	return NOEVENT;
}


void CScrewBullet::Late_Update()
{
	// 타겟이 있다면, 타겟 방향으로 각도 갱신
	if (m_pTarget != nullptr)
	{
		float dx = m_pTarget->Get_Info().fX - m_tCenter.x;
		float dy = m_tCenter.y - m_pTarget->Get_Info().fY; // y축 방향에 따라 부호 조정
		m_fAngle = atan2f(dy, dx) * 180.f / PI; // 라디안 → 도(degree) 변환
	}

	// 중심점 직진 (갱신된 m_fAngle 사용)
	m_tCenter.x += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tCenter.y -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	// 자전 각도 증가
	m_fRotAngle += m_fRotSpeed;

	// 실제 총알 위치 = 중심점 + 자전 반지름
	m_tInfo.fX = m_tCenter.x + m_fDistance * cosf(m_fRotAngle * (PI / 180.f));
	m_tInfo.fY = m_tCenter.y - m_fDistance * sinf(m_fRotAngle * (PI / 180.f));
}

void CScrewBullet::Render(HDC hDC)
{
	CRenderMgr::DorayakiRender(hDC, m_tInfo, m_tRect);
}

void CScrewBullet::Release()
{

}