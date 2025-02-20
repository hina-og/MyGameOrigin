#include "Object.h"
#include "SquareCollider.h"
#include "Engine/Model.h"

Object::Object(GameObject* parent)
    : GameObject(parent, "Object"), hModel_(-1)
{
}

Object::~Object()
{
}

void Object::Initialize()
{
    hModel_ = Model::Load("Model\\building01.fbx");
    assert(hModel_ >= 0);
    transform_.position_ = { 5,0,10 };

    SquareCollider* col = new SquareCollider(5, 10, 5);
    this->AddSquareCollider(col);
}

void Object::Initialize(std::string _fileName, XMFLOAT3 _pos, XMFLOAT3 _size)
{
    hModel_ = Model::Load("Model\\building01.fbx");
    assert(hModel_ >= 0);
    transform_.position_ = _pos;

    SquareCollider* col = new SquareCollider(_size);
    this->AddSquareCollider(col);
}

void Object::Update()
{
}

void Object::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Object::Release()
{
}

//FBX* Object::GetFBX()
//{
//    return pFbx;
//}
