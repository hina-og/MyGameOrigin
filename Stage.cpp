#include "Stage.h"
#include "Engine/SphereCollider.h"
#include "Engine/Model.h"


Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
	for (int y = 0; y < STAGE_SIZE_Y; y++)
	{
		for (int z = 0; z < STAGE_SIZE_Z; z++)
		{
			for (int x = 0; x < STAGE_SIZE_X; x++)
			{
				table[y][z][x] = { 0,0 };
			}
		}
	}
}

Stage::~Stage()
{
}

void Stage::Initialize()
{

	csv.Load("stagedata.csv");

	std::string fileName[] = {
		"BoxDefault",
		"BoxBrick",
		"BoxGrass",
		"BoxSand",
		"BoxWater"
	};

	int handle[END];

	for (int i = 0; i < END; i++)
	{
		handle[i] = Model::Load("Model\\StageBlock\\" + fileName[i] + ".fbx");
	}

	for (int y = 0; y < STAGE_SIZE_Y; y++)
	{
		for (int z = 0; z < STAGE_SIZE_Z; z++)
		{
			for (int x = 0; x < STAGE_SIZE_X; x++)
			{
				table[y][z][x].type = csv.GetValue(x, z + y * 20);
				table[y][z][x].hModel_ = handle[table[y][z][x].type];
			}
		}
	}

	//hModel_ = Model::Load("Model\\Plane.fbx");
	//assert(hModel_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform trans;

	for (int y = 0; y < STAGE_SIZE_Y; y++)
	{
		for (int z = 0; z < STAGE_SIZE_Z; z++)
		{
			for (int x = 0; x < STAGE_SIZE_X; x++)
			{
				if(table[y][z][x].type < END)
				{
					trans.position_ = { (float)x - STAGE_SIZE_X / 2,(float)y - 0.5f,(float)-z };
					Model::SetTransform(table[y][z][x].hModel_, trans);
					Model::Draw(table[y][z][x].hModel_);
				}
			}
		}
	}

	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
}

void Stage::Release()
{
}

//FBX* Stage::GetFBX()
//{
//	return pFbx;
//}

bool Stage::InStage(XMFLOAT3 pos)
{
	if (pos.x >= -STAGE_SIZE_X && pos.x <= STAGE_SIZE_X &&
		pos.z >= -STAGE_SIZE_Z && pos.z <= STAGE_SIZE_Z)
	{
		return true;
	}
	return false;
}
