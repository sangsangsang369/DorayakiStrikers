#include "pch.h"
#include "Define.h"
#include "CAbstractFactory.h"
#include "CStageMgr.h"
#include "CScoreMgr.h"
#include "CMonster.h"

CStageMgr CStageMgr::StageMgr;
/*몬스터 킬 카운트 변수*/
int CStageMgr::m_KillCount = 0;

/*현재 스테이지를 담는 변수*/
int CStageMgr::m_iStage = 0;
/*생성된 몬스터 수를 세는 변수*/
int CStageMgr::m_monstersSpawned = 0;

/// <summary>
/// 랜덤 위치 배치
/// 이미 존재하는 몬스터와 너무 가까운 위치만 피해서 랜덤하게 배치하는 방법.
/// 
/// </summary>
void CStageMgr::SpawnMonsters(int count)
{
    float y = 100.f; // 몬스터가 생성될 y좌표(상단 고정)
    float minX = 40.f; // 좌측 여백
    float maxX = WINCX - 40.f; // 우측 여백

    // 랜덤 엔진 및 분포 설정
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(minX, maxX);

    for (int i = 0; i < count; ++i) 
    {
        float x = 0.0f;
        bool overlap = false;

        // 이미 존재하는 몬스터와 x좌표가 겹치지 않을 때까지 반복
        do 
        {
            x = dist(gen); // minX ~ maxX 사이의 랜덤 x좌표 생성
            overlap = false;

            for (auto* pObj : *m_ObjList[OBJ_MONSTER]) 
            {
                // 기존 몬스터와 x좌표가 40픽셀 이내면 겹침으로 간주
                if (abs(pObj->Get_Info().fX - x) < 40.f) 
                {
                    overlap = true;
                    break;
                }
            }
        } 
        while (overlap);

        // 몬스터 생성 
        CObj* pMonster = CAbstractFactory<CMonster>::Create_Obj(x, y);
        // 몬스터가 살아있다면, 타겟 지정
        if (m_ObjList[OBJ_PLAYER]->empty() == false)
        {
            pMonster->Set_target(m_ObjList[OBJ_PLAYER]->front());
        }
        else
        {
            // 타겟이 없으면 바로 삭제
            Safe_Delete(pMonster);
            continue; // 다음 몬스터 생성으로 넘어감
        }
        // 몬스터 리스트에 추가
        m_ObjList[OBJ_MONSTER]->push_back(pMonster);
        // 몬스터가 사용할 총알 리스트 지정
        dynamic_cast<CMonster*>(pMonster)->Set_Bullet(m_ObjList[OBJ_MONSTER_BULLET]);
        
    }
}

void CStageMgr::SpawnBossMonster()
{
    //1.  리스트 포인터가 nullptr이면 먼저 할당
    if (!m_ObjList[OBJ_BOSS])
    {
        m_ObjList[OBJ_BOSS] = new std::list<CObj*>();
    }

    //2. 보스 몬스터 생성 (중앙 상단)
    float x = WINCX * 0.5f;
    float y = 100.f;

    //3. CMonster 생성 및 타입 지정
    pBoss = new CMonster();
    pBoss->set_MonsterType(MONSTER_BOSS);
    pBoss->Set_Pos(x, y);
    pBoss->Initialize();

    //4. 타겟 지정
    if (m_ObjList[OBJ_PLAYER]->empty() == false)
    {
         pBoss->Set_target(m_ObjList[OBJ_PLAYER]->front());
    }
    else
    {
        // 타겟이 없으면 보스 삭제 후 함수 종료
        Safe_Delete(pBoss);
        return;
    }

    //5. 리스트에 추가
    m_ObjList[OBJ_BOSS]->push_back(pBoss);
	// 몬스터가 사용할 총알 리스트 지정
	dynamic_cast<CMonster*>(pBoss)->Set_Bullet(m_ObjList[OBJ_MONSTER_BULLET]);
    //유도탄 총알 리스트 지정 
    dynamic_cast<CMonster*>(pBoss)->Set_Homing(m_ObjList[OBJ_HOMING_BULLET]);
}

