#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include"Player1.h"
#include "Camera.h"
#include"Tile.h"
#include"Icon.h"
#include"Icons.h"
#include"Character.h"
#include"TriggerSetUI.h"
#include"TriggerSetUIFrame.h"
#include"TriggerIcon.h"
#include"TriggerIcons.h"
#include"Engine/CsvReader.h"

PlayScene::PlayScene(GameObject* parent)
{
	csv_ = new CsvReader();
	Instantiate<Player1>(this);
	/*Instantiate<Character>(this);*/
	Instantiate<Tile>(this);
	/*Instantiate<TriggerIcons>(this);*/
	Instantiate<Icons>(this);
	/*Instantiate<Icon>(this);*/
	/*Instantiate<TriggerSetUI>(this);
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	int FN2DLine = 0;
	string DLC = "Assets//Image//TriggerIcon//";
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "FileName2D") {
			FN2DLine = x;
		}
	}
	for (int y = 1; y < csv_->GetHeight(); y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, y);
		std::string flPath;
		flPath = DLC + graphName;
		TriggerIcon* pTIcon = Instantiate<TriggerIcon>(this);
		pTIcon->Load(flPath);
		SIZE_2D IconSize = pTIcon->GerGraphSize();
		VECTOR graphPos = { 0,IconSize.y * (y - 1) ,0 };
		pTIcon->SetInitialPosition(graphPos);
		pTIcon->Set3DPosition(graphPos);
	}
	TriggerSetUIFrame* pTSUF = Instantiate<TriggerSetUIFrame>(this);*/

	Instantiate<Camera>(this); // Playerより後に書く
	// とりあえずカメラを設定する
	/*SetCameraPositionAndTarget_UpVecY(VGet(0,0,0), VGet(0, 0, 0));*/
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		Player1* pPlayer = FindGameObject<Player1>();
		pPlayer->SetState_(STEP1);
		Tile* pTile = FindGameObject<Tile>();
		pTile->SetState_(STEP1);
	}
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
