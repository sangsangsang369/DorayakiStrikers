#include "pch.h"
#include "CScrewBullet.h"

CScrewBullet::CScrewBullet()
{
    ZeroMemory(&m_tCenter, sizeof(POINT));   // �߽��� �ʱ�ȭ
    m_fRotAngle = 0.f;                       // ȸ�� ���� 0������ ����
    m_fRotSpeed = 0.f;                       // ȸ�� �ӵ� (Initialize���� ����)
    m_fDistance = 0.f;                       // ȸ�� ������ (Initialize���� ����)
    m_bStart = true;                         // ���� �÷��� (ù �����ӿ� �߽��� ����)
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
	// Ÿ���� �ִٸ�, Ÿ�� �������� ���� ����
	if (m_pTarget != nullptr)
	{
		float dx = m_pTarget->Get_Info().fX - m_tCenter.x;
		float dy = m_tCenter.y - m_pTarget->Get_Info().fY; // y�� ���⿡ ���� ��ȣ ����
		m_fAngle = atan2f(dy, dx) * 180.f / PI; // ���� �� ��(degree) ��ȯ
	}

	// �߽��� ���� (���ŵ� m_fAngle ���)
	m_tCenter.x += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tCenter.y -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	// ���� ���� ����
	m_fRotAngle += m_fRotSpeed;

	// ���� �Ѿ� ��ġ = �߽��� + ���� ������
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