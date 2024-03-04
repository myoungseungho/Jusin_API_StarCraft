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
	DIR_UP,
	DIR_RUP,
	DIR_RIGHT,
	DIR_RDOWN,
	DIR_DOWN,
	DIR_LDOWN,
	DIR_LEFT,
	DIR_LUP,
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
	DYNAMIC_OBJ_SCV,
	DYNAMIC_OBJ_MARINE,
	DYNAMIC_OBJ_FIREBAT,
	DYNAMIC_OBJ_MEDIC,
	DYNAMIC_OBJ_TANK,
	DYNAMIC_OBJ_END
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
	COLLECTION_STATE,
	SIEGEMODE_STATE,
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

enum UI_BUILDINGSTATE
{
	UI_STATIC_OBJ_CENTER,
	UI_STATIC_OBJ_DEPOT,
	UI_STATIC_OBJ_BARRACK,
	UI_STATIC_OBJ_FACTORY,
	UI_STATIC_OBJ_STARPORT,
	UI_STATIC_OBJ_END
};

enum FACTIONSTATE
{
	FACTION_NON, // 어느 쪽에도 속하지 않음
	FACTION_ALLY, // 아군
	FACTION_ENEMY, // 적군
	FACTION_RESOURCE, //자원
	FACTION_END
};

enum UIOBJECTTYPE {
	UI_OBJECT_MOUSE,
	UI_OBJECT_ICON,
	UI_OBJECT_WIRE,
	UI_OBJECT_BUILD,
	UI_OBJECT_BACKGROUND,
	UI_OBJECT_MAIN,
	UI_OBJECT_DISPLAY,
	UI_OBJECT_END
};

enum ICONSTATE
{
	ICON_MOVE,
	ICON_STOP,
	ICON_ATTACK,
	ICON_BUILD,
	ICON_ADVANCED_BUILD,
	ICON_SIEGE_MODE,
	ICON_DEFAULT_MODE,
	ICON_CENTER,
	ICON_BARRACK,
	ICON_DEPOT,
	ICON_FACTORY,
	ICON_STARPORT,
	ICON_SCV,
	ICON_MARINE,
	ICON_FIREBAT,
	ICON_MEDIC,
	ICON_TANK,
	ICON_END
};

enum WIREBIGSTATE
{
	WIRE_SCV_BIG,
	WIRE_MARINE_BIG,
	WIRE_FIREBAT_BIG,
	WIRE_MEDIC_BIG,
	WIRE_TANK_BIG,
	WIRE_CENTER_BIG,
	WIRE_DEPOT_BIG,
	WIRE_BARRACK_BIG,
	WIRE_FACTORY_BIG,
	WIRE_STARPORT_BIG,
	WIRE_BIG_END
};

enum WIRESMALLSTATE
{
	WIRE_SCV_SMALL,
	WIRE_MARINE_SMALL,
	WIRE_FIREBAT_SMALL,
	WIRE_MEDIC_SMALL,
	WIRE_TANK_SMALL,
	WIRE_SMALL_END
};

enum COLLISIONSTATE
{
	COLLISION_NOT,
	COLLISION_OK,
	COLLISION_END
};

enum SOUNDSTATE
{
	SOUND_BASIC,
	SOUND_ATTACK,
	SOUND_DIE,
	SOUND_BUILD,
	SOUND_BUILD_COMPLETE,
	SOUND_READY,
	SOUND_END
};

typedef struct tagStat
{
	int m_Hp;
	int m_Mp;
	int m_Attack;
	float m_AttackRange;
	float m_DetectionRange;
	float m_fSpeed;
	int m_MaxHp;
	int m_MaxMp;
	TCHAR m_Name[256]; // 유닛의 이름을 위한 필드 추가
}STAT;

typedef struct tagResource
{
	int m_Mineral;
	int m_Gas;
	int m_People;
	int m_MaxPeople;
}MINERALGASPEOPLE;



enum CHANNELID
{
	SOUND_BGM,
	SOUND_SCV_WALK,
	SOUND_SCV_READY,
	SOUND_SCV_BUILD,
	SOUND_SCV_BUILD_COMPLETE,
	SOUND_SCV_DIE,
	SOUND_MARINE_WALK,
	SOUND_MARINE_READY,
	SOUND_MARINE_ATTACK,
	SOUND_MARINE_DIE,
	SOUND_FIREBAT_WALK,
	SOUND_FIREBAT_READY,
	SOUND_FIREBAT_ATTACK,
	SOUND_FIREBAT_DIE,
	SOUND_MEDIC_WALK,
	SOUND_MEDIC_READY,
	SOUND_MEDIC_DIE,
	SOUND_TANK_WALK,
	SOUND_TANK_READY,
	SOUND_TANK_ATTACK,
	SOUND_TANK_DIE,
	MAXCHANNEL
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

typedef struct tagKeyFrame
{
	wchar_t* m_FrameArrayWalkKey[DIR_END];
	wchar_t* m_FrameArrayAttackKey[DIR_END];
	wchar_t* m_FrameBulletAttackKey[DIR_END];
	wchar_t* m_FrameTankPosinKey[DIR_END];
	wchar_t* m_FrameTankPosinLaunchKey[DIR_END];
	wchar_t* m_FrameSiegeTankKey[DIR_END];

	map<wchar_t*, FRAME> _mapKeyFrame;
}KEYANDFRAME;


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
