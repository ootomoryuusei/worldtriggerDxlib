#include "Player1.h"
#include "Camera.h"
#include"Tile.h"
#include"Icon.h"
#include"Engine/CsvReader.h"
#include"PlayScene.h"
#include"ImGui/imgui.h"

Player1::Player1(GameObject* parent) : Object3D(parent),hBlade(-1),hShield(-1)
{
	hModel = MV1LoadModel("Assets//human.mv1");
	assert(hModel >= 0);
	hBlade = MV1LoadModel("Assets//blade.mv1");
	assert(hBlade >= 0);
	hShield = MV1LoadModel("Assets//SampleSheald.mv1");
	assert(hShield >= 0);
	hAsteroid = MV1LoadModel("Assets//SampleAsteroid.mv1");
	assert(hAsteroid >= 0);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	cPos.x = 0;
	cPos.y = 0;
	prevX = 0;
	prevY = 0;
	prevKey = false;

	cStatus.move = 5;
	cStatus.attack = 4;
	cStatus.speed = 6;
	cStatus.defense = 10;

	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;

	Trigger = {};

	state_ = SELECT;
}

Player1::~Player1()
{
	if (hModel > 0) {
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
	}
	/*DEL(hModel, 1);
	DEL(hBlade, 1);
	DEL(hShield, 1);
	DEL(hAsteroid, 1);*/
}

void Player1::Update()
{
	SetMouseDispFlag(true); //マウスを表示させるフラグ関数

	GetMousePoint(&MouseX, &MouseY);
	mousePos = { (float)MouseX,(float)MouseY };

	// カメラの設定
	MATRIX mRot = MGetRotY(rotation.y);  // 回転行列
	// 回ってないとき、プレイヤーからどれぐらい後ろ？→ベクトル
	VECTOR tmpP = VGet(0, 5, 10);
	// これに回転行列をかける
	VECTOR pRot = tmpP * mRot;
	// これにプレイヤーの座標を足すと、カメラ位置が出る
	VECTOR vRot = VGet(0,5,-5) * mRot;
	SetCameraPositionAndTarget_UpVecY(position + pRot, position + vRot);
	icon = GetParent()->FindGameObject<Icon>();
	Tile* tile = GetParent()->FindGameObject<Tile>();

	/*if (CheckHitKey(KEY_INPUT_RETURN)) {
		state_ = STEP1;
		tile->SetState_(STEP1);
	}*/
}

void Player1::Draw()
{
	switch (state_)
	{
	case SELECT:
	{
		break;
	}
	case STEP1:
	{
		/*position = { icon->GetPIconPos().x,icon->GetPIconPos().y,0.0 };*/
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

		DrawMyTrigger(Trigger, mLeftHand, mRightHand);

		break;
	}
	default:
		break;
	}
	
	// サーベルの刃は、(0,0,0)～(0,-150,0)にある。これにmSabelをかけると、今の座標が手に入る
	/*DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));*/
}

void Player1::SetMyTrigger(MYTRIGGER _trigger)
{
	Trigger = _trigger;
}

void Player1::DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix)
{

	for (int i = 0; i < 4; i++) {
		if (_trigger.Main[i].IsSelected) {
			switch (_trigger.Main[i].tNum)
			{
			case FREE:
			{
				break;
			}
			case MOONBLADE:
			{
				IsLoaded(hBlade,_rightMatrix);
				break;
			}
			case SHIELD:
			{
				IsLoaded(hShield,_rightMatrix);
				break;
			}
			case ASTEROID:
			{
				IsLoaded(hAsteroid,_rightMatrix);
				break;
			}
			default:
				break;
			}
		}

		if (_trigger.Sub[i].IsSelected) {
			switch (_trigger.Sub[i].tNum)
			{
			case FREE:
			{
				break;
			}
			case MOONBLADE:
			{
				IsLoaded(hBlade, _leftMatrix);
				break;
			}
			case SHIELD:
			{
				IsLoaded(hShield, _leftMatrix);
				break;
			}
			case ASTEROID:
			{
				IsLoaded(hAsteroid, _leftMatrix);
				break;
			}
			default:
				break;
			}
		}
	}
}