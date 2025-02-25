#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Object.h"
#include "SquareCollider.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/NoHitSphereCollider.h"
#include "EnemyMaster.h"
#include "Enemy.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_(-1),front_({ 0,0,1,0 })
{
	g_ = 0.87;
	transform_.position_ = { 0,0.5,0 };
	onGround_ = false;
	isJamp_ = false;
	speed_ = 0.1;
	hp_ = 10;

	slide_ = false;
	slideTime_ = Init_SlideTime;
	slideScale_ = 1.0f;
	nearBullet_ = false;
	jastSlide_ = false;
	justTime_ = Init_JustTime;
}

Player::~Player()
{
}

void Player::Initialize()
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
	hModel_ = model_[PLAYER_MODEL::DEFAULT];
	transform_.position_ = { 0,0,-5 };
	assert(hModel_ >= 0);

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0, 0.3, 0), 0.6);
	AddCollider(collider);

	NoHitSphereCollider* slideCollider = new NoHitSphereCollider(XMFLOAT3(0, 0.3, 0), 1.0);
	AddCollider(slideCollider);
}

void Player::Update()
{
	if (canJamp_)
	{
		hModel_ = model_[PLAYER_MODEL::DEFAULT];
	}
	else
	{
		if(Model::GetAnimFrame(model_[PLAYER_MODEL::JAMP]) >= 120)
			Model::SetAnimFrame(model_[PLAYER_MODEL::JAMP], 120);
	}
	if (transform_.position_.y - g_ <= 0)
	{
		onGround_ = true;
	}

	XMFLOAT3 mouseResult;
	mouseResult = Input::GetMouseMove();
	mouseResult.x = -mouseResult.x;

	Camera::MouseToCamera(mouseResult);
	Camera::SetTarget(transform_.position_.x, transform_.position_.y + 2, transform_.position_.z);

	Move();
	
	if (transform_.rotate_.y > 360)
	{
		transform_.rotate_.y -= 360;
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
		canJamp_ = false;//ジャンプできない
		if (hModel_ == model_[PLAYER_MODEL::JAMP] && Model::GetAnimFrame(hModel_) >= 120)
		{
			Model::SetAnimFrame(hModel_, 119);
		}
	}

	if (jastSlide_)
	{
		JastSlide();
	}

	//落ちすぎたときに初期地点に戻す
	if (transform_.position_.y < -100)
	{
		transform_.position_ = { 0,0,0 };
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
	//if (pTarget->GetObjectName() == "Enemy")
	//{
	//	KillMe();
	//	pTarget->KillMe();
	//}

	if (pTarget->GetObjectName() == "object")
	{
		XMFLOAT3 trans = pTarget->squareCollider_->GetDist();
		transform_.position_ = { transform_.position_.x + trans.x,transform_.position_.y ,transform_.position_.z + trans.z };
	}

	if (pTarget->GetObjectName() == "Bullet" && !slide_)
	{
		Damage(1);
	}
}

void Player::NoHitCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet")
	{
		nearBullet_ = false;
		if (slide_)
			nearBullet_ = true;
	}
	if (pTarget->GetParent()->GetObjectName() == "EnemyMaster"&& nearBullet_)
	{
		jastSlide_ = true;
	}
}

void Player::Move()
{
	DirVec camDir_ = Camera::UpdatePlayerPositionAndCamera();

	XMVECTOR moveDirection = XMVectorZero();

	// 入力に基づいて移動方向を決定
	if (!slide_)
	{
		if (Input::IsKey(DIK_S)) {
			moveDirection += camDir_.forward_; // 前方に進む
			hModel_ = model_[PLAYER_MODEL::RUN];
		}
		if (Input::IsKey(DIK_A)) {
			moveDirection += camDir_.right_; // 後方に進む
			hModel_ = model_[PLAYER_MODEL::RUN];
		}
		if (Input::IsKey(DIK_D)) {
			moveDirection -= camDir_.right_;   // 左に進む
			hModel_ = model_[PLAYER_MODEL::RUN];
		}
		if (Input::IsKey(DIK_W)) {
			moveDirection -= camDir_.forward_;   // 右に進む
			hModel_ = model_[PLAYER_MODEL::RUN];
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
		g_ = -0.3;
		Model::SetAnimFrame(model_[PLAYER_MODEL::JAMP], 0);
		hModel_ = model_[PLAYER_MODEL::JAMP];
	}

	if (Input::IsMouseButtonDown(LEFT_CLICK))
	{
		slide_ = true;
		slideTime_ = Init_SlideTime; // スライド時間（適切な時間に調整）
		slideDirection_ = moveDirection; // 現在の移動方向をスライド方向として保存
	}
	if (Input::IsMouseButtonDown(RIGHT_CLICK) && jastSlide_)
	{
		Enemy* e = eMas->NearestEnemy(transform_.position_,3.0f);
		if (e != nullptr)
		{
			Capture(e);
		}
	}



	if (slide_)
	{
		moveDirection = slideDirection_;
		Slide();
	}



	// 移動方向がゼロでない場合、正規化してスピードを掛ける
	if (!XMVector3Equal(moveDirection, XMVectorZero())) {
		moveDirection = XMVector3Normalize(moveDirection) * speed_;

		transform_.position_.x += XMVectorGetX(moveDirection);
		transform_.position_.z += XMVectorGetZ(moveDirection);

		// 方向に合わせて回転
		float angle = atan2(XMVectorGetX(moveDirection), XMVectorGetZ(moveDirection)) * (180 / 3.14f);
		if (fabs(transform_.rotate_.y - angle) > 1.0f) {
			if (transform_.rotate_.y < angle) {
				transform_.rotate_.y += 10.0f;
			}
			else if (transform_.rotate_.y > angle) {
				transform_.rotate_.y -= 10.0f;
			}
		}
	}
}

void Player::Slide()
{
	if (slideScale_ >= 0.7 && slideTime_ > 0)
	{
		slideScale_ -= 0.04;
	}
	if (slideTime_ <= 0)
	{
		slideScale_ += 0.05;
		if (slideScale_ >= 1.0)
		{
			slideScale_ = 1.0;
			slideTime_ = Init_SlideTime;
			slide_ = false;
		}
	}

	transform_.scale_ = { 1 * slideScale_,1 * slideScale_,1 * slideScale_ };

	slideTime_ -= 0.01;

	speed_ = 0.3;

}

void Player::JastSlide()
{
	if (justTime_ <= 0)
	{
		justTime_ = Init_JustTime;
		jastSlide_ = false;
	}

	justTime_ -= 0.01;
}

void Player::Capture(Enemy* _e)
{
	transform_.position_ = _e->GetPosition();
	_e->KillMe();
}

void Player::Damage(int _damage)
{
	hp_ -= _damage;
}