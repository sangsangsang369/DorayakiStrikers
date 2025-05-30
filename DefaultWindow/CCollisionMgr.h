#pragma once

#include "pch.h"
#include "CObj.h"

class CCollisionMgr {

public:
	static void Coll_TwoObj(list<CObj*>& ObjA, std::list<CObj*>& ObjB); //오브젝트 두개 처리용
	static void Coll_PLMON(list<CObj*>& Player, std::list<CObj*>& Monster);
	//static void Coll_PLMON(list<CObj*>& MonsterA, std::list<CObj*>& MonsterB);
	static void Coll_Shield(list<CObj*>& Shield, std::list<CObj*>& Mon_Bullet);
	static void Coll_Bullet_Boss(std::list<CObj*>& player, std::list<CObj*>& bulletList, std::list<CObj*>& bossList, std::list<CObj*>& bossBulletList);
	static void Coll_MOONSTER_PL(std::list<CObj*>& Player, std::list<CObj*>& Monster_Bullet, std::list<CObj*>& Monster);
	static void Coll_Homing(std::list<CObj*>& Player, std::list<CObj*>& Homing_Bullet);

private:
	static bool Coll_CHECK(const RECT& rcSrc, const RECT& rcTmp);
};








//class CCollisionMgr 이전코드
//{
//public:
//	static void		Collision_Rect(list<CObj*> _pDst, list<CObj*> _pSrc);
//	static void		Collision_Circle(list<CObj*> _pDst, list<CObj*> _pSrc);
//	static bool		Check_Sphere(CObj* pDst, CObj* pSrc);
//
//};

