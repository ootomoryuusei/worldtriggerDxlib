#include "TitleScene.h"
#include "Engine/SceneManager.h"

TitleScene::TitleScene(GameObject* parent) : GameObject(parent)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_SELECT);
	}
}

void TitleScene::Draw()
{
	DrawString(0, 0, "TitleScene", GetColor(255, 0, 0));
}
