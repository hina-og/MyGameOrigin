#pragma once
#include "Engine/GameObject.h"
#include "Robot.h"

const int ENEMY_NUM{ 5 };

class EnemyMaster :
    public GameObject
{
    enum ENEMY_TYPE
    {
        ROBOT,
        END
    };
    Enemy* enemy[ENEMY_NUM];
public:
    EnemyMaster(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    Enemy* NearestEnemy(XMFLOAT3 _pos, float _len);
    int GetAliveEnemy();
};

