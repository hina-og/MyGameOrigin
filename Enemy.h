#pragma once
#include "Engine/GameObject.h"
#include "Bullet.h"



class Enemy :
    public GameObject
{
    enum ENEMY_MODEL
    {
        DEFAULT,
        RUN,
        ATTACK,
        END
    };

    std::string modelName[ENEMY_MODEL::END] =
    {
        "Robot",
        "Robot_Run",
        "Robot_Attack",

    };

    int model_[ENEMY_MODEL::END];

    int hModel_;
    bool onGround_;
    bool isJamp_;
    bool canJamp_;
    float speed_;
    int hp_;

    float attackTime_;

    int viewAngle_;//éãñÏäp
    bool foundPlayer_;//ÉvÉåÉCÉÑÅ[Çå©Ç¬ÇØÇΩ
    XMFLOAT3 moveDir_;

    int bulletNum_;
public:
    bool alive_;

    Enemy(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget)  override;
    void NoHitCollision(GameObject* pTarget) override;

    void SetPosition(Transform _pos) { transform_ = _pos; }
    bool ViewingAngle(float _range, XMFLOAT3 _targetPos, float _angle);
    void Damage(int _damage);
    void Attack();
};

