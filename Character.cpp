#include "Character.h"
#include "Camera.h"
#include"Tile.h"
#include"CharacterData.h"
#include"Engine/CsvReader.h"
#include"ImGui/imgui.h"
#include<algorithm>

#include"TriggerFactory.h"

using std::clamp;

Character::Character(GameObject* parent) : Object3D(parent)
{
	csv_ = new CsvReader();

	totalTime = 10;
	elapsedTime = 0.0f;

	dir_ = VGet(1.0f, 0.0f, 0.0f);
}

Character::~Character()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Character::Initialize()
{
	tile_ = GetParent()->FindGameObject<Tile>();
	pCharacterData_ = Instantiate<CharacterData>(this);
}

void Character::Update()
{
	// カメラの設定
	MATRIX mRot = MGetRotY(rotation.y);  // 回転行列
	// 回ってないとき、プレイヤーからどれぐらい後ろ？→ベクトル
	VECTOR tmpP = VGet(0, 5, 10);
	// これに回転行列をかける
	VECTOR pRot = tmpP * mRot;
	// これにプレイヤーの座標を足すと、カメラ位置が出る
	VECTOR vRot = VGet(0, 5, -5) * mRot;
	SetCameraPositionAndTarget_UpVecY(position + pRot, position + vRot);
}

void Character::Draw()
{
	/*position = { icon->GetPIconPos().x,0.0,icon->GetPIconPos().y };*/
	//Object3D::Draw(); // 基底クラスの関数を呼ぶ→Playerキャラを描画する
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);

	/*DrawCapsule3D(position, position + VGet(0, 160, 0), 30, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);*/

	int RightHand = MV1SearchFrame(hModel, "RightHand");
	assert(RightHand >= 0);
	MATRIX mRightHand = MV1GetFrameLocalWorldMatrix(hModel, RightHand);
	//MATRIX mBlade = MV1GetFrameLocalWorldMatrix(hModel, RightHand);

	int LeftHand = MV1SearchFrame(hModel, "LeftHand");
	assert(LeftHand >= 0);
	MATRIX mLeftHand = MV1GetFrameLocalWorldMatrix(hModel, LeftHand);
	MATRIX mAsteroid = Object3D::ChangeFLOAT3ToMATRIX(VGet(mLeftHand.m[3][0], mLeftHand.m[3][1] - 0.2f, mLeftHand.m[3][2]), rotation);

	MATRIX mShield = Object3D::ChangeFLOAT3ToMATRIX({ position.x,position.y,position.z - 1.0f }, rotation);

	/*DrawMyTrigger(myTrigger_, mLeftHand, mRightHand);*/

	// サーベルの刃は、(0,0,0)～(0,-150,0)にある。これにmSabelをかけると、今の座標が手に入る
	/*DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));*/
}

void Character::ReadMyTrigger(int _createNum)
{
	/*csv_->Load("Assets/Character/SelectCharacter.csv");
	int line = 0;
	for (int x = 0;x < csv_->GetWidth(0);x++) {
		if ("MainTrigger" == csv_->GetString(x, 0)) {
			line = x;
			break;
		}
	}
	
	for (int i = 0;i < (int)MAX;i++) {
		for (int index = 0;index < 4;index++) {
			myTrigger_.myTrigger[i].trigger[index].triggerName = csv_->GetString(line, _createNum + 1);
			line++;
		}
	}*/
}

void Character::CreateTriggerInstance()
{
	/*for (int i = 0;i < (int)MAX;i++) {
		for (int index = 0;index < 4;index++) {
			string name = myTrigger_.myTrigger[i].trigger[index].triggerName;
			TriggerFactory::Instance().Create(name, this);
		}
	}*/
}

void Character::DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix)
{
}

void Character::MoveMent()
{
	Tile* pTile = GetParent()->GetParent()->FindGameObject<Tile>();
	if (!firstSet) {
		for (auto& itr : moveMent) {
			dq_moveMent.push_back(itr);
		}

		XMINT2 f_index = { dq_moveMent.front() % pTile->GetTileX(), dq_moveMent.front() / pTile->GetTileZ() };
		position = pTile->GetTilesData(f_index.x, f_index.y).position;
		firstSet = true;
		moveing = true;
	}
	if (moveing) {
		if (dq_moveMent.size() >= 2) {
			auto it = dq_moveMent.begin();
			auto startIndex = *it;
			auto targetIndex = *(++it);

			XMINT2 s_index = { startIndex % pTile->GetTileX(), startIndex / pTile->GetTileZ() };
			XMINT2 t_index = { targetIndex % pTile->GetTileX(),targetIndex / pTile->GetTileZ() };
			VECTOR start = pTile->GetTilesData(s_index.x, s_index.y).position;
			VECTOR target = pTile->GetTilesData(t_index.x, t_index.y).position;
			float percent = elapsedTime / totalTime;
			percent = clamp(percent, 0.0f, 1.0f);
			position = Lerp3D(start, target, percent);
			if (percent >= 1.0f) {
				// 移動完了 → 次の区間へ
				elapsedTime = 0.0f;
				dq_moveMent.pop_front();
			}
		}

		if (dq_moveMent.size() < 2) {
			moveing = false;
		}
		elapsedTime += Time::DeltaTime();
	}
}

bool Character::ArcInPoint(VECTOR _e_pos,float _fov)
{
	VECTOR toEnemy = ToTarget(_e_pos);
	toEnemy = VNorm(toEnemy);

	float dot = VDot(dir_, toEnemy);
	float angle = ToRad(acosf(dot));

	if (angle <= _fov) {
		return true;
	}
	return false;
}
