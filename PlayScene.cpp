#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include"Player1.h"
#include "Camera.h"
#include"Tile.h"
#include"BackGround.h"
#include"Map.h"
#include"rader.h"
#include"Unit.h"
#include"Timer.h"
#include"TileIcons.h"
#include"UnitIcons.h"

PlayScene::PlayScene(GameObject* parent)
{
	Instantiate<BackGround>(this);
	Instantiate<Map>(this);
	Instantiate<rader>(this);
	Instantiate<Unit>(this);
	Instantiate<Timer>(this);
	Instantiate<TileIcons>(this);
	Instantiate<UnitIcons>(this);
	Instantiate<Player1>(this);
	Instantiate<Tile>(this);
	Instantiate<Camera>(this); // Playerより後に書く
	// とりあえずカメラを設定する
	/*SetCameraPositionAndTarget_UpVecY(VGet(0,0,0), VGet(0, 0, 0));*/
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	/*if (CheckHitKey(KEY_INPUT_RETURN)) {
		Player1* pPlayer = FindGameObject<Player1>();
		pPlayer->SetState_(STEP1);
		Tile* pTile = FindGameObject<Tile>();
		pTile->SetState_(STEP1);
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
