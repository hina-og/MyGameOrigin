#pragma once
#include "Engine/GameObject.h"

class Player;

class PlayScene :
    public GameObject
{
    Player* player;
    int enemyNum;
public:
    PlayScene(GameObject* parent);
    void Initialize();
    void Update();
    void Draw();
    void Release();
    void DethEnemy() { enemyNum--; }
    int GetEnemyNumg() { return enemyNum; }
};

