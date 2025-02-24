#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

Bullet::Bullet(GameObject* parent)
	: GameObject(parent, "Bullet"), hModel_(-1),bulletSpeed_(0.5)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Model\\Bullet.fbx");
	assert(hModel_ >= 0);

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0, 0, 0), 0.1);
	AddCollider(collider);
}

void Bullet::Update()
{
	if (!isInitialized_)
	{
		// transform_.rotate_ を基に移動方向を計算
		float yaw = transform_.rotate_.y;   // Y軸回転（左右）
		float pitch = transform_.rotate_.x; // X軸回転（上下）

		// 角度が度数法ならラジアンに変換
		yaw = DirectX::XMConvertToRadians(yaw);
		pitch = DirectX::XMConvertToRadians(pitch);

		moveDir_.x = sin(yaw) * cos(pitch);
		moveDir_.y = sin(pitch);
		moveDir_.z = cos(yaw) * cos(pitch);

		isInitialized_ = true;
	}


	//transform_.position_.z += 0.1;
	transform_.position_.x = transform_.position_.x + moveDir_.x * bulletSpeed_;
	transform_.position_.y = transform_.position_.y + moveDir_.y * bulletSpeed_;
	transform_.position_.z = transform_.position_.z + moveDir_.z * bulletSpeed_;

	//moveDir_ = { moveDir_.x,moveDir_.y + 0.05f,moveDir_.z };
	if (transform_.position_.x < -10 || transform_.position_.y < -10 || transform_.position_.z < -10 ||
		transform_.position_.x >  10 || transform_.position_.y >  10 || transform_.position_.z >  10)
	{
		KillMe();
	}
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}


