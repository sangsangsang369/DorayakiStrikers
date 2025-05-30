#pragma once
#include "Define.h"
#include "CStageMgr.h"

class CScoreMgr
{
public:
	static CScoreMgr* GetInst()
	{
		return &ScoreMgr;
	}

	int GetScore()
	{
		return iScore;
	}

	void SetAddScore(int _iScoreValue)
	{
		
		if (CStageMgr::GetInst()->GetStage() == 4)
		{
			if (CStageMgr::GetInst()->GetBoss() == NULL)
			{
				DebugBreak();
				return;
			}
			else
			{
				return;
			}
		}
		else
		{
			iScore += _iScoreValue;

		}
	}

	void SetScore(int _iScoreValue)
	{
		iScore = _iScoreValue;
	}

protected:

private:
	CScoreMgr() = default;
	~CScoreMgr() = default;
	CScoreMgr& operator=(CScoreMgr& _Other) = delete;
	CScoreMgr(CScoreMgr& _Other) = delete;

	static CScoreMgr ScoreMgr;
	int	iScore = 0;
};

