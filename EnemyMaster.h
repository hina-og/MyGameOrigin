#pragma once
#include "Engine/GameObject.h"
#include "Enemy.h"

const int ENEMY_NUM{ 1 };

class EnemyMaster :
    public GameObject
{
    Enemy* enemy[ENEMY_NUM];
public:
    EnemyMaster(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    int GetAliveEnemy();
};

