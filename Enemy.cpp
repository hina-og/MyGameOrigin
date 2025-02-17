#include "Enemy.h"
#include "Engine/Model.h"
#include "PlayScene.h"


Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
	//hModel_ = Model::Load("Model\\Enemy.fbx");
	//assert(hModel_ >= 0);
	
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model\\Enemy.fbx");
	assert(hModel_ >= 0);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet")
	{
		playscene_->DethEnemy();
 		KillMe();
		pTarget->KillMe();
	}
}