#include "SetScene.h"
#include"Engine/SceneManager.h"
#include"SetIcons.h"
#include"Icons.h"
#include"Player1.h"
#include"Camera.h"
#include"Mouse.h"

SetScene::SetScene(GameObject* parent)
	: GameObject(parent)
{
	/*Instantiate<Icons>(this);*/
	Instantiate<SetIcons>(this);
	Instantiate<Player1>(this);
	Instantiate<Camera>(this);
	Instantiate<Mouse>(this);
}

SetScene::~SetScene()
{
}

void SetScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_PLAY);
	}
}

void SetScene::Draw()
{
}
