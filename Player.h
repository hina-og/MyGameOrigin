#pragma once
#include "Engine/GameObject.h"
#include "Bullet.h"

class Player :
    public GameObject
{
    enum PLAYER_MODEL
    {
        DEFAULT,
        RUN,
        JAMP,
        END
    };

    std::string modelName[PLAYER_MODEL::END] =
    {
        "Slime",
        "Slime_Run",
        "Slime_Jamp",
        
    };
    const float Init_SlideTime{ 0.15f };

    int model_[PLAYER_MODEL::END];
    int hModel_;
    bool onGround_;
    bool isJamp_;
    bool canJamp_;
    float speed_;
    int hp_;

    XMVECTOR moveDirection;
    XMVECTOR front_;

    bool slide_;
    float slideTime_;
    float slideScale_;
    XMVECTOR slideDirection_;
    bool nearTarget_;

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
    void NoHitCollision(GameObject* pTarget) override;

    void Move();
    void Slide();

    void Damage(int _damage);
};

