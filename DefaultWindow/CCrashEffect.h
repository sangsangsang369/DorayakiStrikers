#pragma once
#include "CObj.h"

class CCrashEffect :
    public CObj
{
public:
	CCrashEffect();
	virtual ~CCrashEffect();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	DWORD         m_dwEffectStartTime;
};

