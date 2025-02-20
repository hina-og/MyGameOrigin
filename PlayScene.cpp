#include "PlayScene.h"
#include "Player.h"
#include "EnemyMaster.h"
#include "Stage.h"

namespace 
{
	const int ENEMY_NUM{ 20 };
}

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	player = Instantiate<Player>(this);
	Instantiate<EnemyMaster>(this);
	Instantiate<Stage>(this);
	//Instantiate<Object>(this);
}                                                                                                                                                                  
void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}

