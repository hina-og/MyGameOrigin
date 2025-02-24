#include "Enemy.h"
#include "Engine/Model.h"
#include "PlayScene.h"
#include "Engine/SphereCollider.h"
#include "Engine/NoHitSphereCollider.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
	speed_ = 0.08;
}

void Enemy::Initialize()
{
	for (int i = 0; i < END; i++)
	{
		model_[i] = Model::Load("Model\\" + modelName[i] + ".fbx");
		assert(model_[i] >= 0);
		switch (i)
		{
		case 1:
			Model::SetAnimFrame(model_[i], 0, 120, 2);
			break;
		case 2:
			Model::SetAnimFrame(model_[i], 0, 120, 1);
			break;
		}
	}
	hModel_ = model_[2];
	transform_.position_ = { (float)(rand() % 10 - 5),0,(float)(rand() % 10 - 5) };
	assert(hModel_ >= 0);

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0, 0.3, 0), 0.7);
	AddCollider(collider);

	NoHitSphereCollider* slideCollider = new NoHitSphereCollider(XMFLOAT3(0, 0.3, 0), 5.0);
	AddCollider(slideCollider);
}

void Enemy::Update()
{
	if (transform_.position_.y - g_ <= 0)
	{
		onGround_ = true;
	}



	if (!onGround_)
	{
		if (!isJamp_ /*&& ray.dist > 0*/)
			transform_.position_.y -= /*ray.dist -*/ 0.5;
		isJamp_ = false;
	}
	else
	{
		isJamp_ = true;
		g_ += 0.0001;

	}


	transform_.position_.y -= g_;

	if (onGround_)//地面についているとき
	{
		isJamp_ = true;

		transform_.position_.y = 0;
		canJamp_ = true;
	}
	else
	{
		g_ += 0.01;//重力加速度
		//isJamp_ = false;
	}

	if (transform_.position_.y < -100)
	{
		transform_.position_ = { 0,0,0 };
	}

	if(hModel_ == model_[2] && Model::GetAnimFrame(hModel_) == 75)
		Attack();

	onGround_ = false;
	transform_.rotate_.y += 1.0;
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
	//if (pTarget->GetObjectName() == "Player")
	//{
	//	KillMe();
	//	pTarget->KillMe();
	//}
}

//探知範囲に入ったら
void Enemy::NoHitCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		//double m = (transform_.position_.y - pTarget->GetPosition().y) / (transform_.position_.x - pTarget->GetPosition().x);

		//// 角度 theta を求める
		//// tan(theta) = m => theta = atan(m)
		//double theta = atan2(m);

		XMVECTOR dist = { transform_.position_.x - pTarget->GetPosition().x ,0,transform_.position_.z - pTarget->GetPosition().z };

		dist = XMVector2Normalize(dist);

		// sin(theta) を計算
		float angle = atan2(XMVectorGetZ(dist), XMVectorGetX(dist));
		transform_.rotate_.y = angle * 180.0 / 3.14 * -1 - 90.0;

		// transform_.rotate_ を基に移動方向を計算
		float yaw = transform_.rotate_.y;   // Y軸回転（左右）
		float pitch = transform_.rotate_.x; // X軸回転（上下）

		// 角度が度数法ならラジアンに変換
		yaw = DirectX::XMConvertToRadians(yaw);
		pitch = DirectX::XMConvertToRadians(pitch);

		moveDir_.x = sin(yaw) * cos(pitch);
		moveDir_.y = sin(pitch);
		moveDir_.z = cos(yaw) * cos(pitch);

		transform_.position_.x = transform_.position_.x + moveDir_.x * speed_;
		transform_.position_.y = transform_.position_.y + moveDir_.y * speed_;
		transform_.position_.z = transform_.position_.z + moveDir_.z * speed_;
	}
}

bool Enemy::ViewingAngle(float _range, XMFLOAT3 _targetPos, float _angle)
{
	XMFLOAT3 dist_;
	dist_.x = abs(_targetPos.x - transform_.position_.x);
	dist_.y = abs(_targetPos.y - transform_.position_.y);
	dist_.z = abs(_targetPos.z - transform_.position_.z);
	if (dist_.x > _range || dist_.y > _range || dist_.z > _range)
	{
		return false;
	}
	else
	{
		float startAngle_ = transform_.rotate_.y - (viewAngle_ / 2);
		float endAngle_ = transform_.rotate_.y + (viewAngle_ / 2);
		if (startAngle_ <= _angle && _angle <= endAngle_)
		{
			return true;
		}
	}
	return false;
}

void Enemy::Damage(int _damage)
{
	hp_ -= _damage;
}

void Enemy::Attack()
{
	Bullet* pBullet = Instantiate<Bullet>(this->GetParent()->GetParent());
	pBullet->SetPosition(transform_.position_);
	pBullet->SetRotate(transform_.rotate_);
}
