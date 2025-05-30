#pragma once

#define	WINCX 700
#define	WINCY 800

// 배경 색깔 스카이 블루
#define SKY_BLUE    RGB(135, 206, 235)

#define	PLAYERLIFE 3

#define PURE = 0

#define NOEVENT 0
#define DEAD    1 
#define PI 3.141592f
#define PLAYERCX 300.f  //도라에몽 
#define PLAYERCY 300.f


enum Monster_type
{  
	MONSTER_NORMAL,
	MONSTER_BOSS,


};


enum DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LUP,
	RUP,
	END
};

enum OBJID
{
	OBJ_PLAYER,
	OBJ_BULLET,
	OBJ_MONSTER,
	OBJ_MOUSE,
	OBJ_SHIELD,
	OBJ_MONSTER_BULLET,
	OBJ_HOMING_BULLET,
	OBJ_BOSS,
	OBJ_CRASHEFFECT,
    OBJ_END

	
};

enum BULLET_TYPE
{
	BULLET_NORMAL,
	BULLET_SPIRAL,
	BULLET_END
};

enum LEFTRIGHT
{
	LR_LEFT,
	LR_RIGHT,
	LR_END
};


typedef struct tagInfo
{
	float	fX;		// 중점 X,Y
	float	fY;
	float	fCX;	// 가로, 세로 길이
	float	fCY;	

}INFO;

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}




extern HWND g_hWnd;
extern bool g_bHitbox;