#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include"Player1.h"
#include"Enemy.h"
#include "Camera.h"
#include"Tiles.h"
#include"BackGround.h"
#include"Map.h"
#include"rader.h"
#include"Unit.h"
#include"Timer.h"
#include"TileIcons.h"
#include"UnitIcons.h"
#include "Mouse.h"
#include"MoveSelectIcon.h"
#include"MoveSetIcon.h"

#include"InputManager.h"
#include"GroupManager.h"
#include"Keyboard.h"

PlayScene::PlayScene(GameObject* parent) : GameObject(parent,"playscene")
{
	Instantiate<InputManager>(this); //入力管理クラス
	Instantiate<BackGround>(this); //背景
	Instantiate<GroupManager>(this); //グループ管理クラス
	Instantiate<Timer>(this);

	/*Instantiate<rader>(this);*/
	/*Instantiate<Unit>(this);*/

	Instantiate<Tiles>(this); //タイル群

	Instantiate<Player1>(this); //プレイヤー

	Instantiate<Enemy>(this); //敵

	Instantiate<Map>(this); //マップ

	Instantiate<MoveSelectIcon>(this); //行動選択用アイコン
	Instantiate<MoveSetIcon>(this); //行動セット用アイコン

	Instantiate<UnitIcons>(this); //ユニット群

	Instantiate<Camera>(this); // Playerより後に書く
	
	// とりあえずカメラを設定する
	/*SetCameraPositionAndTarget_UpVecY(VGet(0,0,0), VGet(0, 0, 0));*/
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	/*if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_SELECT);
	}*/
}

void PlayScene::Draw()
{
	//DrawString(0, 0, "PlayScene", GetColor(0, 0, 255));

	//// アナログの取り方
	//int x;
	//int y;
	//GetJoypadAnalogInput(&x, &y, DX_INPUT_PAD1);
	//DrawFormatString(100, 10, GetColor(255,255,255), "Analog %d,%d", x, y);
}
