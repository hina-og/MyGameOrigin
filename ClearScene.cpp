#include "ClearScene.h"
#include "Engine/Image.h"

ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent, "ClearScene"), hPict_(-1)
{
}

void ClearScene::Initialize()
{
	hPict_ = Image::Load("Image\\ClearScene.png");
}

void ClearScene::Update()
{
}

void ClearScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void ClearScene::Release()
{
}