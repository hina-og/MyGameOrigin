#include "Robot.h"
#include "Bullet.h"

Robot::Robot(GameObject* parent)
{
	objectName_ = "Robot";
	hModel_ = -1;
	speed_ = 0.06;
}

void Robot::Initialize()
{
	for (int i = 0; i < END; i++)
	{
		modelList_.push_back(Model::Load("Model\\" + modelName[i] + ".fbx"));
		assert(modelList_[i] >= 0);
		switch (i)
		{
		case ROBOT_MODEL::RUN:
			Model::SetAnimFrame(modelList_[i], 0, 120, 2);
			break;
		case ROBOT_MODEL::ATTACK:
			Model::SetAnimFrame(modelList_[i], 0, 120, 1);
			break;
		}
	}
	hModel_ = modelList_[ROBOT_MODEL::ATTACK];
	transform_.position_ = { (float)(rand() % 10 - 5),0,(float)(rand() % 10 - 5) };
	assert(hModel_ >= 0);

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0, 0.3, 0), 0.7);
	AddCollider(collider);

	NoHitSphereCollider* slideCollider = new NoHitSphereCollider(XMFLOAT3(0, 0.3, 0), 7.0);
	AddCollider(slideCollider);
}

void Robot::Update()
{
	if (transform_.position_.y - g_ <= 0)
	{
		onGround_ = true;
	}



	if (onGround_)
	{
		
	}


	transform_.position_.y -= g_;

	if (onGround_)//地面についているとき
	{
		g_ += 0.0001;
		transform_.position_.y = 0;
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

	if (hModel_ == modelList_[ROBOT_MODEL::ATTACK] && Model::GetAnimFrame(hModel_) == 75)
		Attack();

	onGround_ = false;
	transform_.rotate_.y += 1.0;
}

void Robot::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Robot::Release()
{
}

void Robot::OnCollision(GameObject* pTarget)
{
}

void Robot::NoHitCollision(GameObject* pTarget)
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

		//// transform_.rotate_ を基に移動方向を計算
		//float yaw = transform_.rotate_.y;   // Y軸回転（左右）
		//float pitch = transform_.rotate_.x; // X軸回転（上下）

		//// 角度が度数法ならラジアンに変換
		//yaw = DirectX::XMConvertToRadians(yaw);
		//pitch = DirectX::XMConvertToRadians(pitch);

		//moveDir_.x = sin(yaw) * cos(pitch);
		//moveDir_.y = sin(pitch);
		//moveDir_.z = cos(yaw) * cos(pitch);

		//transform_.position_.x = transform_.position_.x + moveDir_.x * speed_;
		//transform_.position_.y = transform_.position_.y + moveDir_.y * speed_;
		//transform_.position_.z = transform_.position_.z + moveDir_.z * speed_;
	}
}

void Robot::Attack()
{
	Bullet* pBullet = Instantiate<Bullet>(this->GetParent()->GetParent());
	pBullet->SetPosition(transform_.position_);
	pBullet->SetRotate(transform_.rotate_);
}
