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
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Character::Initialize()
{
	pTiles_ = GetParent()->GetParent()->GetParent()->FindGameObject<Tiles>();
	pData_ = Instantiate<CharacterData>(this);
}

void Character::Update()
{
	int RightHand = MV1SearchFrame(hModel, "RightHand");
	assert(RightHand >= 0);
	VECTOR righthand_position = MV1GetFramePosition(hModel, RightHand);
	handsPostion_[RIGHT] = righthand_position;
	//MATRIX mBlade = MV1GetFrameLocalWorldMatrix(hModel, RightHand);

	int LeftHand = MV1SearchFrame(hModel, "LeftHand");
	assert(LeftHand >= 0);
	VECTOR lefthand_postion = MV1GetFramePosition(hModel, LeftHand);
	handsPostion_[LEFT] = lefthand_postion;

	for (int hands = 0;hands < MAX;hands++) {
		for (int i = 0;i < 4;i++) {
			if (trigger_[hands][i] != nullptr) {
				trigger_[hands][i]->Set3DPosition(handsPostion_[hands]);
			}
		}
	}

	switch (state_)
	{
	case FIRST: break;
	case SECONDE: break;
	case THIRD:
	{
		MoveMent();
		break;
	}
	default:
		break;
	}
	/*MATRIX mAsteroid = Object3D::ChangeFLOAT3ToMATRIX(VGet(mLeftHand.m[3][0], mLeftHand.m[3][1] - 0.2f, mLeftHand.m[3][2]), rotation);*/
}

void Character::Draw()
{
	//Object3D::Draw(); // ���N���X�̊֐����Ăԁ�Player�L������`�悷��
	MATRIX mModel = Object3D::ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);

	/*DrawCapsule3D(position, position + VGet(0, 160, 0), 30, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);*/

	

	MATRIX mShield = Object3D::ToMATRIX({ position.x,position.y,position.z - 1.0f }, rotation);

	/*DrawMyTrigger(myTrigger_, mLeftHand, mRightHand);*/

	// �T�[�x���̐n�́A(0,0,0)�`(0,-150,0)�ɂ���B�����mSabel��������ƁA���̍��W����ɓ���
	/*DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));*/
}

void Character::CreateTriggerInstance()
{
	for (int hands = 0;hands < MAX;hands++) { //character������trigger�𐶐�
		for (int i = 0;i < 4;i++) {
			MYTRIGGER myTrigger = pData_->GetMyTrigger();
			string trigger_name = myTrigger.myTrigger[hands].trigger[i].triggerName;
			auto ptr = TriggerFactory::Instance().Create(trigger_name, this);
			if (ptr != nullptr) { //�����������̂�null(FREE)�ȊO�Ȃ�trigger��data��target���Z�b�g����
				auto data = ptr->GetTriggerData();
				data->SetTriggerData(pData_->GetMyTrigger().myTrigger[hands].trigger[i]);
				data->SetTarget(pData_->GetTarget());
				trigger_[hands][i] = ptr;
			}
		}
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

		XMINT2 f_index = { dq_moveMent.front() % MAX_MAP_WIDTH, dq_moveMent.front() / MAX_MAP_HIGHT };
		position = pTiles_->GetpTiles()[f_index.x][f_index.y]->Get3DPosition();
		firstSet = true;
		moveing = true;
	}
	if (moveing) {
		if (dq_moveMent.size() >= 2) {
			auto it = dq_moveMent.begin();
			auto startIndex = *it;
			auto targetIndex = *(++it);

			XMINT2 s_index = { startIndex % MAX_MAP_WIDTH, startIndex / MAX_MAP_HIGHT };
			XMINT2 t_index = { targetIndex % MAX_MAP_WIDTH,targetIndex / MAX_MAP_HIGHT };
			VECTOR start = pTiles_->GetpTiles()[s_index.x][s_index.y]->Get3DPosition();
			VECTOR target = pTiles_->GetpTiles()[t_index.x][t_index.y]->Get3DPosition();
			float percent = elapsedTime / totalTime;
			percent = clamp(percent, 0.0f, 1.0f);
			position = Lerp3D(start, target, percent);
			if (percent >= 1.0f) {
				// �ړ����� �� ���̋�Ԃ�
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
