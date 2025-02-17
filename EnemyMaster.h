#pragma once
#include "Engine/GameObject.h"
class EnemyMaster :
    public GameObject
{
public:
    EnemyMaster(GameObject* parent);
    void Initialize();
    void Update();
    void Draw();
    void Release();
    int GetAliveEnemy();
};

