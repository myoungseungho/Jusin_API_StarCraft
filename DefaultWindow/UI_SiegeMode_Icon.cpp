#include "stdafx.h"
#include "UI_SiegeMode_Icon.h"
#include "BmpMgr.h"
CUI_SiegeMode_Icon::CUI_SiegeMode_Icon()
{
    InsertBmpFile();
}

CUI_SiegeMode_Icon::~CUI_SiegeMode_Icon()
{
    Release();
}

void CUI_SiegeMode_Icon::Initialize()
{
    //ó�� ũ�� ����
    m_tInfo.fCX = 40.f;
    m_tInfo.fCY = 40.f;
    __super::Update_Rect();

    m_pFrameKey = L"SiegeMode_Image";
    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 0;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 200;
    m_tFrame.dwTime = GetTickCount();

    m_eRender = RENDER_UI;
}

int CUI_SiegeMode_Icon::Update()
{
    if (m_bDead)
        return OBJ_DEAD;
    return 0;
}

void CUI_SiegeMode_Icon::Late_Update()
{
}

void CUI_SiegeMode_Icon::Render(HDC hDC)
{
    GdiTransparentBlt(
        hDC,		// (���� ����)���������� �׸��� �׸� DC ����
        m_tRect.left,	// ���� ���� �̹����� ����, ����
        m_tRect.top,
        (int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
        (int)m_tInfo.fCY,
        Get_HDC(),		// ��Ʈ���� ������ �ִ� DC
        (int)m_tInfo.fCX * m_tFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
        (int)m_tInfo.fCY * m_tFrame.iMotion,
        (int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
        (int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
        RGB(0, 0, 0));	// ������ ���� ��
}

void CUI_SiegeMode_Icon::Release()
{
}

UIOBJECTTYPE CUI_SiegeMode_Icon::GetType() const
{
    return UI_OBJECT_ICON;
}

int CUI_SiegeMode_Icon::GetDetailType() const
{
    return ICON_SIEGE_MODE;
}

void CUI_SiegeMode_Icon::InsertBmpFile()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/SiegeMode_Image.bmp", L"SiegeMode_Image");
}
