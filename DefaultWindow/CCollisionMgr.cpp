#include "pch.h"
#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CScoreMgr.h"
#include "CMonster.h"
#include "CPlayer.h"

/*Coll_CHECK : 충돌유무 확인 함수 
최소 x좌표가 최대 x좌표보다 작거나 같음, 최대 x좌표가 최소 x좌표보다 크거나 같을경우 충돌판정 , y좌표도 동일방식*/


bool CCollisionMgr::Coll_CHECK(const RECT& rcSrc, const RECT& rcTmp) {

	return !(rcSrc.right < rcTmp.left || rcSrc.left > rcTmp.right || rcSrc.bottom < rcTmp.top || rcSrc.top > rcTmp.bottom);
}

void CCollisionMgr::Coll_TwoObj(std::list<CObj*>& ObjA, std::list<CObj*>& ObjB) { //오브젝트 두개 충돌 검사용

	for (auto itObjA = ObjA.begin(); itObjA != ObjA.end();) {

		bool bDead = false;

		for (auto itObjB = ObjB.begin(); itObjB != ObjB.end();) { //auto = 리스트 반복자

			if (Coll_CHECK((*itObjA)->Get_Rect(), (*itObjB)->Get_Rect())) 
			{ //오브젝트 두개 좌표 비교
	
				Safe_Delete(*itObjA);
				itObjA = ObjA.erase(itObjA);

				Safe_Delete(*itObjB);
				itObjB = ObjB.erase(itObjB);
				CStageMgr::GetInst()->AddKillCount(1);
  				CScoreMgr::GetInst()->SetAddScore(100);
				bDead = true;

				break;
			}

			else {
				++itObjB; // 빗나간 경우 , 그외 itartor ++
			}

		}

		if (!bDead) ++itObjA; // 마찬가지
	}
}

void CCollisionMgr::Coll_PLMON(std::list<CObj*>& Player, std::list<CObj*>& Monster) {
	for (auto itPlayer = Player.begin(); itPlayer != Player.end(); ) {
		bool bBakchigi = false;
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(*itPlayer);

		for (auto itMonster = Monster.begin(); itMonster != Monster.end(); ) {
			if (Coll_CHECK((*itPlayer)->Get_Rect(), (*itMonster)->Get_Rect())) {
				Safe_Delete(*itMonster);
				itMonster = Monster.erase(itMonster);

				// 플레이어 HP 감소
				if (pPlayer) pPlayer->Minus_PlayerLife();
				CStageMgr::GetInst()->AddKillCount(1);
				// HP가 0 이하라면 전체 삭제
				if (pPlayer && pPlayer->Get_PlayerLife() <= 0) {
					// m_pTarget 초기화
					for (auto& obj : Player) obj->Set_Target(nullptr);
					for (auto& obj : Monster) obj->Set_Target(nullptr);

					// Player 전체 삭제
					for (auto it = Player.begin(); it != Player.end(); ) {
						Safe_Delete(*it);
						it = Player.erase(it);
					}
					// Monster 전체 삭제
					for (auto it = Monster.begin(); it != Monster.end(); ) {
						Safe_Delete(*it);
						it = Monster.erase(it);
					}

					// UI 갱신 (ShowUI는 보통 메인루프에서 호출되지만, 즉시 갱신 원하면 아래처럼 호출)
					// 예시: CUIMgr::GetInst()->ShowUI(m_ObjList, hDC);
					// hDC와 m_ObjList는 상황에 맞게 전달

					return; // 함수 종료
				}

				bBakchigi = true;
				break;
			}
			else {
				++itMonster;
			}
		}
		if (!bBakchigi) {
			++itPlayer;
		}
	}
}

