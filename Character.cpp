#include "Character.h"
#include "Camera.h"
#include"Tiles.h"
#include"CharacterData.h"
#include"TriggerData.h"
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

	dir_ = VGet(0.0f, 0.0f, 1.0f);
}

Character::~Character()
{
	if (hModel_ > 0) {
		MV1DeleteModel(hModel_);
		hModel_ = -1;
	}
}

void Character::Initialize()
{
	pTiles_ = GetParent()->GetParent()->GetParent()->FindGameObject<Tiles>();
	pData_ = Instantiate<CharacterData>(this);
}

void Character::Update()
{
	int RightHand = MV1SearchFrame(hModel_, "RightHand");
	assert(RightHand >= 0);
	VECTOR righthand_position = MV1GetFramePosition(hModel_, RightHand);
	handsPostion_[RIGHT] = righthand_position;
	//MATRIX mBlade = MV1GetFrameLocalWorldMatrix(hModel, RightHand);

	int LeftHand = MV1SearchFrame(hModel_, "LeftHand");
	assert(LeftHand >= 0);
	VECTOR lefthand_postion = MV1GetFramePosition(hModel_, LeftHand);
	handsPostion_[LEFT] = lefthand_postion;

	for (int hands = 0;hands < static_cast<size_t>(HANDS::MAX);hands++) {
		for (int i = 0;i < 4;i++) {
			if (trigger_[hands][i] != nullptr) {
				trigger_[hands][i]->SetPosition(handsPostion_[hands]);
			}
		}
	}

	switch (step_)
	{
	case STEP::FIRST: break;
	case STEP::SECONDE: break;
	case STEP::THIRD:
	{
		MoveMent();
		break;
	}
	default:
		break;
	}
	/*MATRIX mAsteroid = Object3D::ChangeFLOAT3ToMATRIX(VGet(mLeftHand.m[3][0], mLeftHand.m[3][1] - 0.2f, mLeftHand.m[3][2]), rotation);*/
	Object3D::Update();
}

void Character::Draw()
{
	//Object3D::Draw(); // 基底クラスの関数を呼ぶ→Playerキャラを描画する
	MATRIX mModel = Object3D::ToMATRIX(position_, rotation_);
	MV1SetMatrix(hModel_, mModel);
	MV1DrawModel(hModel_);

	/*DrawCapsule3D(position, position + VGet(0, 160, 0), 30, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);*/

	

	MATRIX mShield = Object3D::ToMATRIX({ position_.x,position_.y,position_.z - 1.0f }, rotation_);

	/*DrawMyTrigger(myTrigger_, mLeftHand, mRightHand);*/

	// サーベルの刃は、(0,0,0)～(0,-150,0)にある。これにmSabelをかけると、今の座標が手に入る
	/*DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));*/
}

void Character::CreateTriggerInstance()
{
	for (int hands = 0;hands < static_cast<size_t>(HANDS::MAX);hands++) { //characterが持つtriggerを生成
		for (int i = 0;i < 4;i++) {
			MYTRIGGER myTrigger = pData_->GetMyTrigger();
			string trigger_name = myTrigger.myTrigger[hands].trigger[i].triggerName;
			auto ptr = TriggerFactory::Instance().Create(trigger_name, this);
			if (ptr != nullptr) { //生成したものがnull(FREE)以外ならtriggerにdataとtargetをセットする
				auto data = ptr->GetTriggerData();
				data->SetTriggerData(pData_->GetMyTrigger().myTrigger[hands].trigger[i]);
				data->SetTarget(pData_->GetTarget());
				trigger_[hands][i] = ptr;
			}
		}
	}
	hands_ = { trigger_[RIGHT][0],trigger_[LEFT][0] };
	for (int hands = 0; hands < static_cast<size_t>(HANDS::MAX); hands++) {
		if (hands_[hands] == nullptr) continue;
			hands_[hands]->Enter();
			hands_[hands]->Visible();
	}
}

void Character::DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix)
{
}

void Character::MoveMent()
{
	if (!firstSet) {
		for (auto& itr : moveMent) {
			dq_moveMent.push_back(itr);
		}

		VECTOR f_offset = moveMent.front();
		transform_.position_ = pTiles_->GetpTiles()[f_offset.y][f_offset.x]->GetPosition();
		firstSet = true;
		moveing = true;
	}
	if (moveing) {
		if (dq_moveMent.size() >= 2) {
			auto it = dq_moveMent.begin();
			auto s_offset = *it;
			auto t_offset = *(++it);

			XMFLOAT3 start = pTiles_->GetpTiles()[s_offset.y][s_offset.x]->GetPosition();
			XMFLOAT3 target = pTiles_->GetpTiles()[t_offset.y][t_offset.x]->GetPosition();
			float percent = elapsedTime / totalTime;
			percent = clamp(percent, 0.0f, 1.0f);
			transform_.position_ = Lerp3D(start, target, percent);
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

void Character::EnemyMoveMent()
{
}
