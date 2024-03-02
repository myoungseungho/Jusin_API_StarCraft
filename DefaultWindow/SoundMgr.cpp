#include "stdafx.h"
#include "SoundMgr.h"
#include "Define.h"

CSoundMgr* CSoundMgr::m_pInstance = nullptr;
float g_fVolume(1.0f);
CSoundMgr::CSoundMgr()
{
	m_pSystem = nullptr;
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	// 사운드를 담당하는 대표객체를 생성하는 함수
	FMOD_System_Create(&m_pSystem);

	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();

	//PlayBGM(L"MainBgm.wav", SOUND_BGM);
	PlaySound(L"MainBgm.wav", SOUND_BGM, g_fVolume);

	m_UnitSound.resize(DYNAMIC_OBJ_END);
	for (size_t i = 0; i < DYNAMIC_OBJ_END; ++i) {
		m_UnitSound[i].resize(SOUND_END);
	}
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_ATTACK].push_back(L"EDrRep00.wav");
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_BASIC].push_back(L"TSCWht00.wav");
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_BASIC].push_back(L"TSCWht01.wav");
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_BASIC].push_back(L"TSCWht02.wav");
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_BASIC].push_back(L"TSCWht03.wav");
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_BASIC].push_back(L"TSCYes00.wav");
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_BASIC].push_back(L"TSCYes01.wav");
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_BASIC].push_back(L"TSCYes02.wav");
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_BASIC].push_back(L"TSCYes03.wav");
	m_UnitSound[DYNAMIC_OBJ_SCV][SOUND_DIE].push_back(L"TSCDth00.wav");

	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_ATTACK].push_back(L"TMaFir00.wav");
	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_BASIC].push_back(L"TMaWht00.wav");
	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_BASIC].push_back(L"TMaWht01.wav");
	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_BASIC].push_back(L"TMaWht02.wav");
	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_BASIC].push_back(L"TMaWht03.wav");
	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_BASIC].push_back(L"TMaYes00.wav");
	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_BASIC].push_back(L"TMaYes01.wav");
	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_BASIC].push_back(L"TMaYes02.wav");
	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_BASIC].push_back(L"TMaYes03.wav");
	m_UnitSound[DYNAMIC_OBJ_MARINE][SOUND_DIE].push_back(L"TMaDth00.wav");

	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_ATTACK].push_back(L"tfbFir01.wav");
	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_BASIC].push_back(L"tfbWht00.wav");
	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_BASIC].push_back(L"tfbWht01.wav");
	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_BASIC].push_back(L"tfbWht02.wav");
	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_BASIC].push_back(L"tfbWht03.wav");
	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_BASIC].push_back(L"tfbYes00.wav");
	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_BASIC].push_back(L"tfbYes01.wav");
	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_BASIC].push_back(L"tfbYes02.wav");
	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_BASIC].push_back(L"tfbYes03.wav");
	m_UnitSound[DYNAMIC_OBJ_FIREBAT][SOUND_DIE].push_back(L"TFbDth00.wav");

	m_UnitSound[DYNAMIC_OBJ_MEDIC][SOUND_BASIC].push_back(L"TMdYes00.wav");
	m_UnitSound[DYNAMIC_OBJ_MEDIC][SOUND_BASIC].push_back(L"TMdYes01.wav");
	m_UnitSound[DYNAMIC_OBJ_MEDIC][SOUND_BASIC].push_back(L"TMdYes02.wav");
	m_UnitSound[DYNAMIC_OBJ_MEDIC][SOUND_BASIC].push_back(L"TMdYes03.wav");
	m_UnitSound[DYNAMIC_OBJ_MEDIC][SOUND_DIE].push_back(L"TMdDth00.wav");

	m_UnitSound[DYNAMIC_OBJ_TANK][SOUND_ATTACK].push_back(L"TTaFir00.wav");
	m_UnitSound[DYNAMIC_OBJ_TANK][SOUND_BASIC].push_back(L"ttawht00.wav");
	m_UnitSound[DYNAMIC_OBJ_TANK][SOUND_BASIC].push_back(L"ttawht01.wav");
	m_UnitSound[DYNAMIC_OBJ_TANK][SOUND_BASIC].push_back(L"ttawht02.wav");
	m_UnitSound[DYNAMIC_OBJ_TANK][SOUND_BASIC].push_back(L"ttawht03.wav");
	m_UnitSound[DYNAMIC_OBJ_TANK][SOUND_DIE].push_back(L"TTaDth00.wav");
}
void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}




void CSoundMgr::PlaySound(TCHAR* pSoundKey, CHANNELID eID, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(),
		[&](auto& iter)->bool
		{
			return !lstrcmp(pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;

	if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[eID]);
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(TCHAR* pSoundKey, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
		{
			return !lstrcmp(pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[SOUND_BGM]);
	FMOD_Channel_SetMode(m_pChannelArr[SOUND_BGM], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pChannelArr[SOUND_BGM], fVolume);
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::StopSound(CHANNELID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0; i < MAXCHANNEL; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::SetChannelVolume(CHANNELID eID, float fVolume)
{
	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::LoadSoundFile()
{
	// _finddata_t : <io.h>에서 제공하며 파일 정보를 저장하는 구조체
	_finddata_t fd;

	// _findfirst : <io.h>에서 제공하며 사용자가 설정한 경로 내에서 가장 첫 번째 파일을 찾는 함수
	long handle = _findfirst("../Sound/*.*", &fd);

	if (handle == -1)
		return;

	int iResult = 0;

	char szCurPath[128] = "../Sound/";
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);

		strcat_s(szFullPath, fd.name);
		// "../Sound/Success.wav"

		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			// 아스키 코드 문자열을 유니코드 문자열로 변환시켜주는 함수
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		//_findnext : <io.h>에서 제공하며 다음 위치의 파일을 찾는 함수, 더이상 없다면 -1을 리턴
		iResult = _findnext(handle, &fd);
	}

	FMOD_System_Update(m_pSystem);

	_findclose(handle);
}
