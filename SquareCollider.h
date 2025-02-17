#pragma once
#include <DirectXMath.h>
class SquareCollider
{
	float x;
	float y;
	float z;

	DirectX::XMFLOAT3 dist;
public:
	SquareCollider(float _x, float _y, float _z);
	SquareCollider(DirectX::XMFLOAT3 _size);

	float GetX() { return x / 2; }
	float GetY() { return y / 2; }
	float GetZ() { return z / 2; }

	void SetDist(DirectX::XMFLOAT3 _dist) { dist = _dist; }
	DirectX::XMFLOAT3 GetDist() { return dist; }
};

