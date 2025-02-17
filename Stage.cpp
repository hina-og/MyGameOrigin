#include "Stage.h"
#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hModel_(-1)
{
	transform_.position_ = { 0,0,0 };
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Model\\Plane.fbx");
	assert(hModel_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
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
