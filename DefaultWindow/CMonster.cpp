#include "pch.h"
#include "CMonster.h"
#include "CAbstractFactory.h"
#include "Define.h"
#include "CMonster_Bullet.h"
#include "CScrewBullet.h"
#include<iostream>

CMonster::CMonster()
{

	m_dwSpawnTime = GetTickCount(); // 생성 시각 저장
	m_bTargeting = false;


	m_eMonsterType = MONSTER_NORMAL;  //몬스터 타입 초기값 일반 
	// m_eMonsterType = MONSTER_BOSS;  //몬스터 타입 초기값 일반 

	m_pBullet = nullptr;  // m_pBullet은 nullptr로 초기화 

	m_dwShootTime = GetTickCount();    //시간 함수 
	m_fShootInterval = 1000.f;   //일반 몬스터 사격간격 초기값 1.5초   

	// 체력 시스템 초기화
	m_ihp = 1;      // 일반 몬스터는 1방
	m_iMaxHP = 1;
	m_iAnimFrameIndex = 0.f;
	m_pHomingBullet = nullptr;
	m_fAngle = 1.f;
}

CMonster::~CMonster()
{
	Release();
}


void CMonster::Initialize()
{
	if (m_eMonsterType == MONSTER_BOSS)
	{
		m_tInfo.fCX = PLAYERCX; //300.f
		m_tInfo.fCY = PLAYERCY;
		m_fSpeed = 0.f;  //고정 
		m_fShootInterval = 800.f; //보스 몬스터 사격 간격 0.8초 
		m_tInfo.fX = WINCX / 2.f;  // 화면 가로 중앙 (350)
		m_tInfo.fY = 300.f;
		// 레이저 시스템 초기화
		m_bLaserMode = false;      // 처음엔 레이저 모드 아님
		m_bLaserUsed = false;      // 아직 레이저 안씀
		m_dwLaserStartTime = 0;    // 시작시간 0
		m_dwLaserDuration = 6000;  // 5초간 지속
		m_dwLaserBulletTime = 0;
		if (m_ihp <= 1)
		{
			m_ihp = 50;  //체력 50 
			m_iMaxHP = 50;

		}
		//위치 저장 
		m_fOriginalX = m_tInfo.fX;
		m_fOriginalY = m_tInfo.fY;

	}
	//일반 몬스터 
	else
	{
		// 일반 몬스터 설정
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 40.f;
		m_fSpeed = 1.5f;
		m_ihp = 1;                  // 일반 몬스터는 1방에 죽음
		m_iMaxHP = 1;

	}







}


int CMonster::Update()  //업데이트 관리 
{
	if (m_bDead)
		return DEAD;
	__super::Update_Rect();

	if (m_eMonsterType == MONSTER_BOSS)
	{
		Update_Boss();;
	}
	else
	{
		Update_Normal();
	}








	return NOEVENT;
}

void CMonster::Late_Update()
{
	if (m_eMonsterType == MONSTER_NORMAL)  //몬스터 타입 일반일시 
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));  //따라오게 
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}







}

