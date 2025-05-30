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
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 130.f;
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
	if (g_bHitbox)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 1 pixel �� ����
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen); // hDC�� �� ����
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH)); //NULL�귯���� ���� ����ȭ

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); // m_tRect���� ��ǥ���޾ƿͼ� �簢�� ��Ʈ�ڽ� ����

		SelectObject(hDC, hOldPen);

		DeleteObject(hPen); //�� �پ��� ����(�޸� ���� ������)
	}
}

void CScrewBullet::Release()
{

}