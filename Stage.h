#pragma once
#include "Engine/GameObject.h"
#include "Engine/FBX.h"
#include "Object.h"

const int STAGE_SIZE_X{ 15 };
const int STAGE_SIZE_Z{ 15 };

class Stage
	: public GameObject
{
	int hModel_;
public:
	Stage(GameObject* parent);
	~Stage();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool InStage(XMFLOAT3 pos);
};

