#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/NoHitSphereCollider.h"
#include <vector>

class Player;

class Enemy :
    public GameObject
{
    
protected:
    std::vector<int> modelList_;
    

    //int model_[ENEMY_MODEL::END];

    int hModel_;
    bool onGround_;
    float speed_;
    int hp_;

    float attackTime_;

    int viewAngle_;//Ž‹–ìŠp
    XMFLOAT3 moveDir_;

    bool isChase_;

public:
    bool alive_;


    void SetPosition(Transform _pos) { transform_ = _pos; }
    //bool ViewingAngle(float _range, XMFLOAT3 _targetPos, float _angle);
    void Damage(int _damage);
    virtual void Attack();
    bool IsPlayerInView(float viewAngle);
};