void CMonster::Render(HDC hDC)
{
	//Update_Normal

		// 몬스터 몸체 (동그라미)
	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//멤버 변수로 float 형의 m_iAnimFrameIndex 만들어주기
//Render 함수 안에 넣어주면 됨
	if (m_eMonsterType == MONSTER_BOSS)
	{//Update_Boss
	// 브러시 생성

	
		CRenderMgr::BossMonsterRender(hDC, m_tInfo, m_tRect);


		//레이져 렌더링

		if (m_bLaserMode)
		{
			// 레이저 끝점 계산 (화면 끝까지)

			for (int i = 210; i <360; i += 30)  // 30도씩 12방향
			{
				// 각 방향의 끝점 계산
				int iEndX = m_tInfo.fX + 1000 * cosf(i * (PI / 180.f));
				int iEndY = m_tInfo.fY - 1000 * sinf(i * (PI / 180.f));


				// 1단계: 가장 굵은 외곽선 (어두운 빨강)
				HPEN hOuterPen = CreatePen(PS_SOLID, 30, RGB(255, 10, 10));
				HPEN hOldPen = (HPEN)SelectObject(hDC, hOuterPen);
				MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, NULL);
				LineTo(hDC, iEndX, iEndY);
				SelectObject(hDC, hOldPen);
				DeleteObject(hOuterPen);

				// 2단계: 중간 두께 (밝은 빨강)
				HPEN hMiddlePen = CreatePen(PS_SOLID, 15, RGB(255, 30, 30));
				hOldPen = (HPEN)SelectObject(hDC, hMiddlePen);
				MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, NULL);
				LineTo(hDC, iEndX, iEndY);
				SelectObject(hDC, hOldPen);
				DeleteObject(hMiddlePen);

				// 3단계: 핵심 레이저 (하얀색)
				HPEN hCorePen = CreatePen(PS_SOLID, 8, RGB(255, 255, 255));
				hOldPen = (HPEN)SelectObject(hDC, hCorePen);
				MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, NULL);
				LineTo(hDC, iEndX, iEndY);
				SelectObject(hDC, hOldPen);
				DeleteObject(hCorePen);

				// 4단계: 가장 안쪽 코어 (노란색)
				HPEN hInnerPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
				hOldPen = (HPEN)SelectObject(hDC, hInnerPen);
				MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, NULL);
				LineTo(hDC, iEndX, iEndY);
				SelectObject(hDC, hOldPen);
				DeleteObject(hInnerPen);

				// 🔥 레이저 시작점에 이펙트 원 그리기 (차징 느낌)
				HBRUSH hGlowBrush = CreateSolidBrush(RGB(255, 100, 100));
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hGlowBrush);

				// 외곽 글로우
				int iGlowRadius = 25;
				Ellipse(hDC,
					m_tInfo.fX - iGlowRadius, m_tInfo.fY - iGlowRadius,
					m_tInfo.fX + iGlowRadius, m_tInfo.fY + iGlowRadius);

				SelectObject(hDC, hOldBrush);
				DeleteObject(hGlowBrush);


				// 내부 코어 원
				HBRUSH hCoreBrush = CreateSolidBrush(RGB(255, 255, 0));
				hOldBrush = (HBRUSH)SelectObject(hDC, hCoreBrush);

				int iCoreRadius = 12;
				Ellipse(hDC,
					m_tInfo.fX - iCoreRadius, m_tInfo.fY - iCoreRadius,
					m_tInfo.fX + iCoreRadius, m_tInfo.fY + iCoreRadius);

				SelectObject(hDC, hOldBrush);
				DeleteObject(hCoreBrush);
			}
			CRenderMgr::BossMonsterMadFaceRender(hDC, m_tInfo, m_tRect);
		}
		if (!m_bLaserMode && m_pBullet) {
			for (auto& pBullet : *m_pBullet)
				pBullet->Render(hDC);
		}

	}
	//일반몬스터 
	else
	{
		m_iAnimFrameIndex += 0.5f;

		CRenderMgr::NormalMonsterRender(hDC, m_tInfo, m_iAnimFrameIndex);

		// 포신 그리기 (플레이어 방향)
		m_iMx = m_tInfo.fX + 30 * cosf(m_fAngle * (PI / 180.f));
		m_iMy = m_tInfo.fY - 30 * sinf(m_fAngle * (PI / 180.f));

		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
		// 포신 그리기
		MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, NULL);
		LineTo(hDC, m_iMx, m_iMy);

		SelectObject(hDC, hOldPen);
		DeleteObject(hPen);


	}
	if (g_bHitbox)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 1 pixel 펜 생성
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen); // hDC에 펜 저장
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH)); //NULL브러쉬로 안쪽 투명화

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); // m_tRect에서 좌표값받아와서 사각형 히트박스 생성

		SelectObject(hDC, hOldPen);

		DeleteObject(hPen); //펜 다쓰고 해제(메모리 누수 방지용)
	}

}




