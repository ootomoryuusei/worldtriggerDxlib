#include "SelectScene.h"
#include"Engine/SceneManager.h"
#include"Icons.h"
#include"Player1.h"
#include"Camera.h"

SelectScene::SelectScene(GameObject* parent) 
	: GameObject(parent)
{
	Instantiate<Icons>(this);
	Instantiate<Player1>(this);
	////Instantiate<Tile>(this);
	Instantiate<Camera>(this); // Player‚æ‚èŒã‚É‘‚­
}

SelectScene::~SelectScene()
{
}

void SelectScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_SET);
	}
}

void SelectScene::Draw()
{
}
