#pragma once
#include "Engine/GameObject.h"
class Bullet
	: public GameObject
{
    int hModel_;
    float bulletSpeed_;
    XMFLOAT3 moveDir_;

    bool isInitialized_{false};
public:
    Bullet(GameObject* parent);
    ~Bullet();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void SetMoveDir(XMFLOAT3 _move) { moveDir_ = _move; }
    void SetSpeed(float _speed) { bulletSpeed_ = _speed; }
};