void CMonster::Update_Boss()
{

	// 보스: 움직이지 않고 제자리에서 공격만
	m_tInfo.fX = m_fOriginalX;  // 원래 위치 고정
	m_tInfo.fY = m_fOriginalY;  // 원래 위치 고정

	// 플레이어 방향 계산 좌표고정 
	if (m_pTarget)
	{
		float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fDiagonal > 1.0f)
		{
			m_fAngle = atan2f(-fHeight, fWidth) * (180.f / PI);
		}


	//레이저 히든 
	float fHealthPercent = (float)m_ihp / (float)m_iMaxHP * 100.f;
	if (fHealthPercent <= 20.f && !m_bLaserUsed && !m_bLaserMode)
	{
		m_bLaserMode = true;           // 레이저 모드 켜기
		m_bLaserUsed = true;           // 이제 썼다고 표시 (다시 못씀)
		m_dwLaserStartTime = GetTickCount(); // 시작시간 기록
	}
		}

	if (!m_bLaserMode && m_pTarget)
	{
		float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fDiagonal > 1.0f)
		{
			m_fAngle = atan2f(-fHeight, fWidth) * (180.f / PI);
		}
	}

	// 레이저 모드일때
	if (m_bLaserMode)
	{
		// 5초 지났으면 레이저 끝
		if (GetTickCount() - m_dwLaserStartTime > m_dwLaserDuration)
		{
			m_bLaserMode = false;
		}
		else // 아직 6초 안지났으면 레이저 계속
		{
			
			if (GetTickCount() - m_dwLaserBulletTime > 200)  // 200ms = 0.2초
			{
				for (int i = 210; i < 360; i += 30)  // 12방향
				{
					for (int j = 1; j <= 3; ++j)  //
					{
						float fDistance = j * 80.f;  // 간격도 80픽셀로 늘림
						float fLaserX = m_tInfo.fX + fDistance * cosf(i * (PI / 180.f));
						float fLaserY = m_tInfo.fY - fDistance * sinf(i * (PI / 180.f));

						CObj* pBullet = CAbstractFactory<CMonster_Bullet>::Create_Obj(fLaserX, fLaserY);
						pBullet->Set_Angle(i);
						if (m_pBullet)
							m_pBullet->push_back(pBullet);
					}
				}
				m_dwLaserBulletTime = GetTickCount();  // 시간 갱신
			}
		}
	}
	else        // 레이저 아닐때만 기존 패턴
	{
		// 기존 보스 패턴 코드...
		if (GetTickCount() - m_dwShootTime > m_fShootInterval)
		{
			int iPattern = Get_Random_Pattern();
			switch (iPattern)
			{
			case 0: shoot_Normal(); break;
			case 1: Shoot_FiveWay(); break;
			}
			Try_Special_Pattern();
			m_dwShootTime = GetTickCount();
		}
	}

	//총알 업데이트 
	if (m_pBullet)
	{
		for (auto iter = m_pBullet->begin(); iter != m_pBullet->end(); )
		{
			int iResult = (*iter)->Update();
			if (iResult == DEAD)
			{
				delete (*iter);
				iter = m_pBullet->erase(iter);
			}
			else
			{
				(*iter)->Late_Update();
				++iter;
			}
		}
	}
}



void CMonster::Update_Normal()
{

	//Update_Normal 
	// 플레이어 방향 계산 좌표고정 
	if (m_pTarget)
	{
		float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;  //나 자신 중심으로 타겟 x,y 좌표 타겟지정 
		float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //거리계산 

		if (fDiagonal > 1.0f)
		{
			m_fAngle = atan2f(-fHeight, fWidth) * (180.f / PI); //atan2f 
		}
	}

	//총쏘기 (3초) 자동 
	if (GetTickCount() - m_dwShootTime > m_fShootInterval)
	{
		shoot_Normal();
		m_dwShootTime = GetTickCount();
	}
	//총알 업데이트 
	if (m_pBullet)
	{
		for (auto iter = m_pBullet->begin(); iter != m_pBullet->end(); )
		{
			int iResult = (*iter)->Update();
			if (iResult == DEAD)
			{
				delete (*iter);
				iter = m_pBullet->erase(iter);
			}
			else
			{
				(*iter)->Late_Update();
				++iter;
			}
		}
	}



}


