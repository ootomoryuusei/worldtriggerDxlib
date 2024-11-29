#include "Object3D.h"

Object3D::Object3D(GameObject* parent) : GameObject(parent)
{
	hModel = -1;
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
}

Object3D::Object3D(GameObject* parent, std::string& name) : GameObject(parent, name)
{
	hModel = -1;
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
}

Object3D::~Object3D()
{
	if (hModel > 0) { // モデルがロードされていれば
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Object3D::Draw()
{
	if (hModel > 0) { // モデルがロードされていれば
		MATRIX mTrans = MGetTranslate(position); // 移動行列
		MATRIX mRotX = MGetRotX(rotation.x); // X軸の回転行列
		MATRIX mRotY = MGetRotY(rotation.y); // Y軸の回転行列
		MATRIX mRotZ = MGetRotZ(rotation.z); // Z軸の回転行列
		MATRIX m = mRotZ * mRotX * mRotY * mTrans;
		MV1SetMatrix(hModel, m);
		MV1DrawModel(hModel);
	}
}

bool Object3D::InFront(VECTOR pos, float range)
//                     相手の座標  範囲（ラジアン）
{
	VECTOR targetVec = ToTarget(pos); // 相手へのベクトルを求める（相手の座標ー自分の座標）
	targetVec = VNorm(targetVec); // これの長さを１にする
	VECTOR front = FrontVec();// 自分の正面ベクトルを作る（VGet(0,0,1)*Y軸回転行列）
	// （正面ベクトルはすでに長さが１）
	float ip = VDot(targetVec, front);// ２つのベクトルの内積をとって、角度がrangeより小さければtrueを返す
	if (ip >= cosf(range))
		return true;
	return false;
}

bool Object3D::InRight(VECTOR pos)
{
	return VDot(ToTarget(pos), RightVec()) >= 0.0f;
}

void Object3D::HeadingTo(VECTOR vec)
{
	rotation.y = atan2(vec.x, vec.y);
}

void Object3D::MoveTo(VECTOR vec, float speed)
{
	position += VNorm(vec) * speed;
}
