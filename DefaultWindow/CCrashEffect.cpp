#include "pch.h"
#include "CCrashEffect.h"
#include "CRenderMgr.h"

CCrashEffect::CCrashEffect()
{
	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 35.f;
}

CCrashEffect::~CCrashEffect()
{
}

void CCrashEffect::Initialize()
{
	m_dwEffectStartTime = GetTickCount();
}

int CCrashEffect::Update()
{
	__super::Update_Rect();
	DWORD effectTime = GetTickCount() - m_dwEffectStartTime;
	if (effectTime < 150 && m_tRect.top > 100)
	{
		return NOEVENT;
	}
	else
	{
		return DEAD;
	}
}

void CCrashEffect::Late_Update()
{
	
}

void CCrashEffect::Render(HDC hDC)
{
	CRenderMgr::CrashEffectRener(hDC, m_tInfo, m_tRect);
}

void CCrashEffect::Release()
{
}
