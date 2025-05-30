#pragma once

#include "CObj.h"
#include "CCrashEffect.h"

class CBullet : public CObj
{
public:
	CBullet();
	CBullet(int iType, int iLR);
	virtual ~CBullet();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	CObj* Create_CrashEffect();
	void    Set_CrashEffect(list<CObj*>* pCrashEffect) { m_pCrashEffect = pCrashEffect; }

	void Set_BulletType(int _iType) { m_iBulletType = _iType; }
	void Set_Spiral_LR(int _iLR) { m_iSpiral_LR = _iLR; }

private:
	list<CObj*>* m_pCrashEffect;

private:
	int m_iBulletType;
	int m_iSpiral_LR;
	bool m_bStart;

	POINT		m_tCenter;
	float		m_fSinWidth;
	float		m_fSinAngle;
};

