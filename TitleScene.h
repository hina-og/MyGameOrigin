#pragma once
#include "Engine/GameObject.h"
class TitleScene :
    public GameObject
{
    int hPict_;
public:
    TitleScene(GameObject* parent);
    void Initialize();
    void Update();
    void Draw();
    void Release();
};

