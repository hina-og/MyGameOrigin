#pragma once
#include "Engine/GameObject.h"
#include "Enemy.h"

class Robot
	: public Enemy
{
    enum ROBOT_MODEL
    {
        DEFAULT,
        RUN,
        ATTACK,
        END
    };

    std::string modelName[ROBOT_MODEL::END] =
    {
        "Robot",
        "Robot_Run",
        "Robot_Attack",
    };

	int bulletNum_;
public:
    Robot(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget)  override;
    void NoHitCollision(GameObject* pTarget) override;

    void Attack() override;
};

