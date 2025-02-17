#pragma once
#include "Engine/GameObject.h"

class PlayScene;

class Enemy :
    public GameObject
{
    int hModel_;
    bool Alive_;
    int kinokoNum_;
    PlayScene* playscene_;
public:
    Enemy(GameObject* parent);
    void Initialize();
    void Update();
    void Draw();
    void Release();
    void OnCollision(GameObject* pTarget);
};