void CStageMgr::CopyInitialize(list<CObj*> objList[OBJ_END])
{
    for (int i = 0; i < OBJ_END; ++i)
    {
        this->m_ObjList[i] = &objList[i];
    }
}

void CStageMgr::CheckAndSpawnMonsters(list<CObj*> m_ObjList[OBJ_END])
{
    /*m_ObjList 주소 카피하는 초기화 함수*/
    CStageMgr::CopyInitialize(m_ObjList);

    static const int stageMonsterCounts[] = { 10, 15, 20, 25 };


    if (m_iStage >= 5)
    {
        return;
    }

    switch (m_iStage)
    {
    // 1스테이지  
    case 0:  
    {
        CStageMgr::UpdateStageMonsters(1500.f, stageMonsterCounts[0], m_ObjList);

        break;
    }
    // 2스테이지
    case 1: 
    {
        CStageMgr::UpdateStageMonsters(1400.f, stageMonsterCounts[1], m_ObjList);

        break;
    }
    // 3스테이지
    case 2: 
    {
        CStageMgr::UpdateStageMonsters(1300.f, stageMonsterCounts[2], m_ObjList);
        break;
    }
    // 4스테이지
    case 3: 
    {
        CStageMgr::UpdateStageMonsters(1200.f, stageMonsterCounts[3], m_ObjList);
        break;
    }
    // 보스 스테이지
    case 4: 
    {
        if (m_bBossSpawned == false)
        {
            SpawnBossMonster();
            m_bBossSpawned = true;
        }
        break;
    }
    default:
    {

    }
        break;
    }
}

void CStageMgr::AddKillCount(int _iValue)
{
    m_KillCount += _iValue;
}

void CStageMgr::ResetStage()
{
    m_iStage = 0;
    m_KillCount = 0;
    m_bBossSpawned = false;
    CScoreMgr::GetInst()->SetScore(0);
    CStageMgr::GetInst()->m_monstersSpawned = 0;

    // 필요하다면 여기서 플레이어, 몬스터 등 오브젝트를 다시 생성해서 ObjList에 추가
    // 예시:
    // CObj* pPlayer = CAbstractFactory<CPlayer>::Create_Obj(초기X, 초기Y);
    // ObjList.push_back(pPlayer);
}

// 스테이지별 몬스터 상태 관리 및 스폰을 처리하는 함수
void CStageMgr::UpdateStageMonsters(float shootInterval, int totalMonsters, list<CObj*> m_ObjList[OBJ_END])
{
    // 1. 현재 스테이지의 모든 몬스터의 사격 간격을 설정
    for (CObj* pObj : m_ObjList[OBJ_MONSTER])
    {
        CMonster* pMonster = dynamic_cast<CMonster*>(pObj);
        if (pMonster)
        {
            pMonster->Set_ShootInterval(shootInterval);
        }
    }

    // 2. 스테이지 클리어 조건 체크
    if (m_KillCount >= totalMonsters)
    {
        m_iStage++; // 다음 스테이지로 이동
        m_KillCount = 0; // 킬 카운트 초기화
        m_monstersSpawned = 0; // 생성된 몬스터 수 초기화
        m_ObjList[OBJ_MONSTER].clear(); // 현재 몬스터 리스트 비우기

        return;
    }

    // 3. 남은 몬스터가 있고, 화면에 몬스터가 5마리 미만이면 추가 스폰
    int remain = totalMonsters - m_monstersSpawned;
    if (remain > 0 && m_ObjList[OBJ_MONSTER].size() < 5)
    {
        int spawnCount = min(5 - static_cast<int>(m_ObjList[OBJ_MONSTER].size()), remain);
        // 3-1 몬스터 스폰하는 함수.
        SpawnMonsters(spawnCount);
        m_monstersSpawned += spawnCount;
    }
}


