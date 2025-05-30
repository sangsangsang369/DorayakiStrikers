#pragma once
#include "Define.h"
class CRenderMgr
{
public:
	static void PlayerRender(HDC hDC, INFO _tInfo);
	static void NormalMonsterRender(HDC hDC, INFO _tInfo, float _index);
	static void BossMonsterRender(HDC hDC, INFO _tInfo, RECT _tRect);
	static void BossMonsterMadFaceRender(HDC hDC, INFO _tInfo, RECT _tRect);
	static void CrashEffectRener(HDC hDC, INFO _tInfo, RECT _tRect);
	static void DorayakiRender(HDC hDC, INFO _tInfo, RECT _tRect);
    static void Background(HDC hdc);
};

