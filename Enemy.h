#pragma once
#include "Engine/GameObject.h"
#include "Bullet.h"

class PlayScene;

const int BULLET_NUM{ 1 };

class Enemy :
    public GameObject
{
    int hModel_;
    bool onGround_;
    bool isJamp_;
    bool canJamp_;
    float speed_;
    int hp_;

    float attackTime_;

    int viewAngle_;//éãñÏäp
    bool foundPlayer_;//ÉvÉåÉCÉÑÅ[Çå©Ç¬ÇØÇΩ

    Bullet* bullet[BULLET_NUM];
    int bulletNum_;
public:
    bool alive_;

    Enemy(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget)  override;

    void SetPosition(Transform _pos) { transform_ = _pos; }
    bool ViewingAngle(float _range, XMFLOAT3 _targetPos, float _angle);
    void Damage(int _damage);
    void Attack();
};

