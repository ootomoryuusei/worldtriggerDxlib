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

MATRIX Object3D::ChangeFLOAT3ToMATRIX(FLOAT3 pos, FLOAT3 rot)
{
	MATRIX mTrans = MGetTranslate(pos); // 移動行列
	MATRIX mRotX = MGetRotX(rot.x); // X軸の回転行列
	MATRIX mRotY = MGetRotY(rot.y); // Y軸の回転行列
	MATRIX mRotZ = MGetRotZ(rot.z); // Z軸の回転行列
	MATRIX matrix = mRotZ * mRotX * mRotY * mTrans;
	return matrix;
}

bool Object3D::PointInBox(XMFLOAT2 _point, XMFLOAT2 _LeftUp, XMFLOAT2 _distance)
{
	VECTOR P1P2, P2P3, P3P4, P4P1;
	VECTOR P1P, P2P, P3P, P4P;
	XMFLOAT2 P1, P2, P3, P4;

	P1 = { _LeftUp.x,  _LeftUp.y }; //左上
	P2 = { _LeftUp.x + _distance.x,  _LeftUp.y }; //右上
	P3 = { _LeftUp.x + _distance.x,  _LeftUp.y + _distance.y }; //右下
	P4 = { _LeftUp.x,  _LeftUp.y + _distance.y }; //左下

	P1P2 = { P2.x - P1.x, P2.y - P1.y };
	P2P3 = { P3.x - P2.x, P3.y - P2.y };
	P3P4 = { P4.x - P3.x, P4.y - P3.y };
	P4P1 = { P1.x - P4.x, P1.y - P4.y };

	P1P = { _point.x - P1.x,_point.y - P1.y };
	P2P = { _point.x - P2.x,_point.y - P2.y };
	P3P = { _point.x - P3.x,_point.y - P3.y };
	P4P = { _point.x - P4.x,_point.y - P4.y };

	if (VCross(P1P2, P1P).z >= 0 && VCross(P2P3, P2P).z >= 0 && VCross(P3P4, P3P).z >= 0 && VCross(P4P1, P4P).z >= 0)
	{
		return true;
	}
	return false;
}

bool Object3D::PointInQuad(XMFLOAT2 point, const array<XMFLOAT2, 4>& corners) {
	// 4つの三角形に分けて、それぞれの符号を確認（外積ベース）
	for (int i = 0; i < 4; i++) {
		int j = (i + 1) % 4;
		float dx1 = corners[j].x - corners[i].x;
		float dy1 = corners[j].y - corners[i].y;
		float dx2 = point.x - corners[i].x;
		float dy2 = point.y - corners[i].y;
		VECTOR In1, In2;
		In1 = { dx1,dy1 };
		In2 = { dx2,dy2 };
		if (VCross(In1,In2).z < 0) return false;
	}
	return true;
}
