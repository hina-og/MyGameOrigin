#include "EnemyMaster.h"

EnemyMaster::EnemyMaster(GameObject* parent)
{
}

void EnemyMaster::Initialize()
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i] = Instantiate<Enemy>(this);
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
