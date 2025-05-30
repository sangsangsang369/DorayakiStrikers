#pragma once
#include "CObj.h"
class CMonster_Bullet :
    public CObj
{
public:
    CMonster_Bullet();
   virtual ~CMonster_Bullet();
 
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;



};



