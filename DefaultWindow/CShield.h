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

	float		m_fSinRadius;	// 자전 각도
	float		m_fSinAngle;	// 회전 속도
};