void CMonster::Shoot_Homing()  //유도탄 
{
	if (!m_pHomingBullet) return;

	for (int i = -1; i <= 1; ++i)
	{
		float fScrewAngle = m_fAngle + (i * 30.f); //-30 0 30 3갈래 
		CObj* pScrew = CAbstractFactory<CScrewBullet>::Create_Obj(m_tInfo.fX, m_tInfo.fY);  // 보스 중심
		pScrew->Set_Angle(fScrewAngle);
		// 타겟 지정 추가
		if (m_pTarget)
			pScrew->Set_target(m_pTarget); //플레이어 타겟 지정
		m_pHomingBullet->push_back(pScrew); //푸쉬 
	}
}

int CMonster::Get_Random_Pattern()
{
	return rand() % 2;

}
void CMonster::Try_Special_Pattern()  // 전방향 공격 패턴+연사 
{

	int iSpecial = rand() % 100;  // 0~99 랜덤 값 생성

	if (iSpecial < 15)        // 15% 확률 (0~14) - 유도탄
	{
		Shoot_Homing();  // 단팥빵 유도탄 
	}
	else if (iSpecial >= 15 && iSpecial < 45)   // 30% 확률 (15~44) - 십자 공격
	{
	

		// 십자 모양 (상하좌우 + 대각선)
		int angles[] = { 0, 45, 90, 135, 180, 225, 270, 315 };
		for (int angle : angles)
		{
			CObj* pBullet = CAbstractFactory<CMonster_Bullet>::Create_Obj(m_tInfo.fX, m_tInfo.fY);
			pBullet->Set_Angle(angle);
			if (m_pBullet)
				m_pBullet->push_back(pBullet);
		}
	}
	else if (iSpecial >= 45)   // 55% 확률 (45~99) - 전방향 공격
	{
		// 360도 전방향 공격 (12방향)
		for (int i = 0; i < 360; i += 30)
		{
			CObj* pBullet = CAbstractFactory<CMonster_Bullet>::Create_Obj(m_tInfo.fX, m_tInfo.fY);
			pBullet->Set_Angle(i);
			if (m_pBullet)
				m_pBullet->push_back(pBullet);
		}
		// 5발 연속 (약간씩 각도 다르게)
		for (int i = 0; i < 5; ++i)
		{
			float fAngle = m_fAngle + (rand() % 21 - 10);  // -10~+10도 랜덤
			CObj* pBullet = CAbstractFactory<CMonster_Bullet>::Create_Obj(m_tInfo.fX, m_tInfo.fY);
			pBullet->Set_Angle(fAngle);
			if (m_pBullet)
				m_pBullet->push_back(pBullet);
		}
	}
	// 나머지는 아무것도 안함 (대기시간)
}
void CMonster::shoot_Normal()  //일반 타입 총알
{
	CObj* pBullet = CAbstractFactory<CMonster_Bullet>::Create_Obj(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Angle(m_fAngle);
	if (m_pBullet) {
		m_pBullet->push_back(pBullet); // 전역 리스트에만 추가
	}
}

void CMonster::Take_Damage(int iDamage)
{
	m_ihp -= iDamage; //데미지 입음

	if (m_ihp <= 0)
	{
		m_bDead = true;
		//TODO 스테이지 매니저에 죽으면 킬카운트 하세여 
	}

}

void CMonster::Shoot_FiveWay()
{  // 5갈래 총알 (플레이어 방향 기준으로 20도씩)
	for (int i = -2; i <= 2; ++i)
	{
		float fBulletAngle = m_fAngle + (i * 20.f);  // -40, -20, 0, 20, 40도
		CObj* pBullet = CAbstractFactory<CMonster_Bullet>::Create_Obj(m_tInfo.fX, m_tInfo.fY);
		pBullet->Set_Angle(fBulletAngle);
		if (m_pBullet)
			m_pBullet->push_back(pBullet);  // 전역 리스트에만 추가
	}
}

void CMonster::Release()

{

}

