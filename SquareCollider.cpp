#include "SquareCollider.h"

SquareCollider::SquareCollider(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}

SquareCollider::SquareCollider(DirectX::XMFLOAT3 _size)
	: x(_size.x), y(_size.y), z(_size.z)
{
}
