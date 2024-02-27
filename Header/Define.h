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

#define			MOVE_NOTOK	0
#define			MOVE_OK		1

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
	DYNAMIC_OBJ_END
};


enum UI_OBJID
{
	UI_OBJ_MOUSE,
	UI_OBJ_ICON,
	UI_OBJ_MAINUI,
	UI_OBJ_END
};

enum RENDERID
{
	RENDER_BACKGROUND,
	RENDER_GAMEOBJECT,
	RENDER_BUILDING,
	RENDER_UI,
	RENDER_END
};

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_END };

enum STATEID
{
	NON_STATE = -1,
	IDLE_STATE,
	WALK_STATE,
	ATTACK_STATE,
	DIE_STATE,
	BUILD_STATE,
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

enum BUILDINGSTATE
{
	STATIC_OBJ_CENTER,
	STATIC_OBJ_DEPOT,
	STATIC_OBJ_BARRACK,
	STATIC_OBJ_FACTORY,
	STATIC_OBJ_STARPORT,
	STATIC_OBJ_MINERAL,
	STATIC_OBJ_END
};

enum FACTIONSTATE
{
	FACTION_NON, // ��� �ʿ��� ������ ����
	FACTION_ALLY, // �Ʊ�
	FACTION_ENEMY, // ����
	FACTION_RESOURCE, //�ڿ�
	FACTION_END
};

enum ICONSTATE
{
	ICON_MOVE,
	ICON_STOP,
	ICON_ATTACK,
	ICON_BUILD,
	ICON_ADVANCED_BUILD,
	ICON_CENTER,
	ICON_BARRACK,
	ICON_DEPOT,
	ICON_FACTORY,
	ICON_STARPORT,
	ICON_END
};

enum COLLISIONSTATE
{
	COLLISION_NOT,
	COLLISION_OK,
	COLLISION_END
};

typedef struct tagInfo
{
	float		fX;			// ���� X
	float		fY;			// ���� Y
	float		fCX;		// ���� ������
	float		fCY;		// ���� ������

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
	int		iFrameStart;	// ������ ����� ���ΰ�
	int		iFrameEnd;		// ������ ����� ���ΰ�
	int		iMotion;		// ���η� �����ϴ� �ε���
	DWORD	dwSpeed;		// �ִϸ��̼� ���� �ӵ�
	DWORD	dwTime;			// ���� �ֱ�

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
