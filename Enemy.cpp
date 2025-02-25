#include "Enemy.h"

//bool Enemy::ViewingAngle(float _range, XMFLOAT3 _targetPos, float _angle)
//{
//	XMFLOAT3 dist_;
//	dist_.x = abs(_targetPos.x - transform_.position_.x);
//	dist_.y = abs(_targetPos.y - transform_.position_.y);
//	dist_.z = abs(_targetPos.z - transform_.position_.z);
//	if (dist_.x > _range || dist_.y > _range || dist_.z > _range)
//	{
//		return false;
//	}
//	else
//	{
//		float startAngle_ = transform_.rotate_.y - (viewAngle_ / 2);
//		float endAngle_ = transform_.rotate_.y + (viewAngle_ / 2);
//		if (startAngle_ <= _angle && _angle <= endAngle_)
//		{
//			return true;
//		}
//	}
//	return false;
//}

void Enemy::Damage(int _damage)
{
	hp_ -= _damage;
}

void Enemy::Attack()
{
	
}
