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
	auto* pGroupManager = GetParent()->FindGameObject<GroupManager>();
	auto* pPlayerGroup = pGroupManager->CreateGroup<CharacterGroup>("playerGroup");

	pTile_ = GetParent()->FindGameObject<Tile>();

	csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");
	for (int y = 1;y < csv_->GetHeight();y++) {
		string selectCharacterName = csv_->GetString(0, y);
		Character* pCharacter = CharacterFactory::Instance().Create(selectCharacterName, pPlayerGroup);
		auto pData = pCharacter->FindGameObject<CharacterData>();
		pData->SetName(selectCharacterName);
		pData->DefaultSetStatus(selectCharacterName);
		pData->DefaultSetMyTrigger(selectCharacterName);
	}

	list<Character*> characterlist = pPlayerGroup->FindGameObjects<Character>();
	int index = 0;
	for (auto& itr : characterlist) {
		int placementIndex = csv_->GetInt(9, index + 1);

		int x = placementIndex % MAX_MAP_WIDTH;
		int y = placementIndex / MAX_MAP_WIDTH;

		VECTOR initialPosition = pTile_->GetTilesData(x, y).position;
		itr->Set3DPosition(initialPosition);
		itr->ReadMyTrigger(index);
		index++;
	}
}

void Player1::Update()
{
	//characters_ = pGroup_->FindGameObjects<Character>();
	//for (auto& itr : characters_) {
	//}
	//XMFLOAT3 c_rota = pSelectingCharacter_->GetRotate();
	//VECTOR c_position = pSelectingCharacter_->Get3DPosition();
	//// カメラの設定
	//MATRIX mRot = MGetRotY(c_rota.y);  // 回転行列
	//// 回ってないとき、プレイヤーからどれぐらい後ろ？→ベクトル
	//VECTOR tmpP = VGet(0, 5, 10);
	//// これに回転行列をかける
	//VECTOR pRot = tmpP * mRot;
	//// これにプレイヤーの座標を足すと、カメラ位置が出る
	//VECTOR vRot = VGet(0, 5, -5) * mRot;

	//VECTOR cam_position = c_position + pRot;
	//VECTOR cam_target = c_position + vRot;
	//SetCameraPositionAndTarget_UpVecY(cam_position,cam_target);
}

void Player1::Draw()
{
}