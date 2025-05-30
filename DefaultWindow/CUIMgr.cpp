#include "pch.h"
#include "CUIMgr.h"
#include "CPlayer.h"
#include "CStageMgr.h"
#include "CScoreMgr.h"
#include "CMonster.h" // CMonster 클래스에 대한

CUIMgr CUIMgr::CuiMgr;


void CUIMgr::ShowUI(std::list<CObj*>(&objList)[OBJ_END], HDC _Hdc)
{
	// 1. 2Byte 유니코드 문자열 생성

	// 1-1 스테이지 출력 버퍼
	TCHAR	szBuf[32] = L"";
	// 1-2 라이프 출력 버퍼
	TCHAR	szLifeTextBuf[32] = L"";
	// 1-3 스코어 출력 버퍼
	TCHAR	szScoreTextBuf[32] = L"";


	// 2. 플레이어가 비어있지 않다면, 존재한다면 
	if (objList[OBJ_PLAYER].empty() == false && CStageMgr::GetInst()->GetBossClear() == false)
	{
		//2-1. Player 가져오고,
		CPlayer* pPlayer = static_cast<CPlayer*>(objList[OBJ_PLAYER].front());


		//2-1. Player 라이프 정보 셋팅,
		wsprintf(szLifeTextBuf, L"LIFE %d", pPlayer->Get_PlayerLife());

		//2-2. 스코어 정보 셋팅,
		wsprintf(szScoreTextBuf, L"SCORE %d", CScoreMgr::GetInst()->GetScore());
	}
	else if (CStageMgr::GetInst()->GetBossClear() == true)
	{
		LPCWSTR szGameClearMsg = L"Game Clear";
		int iGameClearMsgLen = lstrlenW(szGameClearMsg);

		// 문자열의 픽셀 크기 구하기
		SIZE szGameClearsize;
		GetTextExtentPoint32(_Hdc, szGameClearMsg, iGameClearMsgLen, &szGameClearsize);

		int iGameClearTextPostion_X = (WINCX - szGameClearsize.cx) / 2;
		int iGameOverTextPostion_Y = 200;
		TextOut(_Hdc, iGameClearTextPostion_X, iGameOverTextPostion_Y, szGameClearMsg, iGameClearMsgLen);

		LPCWSTR szRestartMsg = L"'R'키를 눌러 재시작 할 수 있습니다.";
		int iRestartMsgLen = lstrlenW(szRestartMsg);

		SIZE szGameRestartsize;
		GetTextExtentPoint32(_Hdc, szRestartMsg, iRestartMsgLen, &szGameRestartsize);

		int iRestartTextPostion_X = (WINCX - szGameRestartsize.cx) / 2;
		int iRestartTextPostion_Y = 500;

		TextOut(_Hdc, iRestartTextPostion_X, iRestartTextPostion_Y, szRestartMsg, iRestartMsgLen);
	}	

	// 플레이어가 없으면 게임 오버 메시지 출력
	else if (objList[OBJ_PLAYER].empty() == true && CStageMgr::GetInst()->GetBossClear() == false)
	{
		LPCWSTR szGameOverMsg	= L"GAME OVER";
		LPCWSTR szRestartMsg	= L"'R'키를 눌러 재시작 할 수 있습니다.";
		int iGameOverMsgLen		= lstrlenW(szGameOverMsg);
		int iRestartMsgLen		= lstrlenW(szRestartMsg);

		

		// 문자열의 픽셀 크기 구하기
		SIZE szGameOversize;
		SIZE szGameRestartsize;
		GetTextExtentPoint32(_Hdc, szGameOverMsg, iGameOverMsgLen, &szGameOversize);
		GetTextExtentPoint32(_Hdc, szRestartMsg, iRestartMsgLen, &szGameRestartsize);
		// 화면 가로 중앙에 출력 (예: WINCX가 전체 화면 너비)
		int iGameOverTextPostion_X = (WINCX - szGameOversize.cx) / 2;
		int iGameOverTextPostion_Y = 200;

		int iRestartTextPostion_X = (WINCX - szGameRestartsize.cx) / 2;
		int iRestartTextPostion_Y = 500;

		TextOut(_Hdc, iGameOverTextPostion_X, iGameOverTextPostion_Y, szGameOverMsg, iGameOverMsgLen);
		TextOut(_Hdc, iRestartTextPostion_X, iRestartTextPostion_Y, szRestartMsg, iRestartMsgLen);
	}
	if (CStageMgr::GetInst()->GetBossClear() == true)
	{

	}
	else
	{
		// 3.보스 스테이지가에 도달 했다면,
		if (CStageMgr::GetInst()->GetStage() == 4 && CStageMgr::GetInst()->GetBossClear() == false)
		{
			// 3-1.보스 스테이지로 정보 셋팅,
			wsprintf(szBuf, L"STAGE %s", L"BOSS STAGE");
			CUIMgr::DrawBossHpBar(_Hdc, CStageMgr::GetInst()->GetBoss());
		}
		else if(CStageMgr::GetInst()->GetStage() != 4)
		{
			// 3-2.아니라면 일반 스테이지로 정보 셋팅,
			wsprintf(szBuf, L"STAGE %d", CStageMgr::GetInst()->GetStage() + 1);
		}
	}

	// 4. 텍스트의 크기를 정하는 SIZE 변수 선언
	SIZE szTextSize;

	// 4-1. 텍스트의 실제 픽셀 길이를 구해 중앙 정렬하는 함수
	GetTextExtentPoint32(_Hdc, szBuf, lstrlen(szBuf), &szTextSize);

	// 5-1. 스테이지 TextOut 포지션
	int iText_X_Positon = (WINCX - szTextSize.cx) / 2; // X 포지션 계산
	int iText_Y_Positon = 20; // Y는 20으로

	// 5-2. 라이프 TextOut 포지션
	int	iLifeText_Y_Poston = (WINCY - 100); // X 포지션 계산
	int iLifeText_X_Positon = (WINCX - 650); // Life Text 포지션 계산

	// 5-3. 스코어 TextOut 포지션
	int iScoreText_Y_Postion = (WINCY - 700);
	int iScoreText_X_Postion = (WINCX - 650);

	// 6. TextOut 출력
	TextOut(_Hdc, iText_X_Positon, iText_Y_Positon, szBuf, lstrlen(szBuf));
	TextOut(_Hdc, iLifeText_X_Positon, iLifeText_Y_Poston, szLifeTextBuf, lstrlen(szLifeTextBuf));
	TextOut(_Hdc, iScoreText_X_Postion, iScoreText_Y_Postion, szScoreTextBuf, lstrlen(szScoreTextBuf));	
}

