#pragma once
#include "Engine/GameObject.h"
#include "Bullet.h"

class Player :
    public GameObject
{
    int hModel_;
    bool onGround_;
    bool isJamp_;
    bool canJamp_;
    float speed_;
    int hp_;

    XMVECTOR moveDirection;

    bool slide_;
    float slideTime_;
    float slideScale_;

    Bullet* pBullet;
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;

    void Slide();

    void Damage(int _damage);
};

