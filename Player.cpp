#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Object.h"
#include "SquareCollider.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player.h"),hModel_(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Slime_Run.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0,0,-5 };
}

void Player::Update()
{
	if (transform_.position_.y <= 0 && stage->InStage(transform_.position_))
	{
		onGround = true;
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
		speed_ = 1.5;
	}
	else
	{
		speed_ = 1.0;
	}

	if (Input::IsKeyDown(DIK_SPACE) && canJamp)
	{
		onGround = false;
		isJamp = true;
		canJamp = false;
		g = -0.03;
	}

	if (Input::IsMouseButtonDown(Click))
	{
		slide_ = true;
	}
	if (Input::IsMouseButtonDown(RIGHT_CLICK))
	{

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
		moveDirection = XMVector3Normalize(moveDirection) * (0.01f * speed_); // 速度5.0f

		transform_.position_.x += XMVectorGetX(moveDirection);
		transform_.position_.z += XMVectorGetZ(moveDirection);

		float angle = atan2(XMVectorGetX(moveDirection), XMVectorGetZ(moveDirection)) * (180 / 3.14);

		if (angle < -180)
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
		}
	}

	transform_.position_.y -= g;

	if (onGround)//地面についているとき
	{
		isJamp = true;

		transform_.position_.y = 0;
		canJamp = true;
	}
	else
	{
		g += 0.0001;
		isJamp = false;
	}

	//落ちすぎたときに初期地点に戻す
	if (transform_.position_.y < -100)
	{
		transform_.position_ = { 0,0.5,0 };
	}

	onGround = false;
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
}

void Player::Slide()
{
}
