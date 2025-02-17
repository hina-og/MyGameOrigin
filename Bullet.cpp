#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

Bullet::Bullet(GameObject* parent)
	: GameObject(parent, "Bullet"), hModel_(-1),bulletSpeed_(0.05)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Model\\bullet.fbx");
	assert(hModel_ >= 0);

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3);
	AddCollider(collider);
}

void Bullet::Update()
{
	//transform_.position_.z += 0.1;
	transform_.position_.x = transform_.position_.x + moveDir_.x * bulletSpeed_;
	transform_.position_.y = transform_.position_.y + moveDir_.y * bulletSpeed_;
	transform_.position_.z = transform_.position_.z + moveDir_.z * bulletSpeed_;

	moveDir_ = { moveDir_.x,moveDir_.y - 0.05f,moveDir_.z };
	if (transform_.position_.y < -10)
	{
		KillMe();
	}
	//transform_.position_.y -= 0.01f;

}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
