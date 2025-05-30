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

	// ������ 100
	m_fDistance = 60.f;
	m_fSpeed = 4.f;

	m_fSinRadius = 90.f;  // ȸ�� ����
	m_fSinAngle = 0.f; //  ȸ�� �ӵ�

	m_fAngle = 270.f;
}

int CShield::Update()
{
	__super::Update_Rect();

	// ���ǵ尪 ��ŭ ���� �ڵ����� �����ϰ�
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
	HPEN hPen = CreatePen(PS_SOLID,1,RGB(41, 249, 164)); // �׵θ�
	HBRUSH hBrush = CreateSolidBrush(RGB(235, 255, 245));   //  ä���

	// ���� ��� �귯�� ����
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// ���� �귯��, ������ ����
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	if (g_bHitbox)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 191, 255)); // 1 pixel �� ����
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen); // hDC�� �� ����
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH)); //NULL�귯���� ���� ����ȭ

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); // m_tRect���� ��ǥ���޾ƿͼ� �簢�� ��Ʈ�ڽ� ����

		SelectObject(hDC, hOldPen);

		DeleteObject(hPen); //�� �پ��� ����(�޸� ���� ������)
	}
}


void CShield::Release()
{
}
