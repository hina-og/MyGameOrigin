#pragma once
#include "Engine/GameObject.h"

enum
{
    DEFAULT,
    RUN,
    JAMP,
    END
};


class Player :
    public GameObject
{
    std::string modelName[END] =
    {
        "Slime",
        "Robot_Run",
        "Slime_Jamp",
        
    };

    int model_[END];
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
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;

    void Move();
    void Slide();
};

