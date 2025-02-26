#include "Enemy.h"
#include "Player.h"

bool Enemy::IsPlayerInView(float viewAngle)
{
	GameObject* pPlayer = FindPlayer();
	if (!pPlayer) return false;

	XMVECTOR toPlayer = XMVectorSet(
		pPlayer->GetPosition().x - transform_.position_.x,
		0, 
		pPlayer->GetPosition().z - transform_.position_.z,
		0
	);

	toPlayer = XMVector3Normalize(toPlayer);
	//³–Ê•ûŒüƒxƒNƒgƒ‹
	float yawRad = DirectX::XMConvertToRadians(transform_.rotate_.y);
	XMVECTOR forward = XMVectorSet(sin(yawRad), 0, cos(yawRad), 0);

	//“àÏ
	float dotProduct = XMVectorGetX(XMVector3Dot(forward, toPlayer));

	float angleBetween = acos(dotProduct) * (180.0f / XM_PI);

	return (angleBetween <= viewAngle / 2.0f);
}

void Enemy::Damage(int _damage)
{
	hp_ -= _damage;
}

void Enemy::Attack()
{
	
}
