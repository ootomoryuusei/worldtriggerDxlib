#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include"Player1.h"
#include "Camera.h"
#include"Tile.h"
#include"Icon.h"
#include"Character.h"

PlayScene::PlayScene(GameObject* parent)
{
	Instantiate<Player1>(this);
	/*Instantiate<Character>(this);*/
	Instantiate<Tile>(this);
	Instantiate<Icon>(this);
	Instantiate<Camera>(this); // Player����ɏ���
	// �Ƃ肠�����J������ݒ肷��
	/*SetCameraPositionAndTarget_UpVecY(VGet(0,0,0), VGet(0, 0, 0));*/
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	/*if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
	}*/
}

void PlayScene::Draw()
{
	//DrawString(0, 0, "PlayScene", GetColor(0, 0, 255));

	//// �A�i���O�̎���
	//int x;
	//int y;
	//GetJoypadAnalogInput(&x, &y, DX_INPUT_PAD1);
	//DrawFormatString(100, 10, GetColor(255,255,255), "Analog %d,%d", x, y);
}
