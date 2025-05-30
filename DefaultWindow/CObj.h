#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Dir(DIRECTION eDir)
	{
		m_eDir = eDir;
	}
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Dead() { m_bDead = true; }
	void        Set_target(CObj* pTarget) { m_pTarget = pTarget; }
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect()const { return m_tRect; }


public:
	CObj* Get_Target() const { return m_pTarget; }
	void Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

public:
	virtual void	Initialize()PURE;
	virtual int		Update()PURE;
	virtual void	Late_Update()PURE;
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release()PURE;

	bool		m_bDead;

protected:
	void		Update_Rect();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	float		m_fAngle;
	float		m_fSpeed;
	float		m_fDistance; 
	

	CObj* m_pTarget;


};