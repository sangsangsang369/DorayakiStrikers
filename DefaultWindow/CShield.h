#pragma once
#include "CObj.h"
class CShield :
    public CObj
{
public:
	CShield();
	virtual ~CShield();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	POINT		m_tCenter;

	float		m_fSinRadius;	// ���� ����
	float		m_fSinAngle;	// ȸ�� �ӵ�
};