void CCollisionMgr::Coll_Shield(std::list<CObj*>& Shield, std::list<CObj*>& Mon_Bullet) { //오브젝트 두개 충돌 검사용

	for (auto itShield = Shield.begin(); itShield != Shield.end();) {

		bool bShieldchk = false;

		for (auto itMon_Bullet = Mon_Bullet.begin(); itMon_Bullet != Mon_Bullet.end();) { //auto = 리스트 반복자

			if (Coll_CHECK((*itShield)->Get_Rect(), (*itMon_Bullet)->Get_Rect())) { //오브젝트 두개 좌표 비교

				Safe_Delete(*itShield);
				itShield = Shield.erase(itShield);

				Safe_Delete(*itMon_Bullet);
				itMon_Bullet = Mon_Bullet.erase(itMon_Bullet);

				bShieldchk = true;

				break;
			}

			else {
				++itMon_Bullet; // 빗나간 경우 , 그외 itartor ++
			}

		}

		if (!bShieldchk) ++itShield; // 마찬가지
	}
};

void CCollisionMgr::Coll_Bullet_Boss(
	std::list<CObj*>& player,
	std::list<CObj*>& bulletList,
	std::list<CObj*>& bossList,
	std::list<CObj*>& bossBulletList // 몬스터 불렛 리스트 추가
) {
	for (auto itBoss = bossList.begin(); itBoss != bossList.end(); ) {
		CMonster* pBoss = dynamic_cast<CMonster*>(*itBoss);
		if (!pBoss) {
			++itBoss;
			continue;
		}

		for (auto itBullet = bulletList.begin(); itBullet != bulletList.end(); ) {
			if (Coll_CHECK((*itBoss)->Get_Rect(), (*itBullet)->Get_Rect())) {
				// 보스에게 데미지
				pBoss->Take_Damage(1);

				// 총알 삭제
				Safe_Delete(*itBullet);
				itBullet = bulletList.erase(itBullet);

				// 보스가 죽었으면 삭제 및 포인터 초기화
				if (pBoss->m_bDead) 
				{
					CStageMgr::GetInst()->SetBossClear(true);
					CStageMgr::GetInst()->AddKillCount(1);

					// 보스 리스트 전체 삭제
					for (auto it = bossList.begin(); it != bossList.end(); ) 
					{
						Safe_Delete(*it);
						it = bossList.erase(it);
					}
					// 총알 리스트 전체 삭제
					for (auto it = bulletList.begin(); it != bulletList.end(); ) 
					{
						Safe_Delete(*it);
						it = bulletList.erase(it);
					}
					// 몬스터 불렛 리스트 전체 삭제
					for (auto it = bossBulletList.begin(); it != bossBulletList.end(); ) 
					{
						Safe_Delete(*it);
						it = bossBulletList.erase(it);
					}
					// 플레이어 리스트 전체 삭제
					for (auto it = player.begin(); it != player.end(); ) 
					{
						Safe_Delete(*it);
						it = player.erase(it);
					}
					CStageMgr::GetInst()->SetBoss(nullptr);
					return;
				}
			}
			else {
				++itBullet;
			}
		}
		++itBoss;
	}
}

void CCollisionMgr::Coll_MOONSTER_PL(std::list<CObj*>& Player, std::list<CObj*>& Monster_Bullet, std::list<CObj*>& Monster) {
	for (auto itPlayer = Player.begin(); itPlayer != Player.end(); ) 
	{
		bool bBakchigi = false;
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(*itPlayer);

		for (auto itMonster_Bullet = Monster_Bullet.begin(); itMonster_Bullet != Monster_Bullet.end(); ) 
		{
			if (Coll_CHECK((*itPlayer)->Get_Rect(), (*itMonster_Bullet)->Get_Rect())) 
			{
				// 몬스터 총알 삭제
				Safe_Delete(*itMonster_Bullet);
				itMonster_Bullet = Monster_Bullet.erase(itMonster_Bullet);

				// 플레이어 HP 감소
				if (pPlayer) pPlayer->Minus_PlayerLife();

				// HP가 0 이하라면 전체 삭제
				if (pPlayer && pPlayer->Get_PlayerLife() <= 0) 
				{
					// m_pTarget 초기화
					for (auto& obj : Player) obj->Set_Target(nullptr);
					for (auto& obj : Monster) obj->Set_Target(nullptr);

					// Player 전체 삭제
					for (auto it = Player.begin(); it != Player.end(); ) 
					{
						Safe_Delete(*it);
						it = Player.erase(it);
					}
					// Monster_Bullet 전체 삭제
					for (auto it = Monster_Bullet.begin(); it != Monster_Bullet.end(); ) 
					{
						Safe_Delete(*it);
						it = Monster_Bullet.erase(it);
					}
					// Monster 전체 삭제
					for (auto it = Monster.begin(); it != Monster.end(); ) 
					{
						Safe_Delete(*it);
						it = Monster.erase(it);
					}

					// (선택) UI 갱신 필요시 메인루프에서 ShowUI 호출
					return;
				}

				bBakchigi = true;
				break;
			}
			else {
				++itMonster_Bullet;
			}
		}
		if (!bBakchigi) {
			++itPlayer;
		}
	}
}

