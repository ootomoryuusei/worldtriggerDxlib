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
	// カメラの設定
	MATRIX mRot = MGetRotY(rotation.y);  // 回転行列
	// 回ってないとき、プレイヤーからどれぐらい後ろ？→ベクトル
	VECTOR tmpP = VGet(0, 200, -300);
	// これに回転行列をかける
	VECTOR pRot = tmpP * mRot;
	// これにプレイヤーの座標を足すと、カメラ位置が出る
	VECTOR vRot = VGet(0, 100, 300) * mRot;
	SetCameraPositionAndTarget_UpVecY(position + pRot, position + vRot);
}

void Player1::Draw()
{
	Object3D::Draw(); // 基底クラスの関数を呼ぶ→Playerキャラを描画する

	/*DrawCapsule3D(position, position + VGet(0, 160, 0), 30, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);*/

    if (hBlade > 0) { // モデルがロードされていれば
		// サーベルを描画する
		MV1SetMatrix(hBlade,ChangeFLOAT3ToMATRIX(position,rotation));
		MV1DrawModel(hBlade); ;
	};

	// サーベルの刃は、(0,0,0)～(0,-150,0)にある。これにmSabelをかけると、今の座標が手に入る
	DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));

	int gHandle = LoadGraph("Assets\\TestCircle.png");
	DrawCircleGauge(position.x, position.y, 50.0, gHandle, 25.0);
}

MATRIX Player1::ChangeFLOAT3ToMATRIX(FLOAT3 pos, FLOAT3 rot)
{
	MATRIX mTrans = MGetTranslate(pos); // 移動行列
	MATRIX mRotX = MGetRotX(rot.x); // X軸の回転行列
	MATRIX mRotY = MGetRotY(rot.y); // Y軸の回転行列
	MATRIX mRotZ = MGetRotZ(rot.z); // Z軸の回転行列
	MATRIX matrix = mRotZ * mRotX * mRotY * mTrans;
	return matrix;
}