#include "EnemyMaster.h"

EnemyMaster::EnemyMaster(GameObject* parent)
    : GameObject(parent,"EnemyMaster")
{

}

void EnemyMaster::Initialize()
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i] = Instantiate<Robot>(this);
    }
}

void EnemyMaster::Update()
{
}

void EnemyMaster::Draw()
{
}

void EnemyMaster::Release()
{
}

Enemy* EnemyMaster::NearestEnemy(XMFLOAT3 _pos, float _len)//ˆø”‚Ì_pos‚©‚çˆê”Ô‹ß‚¢“G‚Ìƒ|ƒCƒ“ƒ^‚ð•Ô‚·
{
    Enemy* nearEnemy = enemy[0];
    XMFLOAT3 pos = enemy[0]->GetPosition();
    float dist = fDistanceCalculation3D(_pos, pos);
    for (int i = 1; i < ENEMY_NUM; i++)
    {
        pos = enemy[i]->GetPosition();
        float fdist = fDistanceCalculation3D(_pos, pos);
        if (dist > fdist)
        {
            dist = fdist;
            nearEnemy = enemy[i];
        }
    }
    if (dist > _len)
    {
        nearEnemy = nullptr;
    }
    return nearEnemy;
}

int EnemyMaster::GetAliveEnemy()
{
    int aliveNum = 0;
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (enemy[i]->alive_)
        {
            aliveNum++;
        }
    }
    return aliveNum;
}
