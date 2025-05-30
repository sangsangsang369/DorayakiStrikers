#pragma once
#include "CObj.h"
#include "CRenderMgr.h"

// ���������� �־����� �Ѿ� Ŭ����
class CScrewBullet : public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Set_target(CObj* pTarget) { m_pTarget = pTarget; }
private:
	POINT m_tCenter;          // �߽���
	float m_fRotAngle;        // ���� ����
	float m_fRotSpeed;        // ȸ�� �ӵ� 
	float m_fDistance;        // ȸ�� ������
	bool m_bStart;            // ���� �߽��� 
};