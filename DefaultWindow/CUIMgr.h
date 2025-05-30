#pragma once
#include "CObj.h"
#include "CMonster.h" // CMonster 클래스에 대한 

class CUIMgr
{
public:
	static CUIMgr* GetInst()
	{
		return &CuiMgr;
	}

	void ShowUI(std::list<CObj*>(&objList)[OBJ_END], HDC _Hdc);
	void DrawBossHpBar(HDC hDC, CMonster* pBoss);
protected:

private:
	CUIMgr() = default;
	~CUIMgr() = default;
	CUIMgr& operator=(CUIMgr& _Other) = delete;
	CUIMgr(CUIMgr& _Other) = delete;

	static CUIMgr CuiMgr;
};

