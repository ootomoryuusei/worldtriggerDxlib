#include "Player1.h"
#include "Camera.h"
#include"Tile.h"
#include "ImGui/imgui.h"

Player1::Player1(GameObject* parent) : Object3D(parent),hBlade(-1)
{
	hModel = MV1LoadModel("Assets//human.mv1");
	assert(hModel >= 0);
	hBlade = MV1LoadModel("Assets//SampleAsteroid.mv1");
	assert(hBlade >= 0);
	hPIcon = LoadGraph("Assets//Image//pIcon.png");
	assert(hPIcon >= 0);
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	/*tile = new Tile(this);
	tile->Initialize();*/
	cX = 0;
	cY = 0;
	prevX = 0;
	prevY = 0;
	prevKey = false;

	cStatus.move = 5;
	cStatus.attack = 4;
	cStatus.speed = 6;
	cStatus.defense = 10;
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
	if (hPIcon > 0) {
		DeleteGraph(hPIcon);
		hPIcon = -1;
	}
}

void Player1::Update()
{
	/*if (CheckHitKey(KEY_INPUT_W)) {
		if (prevKey == false) {
			prevY = cY;
			cY += 1;
			if (cY > z - 1) {
				cY = prevY;
			}
		}
		prevKey = true;
	}else 
	if (CheckHitKey(KEY_INPUT_S)) {
		if (prevKey == false) {
			prevY = cY;
			cY -= 1;
			if (cY < 0) {
				cY = prevY;
			}
		}
		prevKey = true;
	}else
	if (CheckHitKey(KEY_INPUT_A)) {
		if (prevKey == false) {
			prevX = cX;
			cX += 1;
			if (cX > x - 1) {
				cX = prevX;
			}
		}
		prevKey = true;
	}else
	if (CheckHitKey(KEY_INPUT_D)) {
		if (prevKey == false) {
			prevX = cX;
			cX -= 1;
			if (cX < 0) {
				cX = prevX;
			}
		}
		prevKey = true;
	}else {
		prevKey = false;
	}*/
	// カメラの設定
	MATRIX mRot = MGetRotY(rotation.y);  // 回転行列
	// 回ってないとき、プレイヤーからどれぐらい後ろ？→ベクトル
	VECTOR tmpP = VGet(0, 5, 10);
	// これに回転行列をかける
	VECTOR pRot = tmpP * mRot;
	// これにプレイヤーの座標を足すと、カメラ位置が出る
	VECTOR vRot = VGet(0,5,-5) * mRot;
	SetCameraPositionAndTarget_UpVecY(position + pRot, position + vRot);
	Tile* tile = GetParent()->FindGameObject<Tile>();
	/*position = tile->GetTileData(cY, cX);*/
	if (tile->GetWay().size() >= cStatus.move) {
		for (auto itr : tile->GetWay()) {
			Sleep(500);
			position = tile->GetTileData(itr.first, itr.second);
		}
	}
	
	ImGui::Begin("position");
	ImGui::InputFloat("X", &position.x);
	ImGui::InputFloat("Y", &position.y);
	ImGui::InputFloat("Z", &position.z);
	ImGui::End();
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

	//if (hPIcon > 0) { // モデルがロードされていれば
	//	DrawGraph(300, 300, hPIcon, TRUE);
	//};

	// サーベルの刃は、(0,0,0)～(0,-150,0)にある。これにmSabelをかけると、今の座標が手に入る
	/*DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));*/

	/*int gHandle = LoadGraph("Assets\\TestCircle.png");
	DrawCircleGauge(position.x, position.y, 50.0, gHandle, 25.0);*/
}

