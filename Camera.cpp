#include "Camera.h"
#include "Player.h"
#include"Player1.h"

Camera::Camera(GameObject* parent) : Object3D(parent)
{
	//Player* pPlayer = GetParent()->FindGameObject<Player>();
	//VECTOR pPos = pPlayer->GetPosition(); // プレイヤーの位置
	//float rotY = pPlayer->GetRotate().y; // プレイヤーのY回転
	//// とりあえず、初期値positionは、プレイヤーから(0,200,-300)、lookTargetは、プレイヤーから(0,100,300)
	//position = VGet(0, 200, -300) * MGetRotY(rotY) + pPos;
	//lookTarget = VGet(0, 100, 300) * MGetRotY(rotY) + pPos;
	//rotation = VGet(0, 0, 0);
	Player1* pPlayer1 = GetParent()->FindGameObject<Player1>();
	VECTOR pPos = pPlayer1->GetPosition();
	float rotY = pPlayer1->GetRotate().y;
	position = VGet(0, 200, -300) * MGetRotY(rotY) + pPos;
	lookTarget = VGet(0, 100, 300) * MGetRotY(rotY) + pPos;
	rotation = VGet(0, 0, 0);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (CheckHitKey(KEY_INPUT_UP)) {
		rotation.x += XMConvertToRadians(180.0f) * Time::DeltaTime();
		if (rotation.x >= XMConvertToRadians(80.0f)) {
			rotation.x = XMConvertToRadians(80.0f);
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		rotation.x -= XMConvertToRadians(180.0f) * Time::DeltaTime();
		if (rotation.x <= XMConvertToRadians(-60.0f)) {
			rotation.x = XMConvertToRadians(-60.0f);
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		rotation.y += XMConvertToRadians(180.0f) * Time::DeltaTime();
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		rotation.y -= XMConvertToRadians(180.0f) * Time::DeltaTime();
	}

	Player1* pPlayer1 = GetParent()->FindGameObject<Player1>();
	VECTOR pPos = pPlayer1->GetPosition(); // プレイヤーの位置
	float rotY = pPlayer1->GetRotation().y; // プレイヤーのY回転

	// カメラ操作の時の中心座標を求める
	VECTOR center = pPos + VGet(0, 150, 0); // 首の高さ
	position = VGet(100, 50, -200) * MGetRotX(rotation.x) * MGetRotY(rotation.y) + center;
	lookTarget = VGet(0,-50, 300) * MGetRotX(rotation.x) * MGetRotY(rotation.y) + center;

	if (vibTimer > 0.0f) {
		vibTimer -= Time::DeltaTime();
		if (vibTimer <= 0.0f)
			vibTimer = 0.0f;
	}
	float val = sinf(vibTimer*2.0) * vibTimer * 2.0f;
	if (val > vibTimer / 2.0f)
		val = vibTimer;
	else if (val < -vibTimer / 2.0f)
		val = -vibTimer;
	else
		val = 0;
	vibValue = vibParam * val;
	position += vibValue;
	lookTarget += vibValue;
}

void Camera::Draw()
{
	SetCameraPositionAndTarget_UpVecY(position, lookTarget);
}

void Camera::Vibration(VECTOR v)
{
	vibTimer = 0.5f; // 揺れ時間
	vibParam = v;
}
