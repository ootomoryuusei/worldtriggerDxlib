#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include"Player1.h"
#include "Ground.h"
#include "Goblin.h"
#include "Camera.h"
#include"Tile.h"
PlayScene::PlayScene(GameObject* parent)
{
	/*Instantiate<Player>(this);*/
	Instantiate<Player1>(this);
	Instantiate<Tile>(this);
	Instantiate<Camera>(this); // Playerより後に書く
	/*Instantiate<Ground>(this);*/
	/*Instantiate<Goblin>(this);*/

	// とりあえずカメラを設定する
	/*SetCameraPositionAndTarget_UpVecY(VGet(0,0,0), VGet(0, 0, 0));*/
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PlayScene", GetColor(0, 0, 255));

	// アナログの取り方
	int x;
	int y;
	GetJoypadAnalogInput(&x, &y, DX_INPUT_PAD1);
	DrawFormatString(100, 10, GetColor(255,255,255), "Analog %d,%d", x, y);
}
