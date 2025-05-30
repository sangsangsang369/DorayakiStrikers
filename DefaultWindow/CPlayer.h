#pragma once
#include "CObj.h"
#include "CShield.h"
#include "CRenderMgr.h"

class CPlayer :
    public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void    Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
    void    Set_Shield(list<CObj*>* pShield) { m_pShield = pShield; }
    void    Set_CrashEffect(list<CObj*>* pCrashEffect) { m_pCrashEffect = pCrashEffect; }
    // 플레이어 라이프 가져오는 함수
    int     Get_PlayerLife()                 { return m_iPlayerLife; };
    // 스코어 가져오는 함수
    int     Get_Score()                      { return m_iScore; }
    // 플레이어 라이프 하나씩 마이너스 해주는 함수
    void    Minus_PlayerLife()               { m_iPlayerLife -= 1; }
    // 스코어 1점씩 플러스 해주는 함수
    void    Plus_Score()                     { m_iPlayerLife += 1; }
    // 스코어 매개변수만큼 플러스 해주는 함수
    void    Plus_Score(int _score)           { m_iScore += _score; }

public:   
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void    Key_Input();
    CObj*   Create_Bullet(float fAngle);
    CObj*   Create_SpiralBullet(float fAngle, int _iLR);
    CObj*   Create_Shield();
   


private:
    list<CObj*>*        m_pBullet; 
    list<CObj*>*        m_pShield;
    list<CObj*>*        m_pCrashEffect;

    int                 m_iPlayerLife;
    int                 m_iScore;

    POINT               m_tPosin;    // 포신 끝 위치 저장
    bool                m_bPosinDir;


    DWORD               m_dwShieldStartTime;
    bool                m_bSKeyPressed;    
    bool                m_bShieldExpired;

    bool                m_bReload = false;
    bool                m_bResetRequested = false;
};

