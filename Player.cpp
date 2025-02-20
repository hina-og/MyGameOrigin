#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Object.h"
#include "SquareCollider.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player.h"),hModel_(-1)
{
	g_ = 0.87;
	transform_.position_ = { 0,0.5,0 };
	onGround_ = false;
	isJamp_ = false;
	speed_ = 0.1;
	hp_ = 10;

	slide_ = false;
	slideTime_ = 0.2f;
	slideScale_ = 1.0f;
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Slime_Run.fbx");
	assert(hModel_ >= 0);

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3);
	AddCollider(collider);

	transform_.position_ = { 0,0,-5 };
}

void Player::Update()
{
	if (transform_.position_.y <= 0)
	{
		onGround_ = true;
	}


	XMFLOAT3 mouseResult;
	mouseResult = Input::GetMouseMove();
	mouseResult.x = -mouseResult.x;

	Camera::MouseToCamera(mouseResult);
	Camera::SetTarget(transform_.position_.x, transform_.position_.y + 2, transform_.position_.z);


	DirVec camDir_ = Camera::UpdatePlayerPositionAndCamera();

	if (!slide_)
	{
		moveDirection = XMVectorZero();

		if (Input::IsKey(DIK_A))
		{
			moveDirection += camDir_.right_;
			transform_.rotate_.y += 1;
		}
		if (Input::IsKey(DIK_D))
		{
			moveDirection -= camDir_.right_;
		}
		if (Input::IsKey(DIK_S))
		{
			moveDirection += camDir_.forward_;
		}
		if (Input::IsKey(DIK_W))
		{
			moveDirection -= camDir_.forward_;
		}
	}
	if (Input::IsKey(DIK_LSHIFT))
	{
		speed_ = 0.15;
	}
	else
	{
		speed_ = 0.1;
	}

	if (Input::IsKeyDown(DIK_SPACE) && canJamp_)
	{
		onGround_ = false;
		isJamp_ = true;
		canJamp_ = false;
		g_ = -0.5;
	}

	if (Input::IsMouseButtonDown(LEFT_CLICK))
	{
		slide_ = true;
	}
	if (Input::IsMouseButtonDown(RIGHT_CLICK))
	{
		pBullet = Instantiate<Bullet>(this->GetParent()->GetParent());
		pBullet->SetPosition(transform_.position_);
		pBullet->SetRotate(transform_.rotate_);
	}

	if (transform_.rotate_.y > 360)
	{
		transform_.rotate_.y -= 360;
	}

	if (slide_)
	{
		Slide();
	}

	// 移動方向がゼロでない場合、正規化して速度を掛ける
	if (!XMVector3Equal(moveDirection, XMVectorZero())) {
		moveDirection = XMVector3Normalize(moveDirection) * speed_; // 速度5.0f

		transform_.position_.x += XMVectorGetX(moveDirection);
		transform_.position_.z += XMVectorGetZ(moveDirection);

		float angle = atan2(XMVectorGetX(moveDirection), XMVectorGetZ(moveDirection)) * (180 / 3.14);

		/*if (angle < -180)
		{
			angle = -180;
		}
		if (angle > 180)
		{
			angle = 180;
		}

		if (transform_.rotate_.y != angle)
		{
			if (angle - transform_.rotate_.y <= 180.0)
			{

				if (angle - transform_.rotate_.y < 1.0)
				{
					transform_.rotate_.y = angle;
				}
				else
				{
					transform_.rotate_.y += 1.0;
				}
			}
			if (angle - transform_.rotate_.y > 180)
			{
				if (transform_.rotate_.y - angle > -1.0)
				{
					transform_.rotate_.y = angle;
				}
				else
				{
					transform_.rotate_.y -= 1.0;
				}
			}
		}*/
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
		g_ += 0.87;
		isJamp_ = false;
	}

	//落ちすぎたときに初期地点に戻す
	if (transform_.position_.y < -100)
	{
		transform_.position_ = { 0,0.5,0 };
	}

	onGround_ = false;
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
	//Enemy* enemy = (Enemy*)FindObject("Enemy");

	//if (pTarget == enemy)
	//{
	//	//KillMe();
	//	//pTarget->KillMe();
	//}
	if (pTarget->GetObjectName() == "Enemy")
	{
		KillMe();
		pTarget->KillMe();
	}

	if (pTarget->GetObjectName() == "object")
	{
		XMFLOAT3 trans = pTarget->squareCollider_->GetDist();
		transform_.position_ = { transform_.position_.x + trans.x,transform_.position_.y ,transform_.position_.z + trans.z };
	}

	if (pTarget->GetObjectName() == "Bullet" && pTarget->GetParent()->GetObjectName() == "Enemy")
	{
		Damage(1);
	}
}

void Player::Slide()
{
	if (slideScale_ >= 0.7 && slideTime_ > 0)
	{
		slideScale_ -= 0.01;
	}
	if (slideTime_ <= 0)
	{
		slideScale_ += 0.05;
		if (slideScale_ >= 1.0)
		{
			slideScale_ = 1.0;
			slideTime_ = 0.2f;
			slide_ = false;
		}
	}

	transform_.scale_ = { 1 * slideScale_,1 * slideScale_,1 * slideScale_ };

	slideTime_ -= 0.001;

	speed_ = 2.0;
}

void Player::Damage(int _damage)
{
	hp_ -= _damage;
}