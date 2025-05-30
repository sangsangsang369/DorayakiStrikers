#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CMonster.h"
#include "CMouse.h"
#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CUIMgr.h"

CMainGame::CMainGame() : m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	//AllocConsole();  // 콘솔창 할당

	//// 표준 출력을 콘솔로 연결
	//freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	//freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
	//freopen_s((FILE**)stdin, "CONIN$", "r", stdin);  //디버깅용 콘솔창 

	// cout 사용하려면 이것도 추가
	std::ios::sync_with_stdio(true);
	m_DC = GetDC(g_hWnd);
	// 백버퍼용 DC 생성
	m_hMemDC = CreateCompatibleDC(m_DC);
	// 화면 크기에 맞는 비트맵 생성
	m_hBackBitmap = CreateCompatibleBitmap(m_DC, WINCX, WINCY);

	// 비트맵을 메모리 DC에 선택(기존 비트맵은 나중에 해제)
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBackBitmap);

	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create_Obj());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Shield(&m_ObjList[OBJ_SHIELD]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_CrashEffect(&m_ObjList[OBJ_CRASHEFFECT]);

	//for (int i = 0; i < 3; ++i)
	//{
	//	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create_Obj(200.f * (i + 1), 140.f * (i + 1)));
	//	m_ObjList[OBJ_MONSTER].back()->Set_target(m_ObjList[OBJ_PLAYER].front());
	//}

	//m_ObjList[OBJ_MOUSE].push_back(CAbstractFactory<CMouse>::Create_Obj());

}


void CMainGame::Update()
{

	CStageMgr::GetInst()->CheckAndSpawnMonsters(m_ObjList);
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if(DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	if (m_ObjList[OBJ_PLAYER].empty() || CStageMgr::GetInst()->GetBossClear() == true)
	{
		if (GetAsyncKeyState('R') & 0x8000)
		{
			CMainGame::ResetGame();
		}
	}

	if (GetAsyncKeyState('P')) {

		g_bHitbox = !g_bHitbox;
	}
}

void CMainGame::Late_Update()
{

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Late_Update();
		}
	}

	//CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MOUSE], m_ObjList[OBJ_MONSTER]);
	//CCollisionMgr::Collision_Rect(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER]);

	//CCollisionMgr::Collision_Circle(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Coll_TwoObj(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER]); // 플레이어 총알 <-> 몬스터
	CCollisionMgr::Coll_Bullet_Boss(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET], m_ObjList[OBJ_BOSS], m_ObjList[OBJ_MONSTER_BULLET]); // 플레이어 총알 <-> 보스
	CCollisionMgr::Coll_PLMON(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]); // 플레이어 <-> 몬스터(확인)
	CCollisionMgr::Coll_Shield(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_MONSTER_BULLET]); // 쉴드 <-> 몬스터 총알
	CCollisionMgr::Coll_MOONSTER_PL(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER_BULLET], m_ObjList[OBJ_MONSTER]); //몬스터 총알 <-> 플레이어(확인)
	//CCollisionMgr::Coll_Homing(m_ObjList[OBJ_HOMING_BULLET], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Coll_PLMON(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_HOMING_BULLET]); // 플레이어 <-> 몬스터(확인)
}

void CMainGame::Render()
{
	m_iFPS++;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	// 백버퍼를 흰색으로 초기화
	PatBlt(m_hMemDC, 0, 0, WINCX, WINCY, WHITENESS);

	// 플레이어 렌더 호출

	CRenderMgr::Background(m_hMemDC);

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Render(m_hMemDC);
		}
	}
	CUIMgr::GetInst()->ShowUI(m_ObjList , m_hMemDC);
	// 문자열 함수

	// RECT	rc{ 300, 300, 400, 400 };
	// DrawText(m_DC, szBuf, lstrlen(szBuf), &rc, DT_CENTER);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);


}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_DC);

	// DC에서 비트맵을 원래대로 돌려놓음
	SelectObject(m_hMemDC, m_hOldBitmap);

	// 비트맵 해제
	DeleteObject(m_hBackBitmap);

	// 메모리 DC 해제
	DeleteDC(m_hMemDC);
		
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

}

void CMainGame::ResetGame()
{
	// 오브젝트 메모리 해제 및 리스트 클리어
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
	// 스테이지 매니저도 초기화
	CStageMgr::GetInst()->ResetStage();
	// 플레이어 재생성 등 필요한 초기화
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create_Obj());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Shield(&m_ObjList[OBJ_SHIELD]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_CrashEffect(&m_ObjList[OBJ_CRASHEFFECT]);
	//m_ObjList[OBJ_MOUSE].push_back(CAbstractFactory<CMouse>::Create_Obj());
	CStageMgr::GetInst()->SetBossClear(false);
	// 필요하다면 추가 초기화
}
