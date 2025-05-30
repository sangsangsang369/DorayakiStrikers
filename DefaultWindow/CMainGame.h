#pragma once

#include "Define.h"
#include "CPlayer.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render();
	void	Release();

public:
	void	ResetGame();

private:
	HDC		m_DC;

	TCHAR	m_szFPS[32];
	int		m_iFPS;
	DWORD	m_dwTime;

	list<CObj*>	m_ObjList[OBJ_END];

	// 백버퍼용 메모리 DC
	HDC m_hMemDC = nullptr;

	// 백버퍼용 비트맵
	HBITMAP	m_hBackBitmap = nullptr;

	// 이전 비트맵(리소스 해제용)
	HBITMAP m_hOldBitmap = nullptr;
};

// 숙제 1. 삼각 함수가 무엇인지 공부하라
// 숙제 2. 플레이어를 중심으로 회전하는 포신을 구현하라
// 숙제 3. 포신이 바라보는 방향으로 이동하고, 총알이 나가도록 만들어라.


/////////////////////////////////////////////////////////////////////

// 디자인 패턴 : 코드의 구조들을 일정한 형태로 만들어 재사용하기 편리하게 만든 패턴
// https://refactoring.guru/ko/design-patterns

// 1. 추상 팩토리 패턴 : 객체를 생성하는 방법을 추상화시킨 패턴
// 2. 반복자 패턴 : 내부 표현 방식은 공개하지 않고, 순차적인 방법을 제공하는 패턴

