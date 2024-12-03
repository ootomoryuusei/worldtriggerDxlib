#include "Player1.h"
#include "Camera.h"

Player1::Player1(GameObject* parent) : Object3D(parent),hBlade(-1)
{
	hModel = MV1LoadModel("Assets//human.mv1");
	assert(hModel >= 0);
	hBlade = MV1LoadModel("Assets//Blade.mv1");
	assert(hBlade >= 0);
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
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
}

void Player1::Update()
{
	//// カメラの設定
	//MATRIX mRot = MGetRotY(rotation.y);  // 回転行列
	//// 回ってないとき、プレイヤーからどれぐらい後ろ？→ベクトル
	//VECTOR tmpP = VGet(0, 65, 0);
	//// これに回転行列をかける
	//VECTOR pRot = tmpP * mRot;
	//// これにプレイヤーの座標を足すと、カメラ位置が出る
	//VECTOR vRot = VGet(0, 0, 3) * mRot;
	//SetCameraPositionAndTarget_UpVecY(position + pRot, position + vRot);
}

void Player1::Draw()
{
	Object3D::Draw(); // 基底クラスの関数を呼ぶ→Playerキャラを描画する

	/*DrawCapsule3D(position, position + VGet(0, 160, 0), 30, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);*/

	int RightHand = MV1SearchFrame(hModel, "RightHand");
	assert(RightHand >= 0);
	MATRIX mBlade = MV1GetFrameLocalWorldMatrix(hModel, RightHand);


    if (hBlade > 0) { // モデルがロードされていれば
		// サーベルを描画する
	/*	MV1SetMatrix(hBlade,ChangeFLOAT3ToMATRIX(position,rotation));
		MV1DrawModel(hBlade); ;*/
		// サーベルを描画する
		MV1SetMatrix(hBlade, mBlade);
		MV1DrawModel(hBlade);
	};

	// サーベルの刃は、(0,0,0)～(0,-150,0)にある。これにmSabelをかけると、今の座標が手に入る
	/*DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));*/

	/*int gHandle = LoadGraph("Assets\\TestCircle.png");
	DrawCircleGauge(position.x, position.y, 50.0, gHandle, 25.0);*/
}

