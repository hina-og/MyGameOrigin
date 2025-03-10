#pragma once
#include "Engine/GameObject.h"
#include "Engine/FBX.h"
#include "Engine/CsvReader.h"
#include "Object.h"

const int STAGE_SIZE_X{ 20 };
const int STAGE_SIZE_Y{ 3 };
const int STAGE_SIZE_Z{ 20 };

enum BoxTex
{
	BRICK, DEFAULT, GRASS, SAND, WATER, END, SPACE
};

class Stage
	: public GameObject
{
	//int hModel_;

	CsvReader csv;

	struct BoxData
	{
		int hModel_;
		int type;
		//Fbx* fbx;
	};

	//Fbx* fbx[END];
	BoxData table[STAGE_SIZE_Y][STAGE_SIZE_Z][STAGE_SIZE_X];

public:
	Stage(GameObject* parent);
	~Stage();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool InStage(XMFLOAT3 pos);
};

