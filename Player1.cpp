#include "Player1.h"
#include "Camera.h"
#include"Tile.h"
#include"Engine/CsvReader.h"
#include"ImGui/imgui.h"

#include"CharacterFactory.h"
#include "CharacterGroup.h"
#include"CharacterData.h"

#include"GroupManager.h"

Player1::Player1(GameObject* parent) : Object3D(parent)
{
}

Player1::~Player1()
{
	/*if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
	if (hBlade > 0) {
		MV1DeleteModel(hBlade);
		hBlade = -1;
	}
	if (hShield > 0) {
		MV1DeleteModel(hShield);
		hShield = -1;
	}
	if (hAsteroid > 0) {
		MV1DeleteModel(hAsteroid);
		hAsteroid = -1;
	}*/
	/*DEL(hModel, 1);
	DEL(hBlade, 1);
	DEL(hShield, 1);
	DEL(hAsteroid, 1);*/
}

void Player1::Initialize()
{
	pGroupManager_ = GetParent()->FindGameObject<GroupManager>();
	auto* pPlayerGroup = pGroupManager_->CreateGroup<CharacterGroup>("playerGroup"); //グループマネージャーでplayerGroupを作成

	pTile_ = GetParent()->FindGameObject<Tile>();

	csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");
	for (int y = 1;y < csv_->GetHeight();y++) { //選択したキャラクターをplayerに生成&playerのグループに追加
		string selectCharacterName = csv_->GetString(0, y);
		Character* pCharacter = CharacterFactory::Instance().Create(selectCharacterName, pPlayerGroup);
		pPlayerGroup->Add(pCharacter);
		auto pData = pCharacter->FindGameObject<CharacterData>();
		pData->DefaultSetStatus(selectCharacterName);
		pData->DefaultSetMyTrigger(selectCharacterName);
		pData->SetTarget("enemyGroup");
		pCharacter->CreateTriggerInstance();
	}

	characterlist_ = pPlayerGroup->FindGameObjects<Character>();
	int index = 0;
	for (auto& itr : characterlist_) {
		int placementIndex = csv_->GetInt(9, index + 1);

		int x = placementIndex % MAX_MAP_WIDTH;
		int y = placementIndex / MAX_MAP_WIDTH;

		VECTOR initialPosition = pTile_->GetTilesData(x, y).position;
		itr->Set3DPosition(initialPosition);
		index++;
	}
}

void Player1::Update()
{
	characterlist_ = pGroupManager_->GetGroup("playerGroup")->FindGameObjects<Character>();
	for (auto& itr : characterlist_) {
		pSelectingCharacter_ = itr;
	}
	XMFLOAT3 c_rota = pSelectingCharacter_->GetRotate();
	VECTOR c_position = pSelectingCharacter_->Get3DPosition();
	// カメラの設定
	MATRIX mRot = MGetRotY(c_rota.y);  // 回転行列
	// 回ってないとき、プレイヤーからどれぐらい後ろ？→ベクトル
	VECTOR tmpP = VGet(0, 5, 10);
	// これに回転行列をかける
	VECTOR pRot = tmpP * mRot;
	// これにプレイヤーの座標を足すと、カメラ位置が出る
	VECTOR vRot = VGet(0, 3, -5) * mRot;

	VECTOR cam_position = c_position + pRot;
	VECTOR cam_target = c_position + vRot;
	SetCameraPositionAndTarget_UpVecY(cam_position,cam_target);
}

void Player1::Draw()
{
}