void CCollisionMgr::Coll_Homing(std::list<CObj*>& Player, std::list<CObj*>& Homing_Bullet) { //오브젝트 두개 충돌 검사용

	for (auto itPlayer = Player.begin(); itPlayer != Player.end();) 
	{

		bool bHomingchk = false;

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(*itPlayer);
		for (auto itHoming_Bullet = Homing_Bullet.begin(); itHoming_Bullet != Homing_Bullet.end();) 
		{ //auto = 리스트 반복자

			if (Coll_CHECK((*itPlayer)->Get_Rect(), (*itHoming_Bullet)->Get_Rect())) 
			{ //오브젝트 두개 좌표 비교

				Safe_Delete(*itHoming_Bullet);
				itHoming_Bullet = Homing_Bullet.erase(itHoming_Bullet);

				// 플레이어 HP 감소
				if (pPlayer)
				{
					pPlayer->Minus_PlayerLife();
				}
				// HP가 0 이하라면 전체 삭제
				if (pPlayer && pPlayer->Get_PlayerLife() <= 0)
				{
					// m_pTarget 초기화
					for (auto& obj : Player) obj->Set_Target(nullptr);
					for (auto& obj : Homing_Bullet) obj->Set_Target(nullptr);

					// Player 전체 삭제
					for (auto it = Player.begin(); it != Player.end(); )
					{
						Safe_Delete(*it);
						it = Player.erase(it);
					}

					// 유도탄 삭제
					for (auto it = Homing_Bullet.begin(); it != Homing_Bullet.end(); )
					{
						Safe_Delete(*it);
						it = Homing_Bullet.erase(it);
					}


				}


				bHomingchk = true;

				break;
			}

			else {
				++itHoming_Bullet; // 빗나간 경우 , 그외 itartor ++
			}

		}

		if (!bHomingchk) ++itPlayer; // 마찬가지
	}
};

//void CCollisionMgr::Collision_Rect(list<CObj*> _pDst, list<CObj*> _pSrc) 이전코드
//{
//	RECT	rcCollision{};
//
//	for (auto& Dst : _pDst)
//	{
//		for (auto& Src : _pSrc)
//		{
//			if (IntersectRect(&rcCollision, &(Dst->Get_Rect()), &(Src->Get_Rect())))
//			{
//				Dst->Set_Dead();
//				Src->Set_Dead();
//			}
//		}
//	}
//
//
//}
//
//void CCollisionMgr::Collision_Circle(list<CObj*> _pDst, list<CObj*> _pSrc)
//{
//	for (auto& Dst : _pDst)
//	{
//		for (auto& Src : _pSrc)
//		{
//			if (Check_Sphere(Dst, Src))
//			{
//				Dst->Set_Dead();
//				Src->Set_Dead();
//			}
//		}
//	}
//}
//
//bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
//{
//	float	fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
//
//	float	fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
//	float	fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);
//
//	float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);
//
//	return fRadius >= fDistance;
//}
