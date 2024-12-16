#include "Player1.h"
#include "Camera.h"
#include"Tile.h"
#include"Icon.h"

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
	/*hPIcon = LoadGraph("Assets//Image//pIcon.png");
	assert(hPIcon >= 0);*/
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
	/*if (hPIcon > 0) {
		DeleteGraph(hPIcon);
		hPIcon = -1;
	}*/
}

void Player1::Update()
{
	
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
	if (icon->GetCompWay()) {
		time += flame;  // 時間を増加させる
		if (time > movetime) {  // 一定の時間が経過した場合
			static size_t index = 0;  // 現在処理しているイテレーターのインデックス
			const auto& way = icon->GetWay();

			// イテレーターが範囲内にある場合に処理
			if (index < way.size()) {
				// 現在の位置を取得
				position = tile->GetTilesData(way[index].y, way[index].x).position;
				// インデックスを次に進める
				++index;
			}
			else {
				// すべての処理が終わった場合、インデックスをリセット
				icon->SetCompWay(false);
				icon->GetWay().clear();
			}
			time = 0.0f;  // 時間リセット
		}
	}
	
	
}

void Player1::Draw()
{
	//Object3D::Draw(); // 基底クラスの関数を呼ぶ→Playerキャラを描画する
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position,rotation);
	MV1SetMatrix(hModel,mModel);
	MV1DrawModel(hModel);

	/*DrawCapsule3D(position, position + VGet(0, 160, 0), 30, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);*/

	int RightHand = MV1SearchFrame(hModel, "RightHand");
	assert(RightHand >= 0);
	MATRIX mBlade = MV1GetFrameLocalWorldMatrix(hModel, RightHand);


    if (hBlade > 0) { // モデルがロードされていれば
		// サーベルを描画する
		MV1SetMatrix(hBlade, mBlade);
		MV1DrawModel(hBlade);
	};

	int LeftHand = MV1SearchFrame(hModel, "LeftHand");
	assert(LeftHand >= 0);
	MATRIX mLeftHand = MV1GetFrameLocalWorldMatrix(hModel, LeftHand);
	MATRIX mAsteroid = Object3D::ChangeFLOAT3ToMATRIX(VGet(mLeftHand.m[3][0],mLeftHand.m[3][1] - 0.2f, mLeftHand.m[3][2]),rotation);

	if (hAsteroid > 0) {
		MV1SetMatrix(hAsteroid, mAsteroid);
		MV1DrawModel(hAsteroid);
	}

	MATRIX mShield = Object3D::ChangeFLOAT3ToMATRIX({ position.x,position.y,position.z - 1.0f }, rotation);
	if (hShield > 0) {
		MV1SetMatrix(hShield,mShield);
		MV1DrawModel(hShield);
	}

	//if (hPIcon > 0) { // モデルがロードされていれば
	//	DrawGraph(300, 300, hPIcon, TRUE);
	//};

	// サーベルの刃は、(0,0,0)～(0,-150,0)にある。これにmSabelをかけると、今の座標が手に入る
	/*DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));*/

	/*int gHandle = LoadGraph("Assets\\TestCircle.png");
	DrawCircleGauge(position.x, position.y, 50.0, gHandle, 25.0);*/
}

