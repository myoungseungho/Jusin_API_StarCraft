#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			PI			3.14f

#define			TILEX		30
#define			TILEY		20

#define			TILECX		64
#define			TILECY		64

#define			OBJ_NOEVENT	 0
#define			OBJ_DEAD	 1

#define			VK_MAX		0xff

enum DIRECTION
{
	DIR_LEFT, 
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LUP,
	DIR_RUP,
	DIR_LDOWN,
	DIR_RDOWN,
	DIR_END
};

enum OBJID
{
	OBJ_SCV,
	OBJ_MARINE,
	OBJ_FIREBAT,
	OBJ_MEDIC,
	OBJ_PLAYER,
	OBJ_BULLET,
	OBJ_MONSTER,
	OBJ_MOUSE,
	OBJ_SHIELD,
	OBJ_UI,	
	OBJ_END
};

enum RENDERID
{
	RENDER_BACKGROUND,
	RENDER_GAMEOBJECT,
	RENDER_UI,
	RENDER_END
};

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_END };

enum SCVSTATE
{
	SCV_IDLE,
	SCV_WALK,
	SCV_ATTACK,
	SCV_DIE,
	SCV_END,
};

enum MARINESTATE
{
	MARINE_IDLE,
	MARINE_WALK,
	MARINE_ATTACK,
	MARINE_DIE,
	MARINE_END,
};

enum STATEID
{
	IDLE_STATE,
	WALK_STATE,
	ATTACK_STATE,
	DIE_STATE,
	END_STATE
};


typedef struct tagInfo
{
	float		fX;			// 중점 X
	float		fY;			// 중점 Y
	float		fCX;		// 가로 사이즈
	float		fCY;		// 세로 사이즈

}INFO;

typedef struct tagLinePoint
{
	float		fX;
	float		fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

typedef	struct tagLineInfo
{
	LINEPOINT	tLeft;
	LINEPOINT	tRight;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOINT& _tLeft, LINEPOINT& _tRight)
		: tLeft(_tLeft), tRight(_tRight) { }

}LINEINFO;

typedef struct tagFrame
{
	int		iFrameStart;	// 어디부터 출력할 것인가
	int		iFrameEnd;		// 어디까지 출력할 것인가
	int		iMotion;		// 세로로 증가하는 인덱스
	DWORD	dwSpeed;		// 애니메이션 동작 속도
	DWORD	dwTime;			// 갱신 주기

}FRAME;


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

extern HWND		g_hWnd;
