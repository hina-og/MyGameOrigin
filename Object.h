#pragma once
#include "Engine/GameObject.h"
#include "Engine/FBX.h"

class Object
	: public GameObject
{
	int hModel_;
public:
	Object(GameObject* parent);
	~Object();
	void Initialize() override;
	void Initialize(std::string _fileName, XMFLOAT3 _pos, XMFLOAT3 _size);
	void Update() override;
	void Draw() override;
	void Release() override;

	//FBX* GetFBX();
};

