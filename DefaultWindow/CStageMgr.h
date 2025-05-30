#pragma once
class CObj;
class CMonster;
class CStageMgr
{
public:
	static CStageMgr* GetInst()
	{
		return &StageMgr;
	}

	int GetStage()
	{
		return m_iStage;
	}

	void SetStage(int _iStageValue)
	{
		_iStageValue = m_iStage;
	}
public:
	void	SpawnMonsters(int count);
	void	CopyInitialize(list<CObj*> objList[OBJ_END]);
	void	CheckAndSpawnMonsters(list<CObj*> m_ObjList[OBJ_END]);
	void	SpawnBossMonster();
	void	AddKillCount(int _iValue);
	void	SetMonsterSpawned(int _iValue)
	{
		m_monstersSpawned = _iValue;
	}

	/*화면에 스폰된 몬스터 수를 얻는 함수*/
	int  GetMonsterSpawned(int _iValue)
	{
		return m_monstersSpawned;
	}
	
	/*보스의 주소를 얻는 함수.*/
	CMonster* GetBoss() const 
	{ 
		return pBoss; 
	}

	void SetBoss(CMonster* pNewBoss)
	{
		pBoss = pNewBoss;
	}

	void SetBossClear(bool _bIsClear)
	{
		m_bBossClear = _bIsClear;
	}

	bool GetBossClear() const
	{
		return m_bBossClear;
	}

	bool SetBossSpawned(bool _bBossSpawned)
	{
		m_bBossSpawned = _bBossSpawned;
	}

	bool GetBossSpawned()
	{
		return m_bBossSpawned;
	}

	void ResetStage();

	void UpdateStageMonsters(float shootInterval, int totalMonsters, list<CObj*> m_ObjList[OBJ_END]);
	
protected:

private:
	CStageMgr() = default;
	~CStageMgr() = default;
	CStageMgr& operator=(CStageMgr& _Other) = delete;
	CStageMgr(CStageMgr& _Other) = delete;

	static CStageMgr StageMgr;
	CMonster* pBoss = nullptr;

	/*현재 스테이지를 담는 변수*/
	static int m_iStage;
	/*몬스터 킬 카운트 변수*/
	static int m_KillCount;
	/*생성된 몬스터 수를 세는 변수*/
	static int m_monstersSpawned;

	bool			m_bBossSpawned = false;

	bool			m_bBossClear = false;

	list<CObj*>*	m_ObjList[OBJ_END];

};

