#pragma once
#include "CObj.h"
#include "CRenderMgr.h"

// 나선형으로 휘어지는 총알 클래스
class CScrewBullet : public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Set_target(CObj* pTarget) { m_pTarget = pTarget; }
private:
	POINT m_tCenter;          // 중심점
	float m_fRotAngle;        // 자전 각도
	float m_fRotSpeed;        // 회전 속도 
	float m_fDistance;        // 회전 반지름
	bool m_bStart;            // 시작 중심점 
};