void CUIMgr::DrawBossHpBar(HDC _hDC, CMonster* pBoss)
{
	if (pBoss == nullptr)
	{
		return;
	}// 초기화

	int iHP = pBoss->Get_Boss_HP();        // 현재 체력
	int iHPFULL = 50;     // 최대 체력

	int iBarWidth = 400;     // bar 길이
	int iBarHeight = 20;     // 높이
	int iBarX = (WINCX - iBarWidth) / 2; // 중앙 위치
	int iBarY = 45;          // 상단 위치


		
	
	HBRUSH hBkBrush = CreateSolidBrush(RGB(100, 100, 100)); // 디졋을때 RGB 빈칸
	RECT rcBack = { iBarX, iBarY, iBarX + iBarWidth, iBarY + iBarHeight };
	
	FillRect(_hDC, &rcBack, hBkBrush);
	DeleteObject(hBkBrush);
	
	int iHpBarLen = (int)((float)iHP / iHPFULL * iBarWidth); //hp bar 길이 추적
	
	HBRUSH hHpBrush = CreateSolidBrush(RGB(255, 85, 145)); // 개피일때 RGB 빨강
	RECT rcHp = { iBarX, iBarY, iBarX + iHpBarLen, iBarY + iBarHeight };
	
	FillRect(_hDC, &rcHp, hHpBrush);
	DeleteObject(hHpBrush);
	
}