#include "Enemy.h"
#include "Engine/Model.h"
#include "PlayScene.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	transform_.position_ = { (float)(rand() % 10 - 5),0,(float)(rand() % 10 - 5) };
	hModel_ = Model::Load("Model\\Enemy.fbx");
	assert(hModel_ >= 0);
}

void Enemy::Update()
{
	if (transform_.position_.y < 0)
	{
		onGround_ = true;
	}

	Player* player = (Player*)FindObject("Player");
	//float angle = atan2(transform_.position_.x - player->GetTransform().position_.x, transform_.position_.z - player->GetTransform().position_.z) * (180.0 / 3.14);

	//player‚ðŒ©‚Â‚¯‚½‚ç
	//if (ViewingAngle(10.0, player->GetTransform().position_, angle))
	//{
	//	//foundPlayer_ = true;
	//	//if(!isJamp_)
	//	//	//isJamp_ = true;
	//	//transform_.rotate_.y = angle;
	//}
	//else
	//{
	//	foundPlayer_ = false;
	//}

	if (!onGround_)
	{
		if (!isJamp_ /*&& ray.dist > 0*/)
			transform_.position_.y -= /*ray.dist -*/ 0.5;
		isJamp_ = false;
	}
	else
	{
		isJamp_ = true;
		//g_ += 0.0001;

	}

	//transform_.position_.x += cos(angle) * (0.01f * speed_) * 0.5;
	//transform_.position_.z -= sin(angle) * (0.01f * speed_) * 0.5;
	if (foundPlayer_)
	{
		/*transform_.position_.x += cos(angle) * (0.01f * speed_) * 0.5;
		transform_.position_.z -= sin(angle) * (0.01f * speed_) * 0.5;*/
	}

	transform_.position_.y -= g_;

	if (onGround_)//’n–Ê‚É‚Â‚¢‚Ä‚¢‚é‚Æ‚«
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

	if (transform_.position_.y < -100)
	{
		transform_.position_ = { 0,0.5,0 };
	}

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
	if (pTarget->GetObjectName() == "Bullet")
	{
 		KillMe();
		pTarget->KillMe();
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
	attackTime_ += 1.0f / 10.0f;

	if (attackTime_ >= 2.0f)
	{
		attackTime_ -= 2.0;

		Bullet* pBullet = Instantiate<Bullet>(this->GetParent()->GetParent());
		pBullet->SetPosition(transform_.position_);
		pBullet->SetRotate(transform_.rotate_);
		/*for (int i = 0; i < BULLET_NUM; i++)
		{
			if (bullet[i] != nullptr)
			{
				if(bullet[i]->IsDead())
					bullet[i] = nullptr;
			}
			else
			{
				bullet[i] = Instantiate<Bullet>(this);
				bullet[i]->SetPosition(transform_.position_);
				bullet[i]->SetRotate(transform_.rotate_);
				break;
			}
		}*/
	}
}
