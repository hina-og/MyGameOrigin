#pragma once
#include "Engine/GameObject.h"
class Player :
    public GameObject
{
    int hModel_;
    bool onGround;
    bool isJamp;
    bool canJamp;
    float speed_;

    XMVECTOR moveDirection;

    bool slide_;
    float slideTime_;
    float slideScale_;
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
};

