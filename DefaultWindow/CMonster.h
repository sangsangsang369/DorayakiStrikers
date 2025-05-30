#pragma once
#include "CObj.h"
#include "CRenderMgr.h"
class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void set_MonsterType(Monster_type eType) { m_eMonsterType = eType; }; //MonsterType 
	void Set_ShootInterval(float fInterval) { m_fShootInterval = fInterval; } //사격 간격 
	void Set_Bullet(list<CObj*>* mBullet) { m_pBullet = mBullet; }
	int  Get_Boss_HP() { return m_ihp; };




public:
	void Update_Boss();
	void Update_Normal();
	void shoot_Normal();
	//데미지 값 총알 맞으면 호출 
	void Take_Damage(int iDamage = 1);






private:
	int m_iMx;  //몬스터 x 좌표
	int m_iMy;  //몬스터 y 좌표 
	Monster_type m_eMonsterType;  //몬스터 타입 멤버변수 1.NORMAL,2.BossMonster 
	float m_fDirX;  //플레이어 방향
	float m_fDirY;
	list<CObj*>* m_pBullet; //총알 객체 
	int m_iMaxHP; //최대 체력 
	int m_ihp; //보스 몬스터 hp 
	//boss 패턴
public:
	void Shoot_FiveWay();
	void Shoot_Homing();
	void Set_Homing(list<CObj*>* PHoming) { m_pHomingBullet = PHoming; }  // Setter 
	int Get_Random_Pattern();
	void Try_Special_Pattern();


private:

	DWORD m_dwShootTime;  //발사시간 
	float m_fShootInterval; //발사 간격 
	int m_iRadius;  //보스
	float m_fDegree; //보스 
	float m_iAnimFrameIndex;
	float m_fOriginalX; //보스 전용 x좌표 
	float m_fOriginalY; //보스 전용 Y 좌표 

	DWORD	m_dwSpawnTime = 0; // 생성 시각 저장
	bool	m_bTargeting = false; // 처음엔 false

private:
	//보스 관련 
	list<CObj*>* m_pHomingBullet;  //나선총알 
	int m_iSkillPattern;
	int m_iLastPattern;
	int m_iPatternCount;

private:
	// 레이저 시스템
	bool m_bLaserMode;          // 레이저 모드 활성화 여부
	bool m_bLaserUsed;          // 레이저 한번 썼는지 체크 
	DWORD m_dwLaserStartTime;   // 레이저 시작 시간
	DWORD m_dwLaserDuration;    // 레이저 지속시간 (3000ms = 3초)
	DWORD m_dwLaserBulletTime;
	public:
	void Render_Laser(HDC hDC);  // 레이저 전용 렌더링 함수
	bool Is_Laser_Active() { return m_bLaserMode; }  // 레이저 활성화 상태 체크
	// CMonster.h
	








};

