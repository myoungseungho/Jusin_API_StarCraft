#pragma once

#define			MAPCX		4096
#define			MAPCY		4096

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			PI			3.14f

#define			TILEX		128
#define			TILEY		128

#define			TILECX		32
#define			TILECY		32

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
	OBJ,
	DYNAMIC_OBJ,
	STATIC_OBJ,
	UI_OBJ,
	OBJ_END
};

enum DYNAMIC_OBJID
{
	DYANMIC_OBJ_SCV,
	DYNAMIC_OBJ_MARINE,
	DYNAMIC_OBJ_FIREBAT,
	DYNAMIC_OBJ_MEDIC,
	DYNAMIC_OBJ_TANK,
	DYNAMIC_OBJ_UI,
	DYNAMIC_OBJ_END
};

enum STATIC_OBJID
{
	STATIC_OBJ_END = 1
};

enum UI_OBJID
{
	UI_OBJ_MOUSE,
	UI_OBJ_END
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
	NON_STATE = -1,
	IDLE_STATE,
	WALK_STATE,
	ATTACK_STATE,
	DIE_STATE,
	END_STATE
};

enum MOUSESTATE
{
	MOUSE_IDLE_STATE = -1,
	MOUSE_LCLICK,
	MOUSE_RCLICK,
	MOUSE_LDRAG,
	MOUSE_END
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
