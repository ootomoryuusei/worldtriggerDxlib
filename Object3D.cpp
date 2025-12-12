#include "Object3D.h"
#include"Raycaster3D.h"

void Object3D::RegisterToRaycaster()
{
	raycaster3D_ = GetParent()->FindGameObject<InputManager>()->GetRaycastManager()->GetRaycaster3D();
	if (!raycaster3D_) return; // Raycaster3Dが存在しない場合は登録しない

	auto& list = raycaster3D_->objects_;
	if (std::find(list.begin(), list.end(), this) == list.end()) list.push_back(this);
}

void Object3D::UnregisterFromRaycaster()
{
	if (!raycaster3D_) return; // Raycaster3Dが存在しない場合は登録しない
	auto& list = raycaster3D_->objects_;
	list.erase(
		std::remove(list.begin(), list.end(), this),
		list.end()
	);
}

Object3D::Object3D(GameObject* parent) : GameObject(parent)
{
	hModel_ = -1;
	position_ = VGet(0, 0, 0);
	rotation_ = VGet(0, 0, 0);
}

Object3D::Object3D(GameObject* parent,const std::string& name) : GameObject(parent, name)
{
	hModel_ = -1;
	position_ = VGet(0, 0, 0);
	rotation_ = VGet(0, 0, 0);
}

Object3D::~Object3D()
{
	if (hModel_ > 0) { // モデルがロードされていれば
		MV1DeleteModel(hModel_);
		hModel_ = -1;
	}
}

void Object3D::Initialize()
{
	RegisterToRaycaster(); // Raycaster3Dに登録
}

void Object3D::Update()
{
	if (hModel_ < 0) return; //モデルがロード済みならば
	position_ = VGet(transform_.position_.x, transform_.position_.y, transform_.position_.z);
	rotation_ = VGet(transform_.rotate_.x, transform_.rotate_.y, transform_.rotate_.z);
	matrix_ = ToMATRIX(position_, rotation_);
}

void Object3D::Draw()
{
	if (hModel_ < 0) return; // モデルがロード済みならば
	MV1SetMatrix(hModel_, matrix_);
	MV1DrawModel(hModel_);
}

void Object3D::Release()
{
	UnregisterFromRaycaster(); // Raycaster3Dから登録解除
}

void Object3D::LoadModel(const string& path)
{
	hModel_ = MV1LoadModel(path.c_str());
	assert(hModel_ >= 0); //アサーション
	size_ = CalculateModelSize();
}

bool Object3D::Raycast(const VECTOR& rayOrigin, const VECTOR& rayDir, float& outDist)
{
	if (hModel_ < 0) return false;

	VECTOR rayEnd = rayOrigin + rayDir * 10000.0f; // 適当な長さのレイを作成

	MV1_COLL_RESULT_POLY res = MV1CollCheck_Line(hModel_,-1,rayOrigin, rayEnd);

	if (res.HitFlag) {
		outDist = res.HitPosition.z - rayOrigin.z; // レイの始点からの距離を計算
		return true;
	}
	return false;
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
	rotation_.y = atan2(vec.x, vec.y);
}

void Object3D::MoveTo(VECTOR vec, float speed)
{
	position_ += VNorm(vec) * speed;
}

MATRIX Object3D::ToMATRIX(FLOAT3 pos, FLOAT3 rot)
{
	MATRIX mTrans = MGetTranslate(pos); // 移動行列
	MATRIX mRotX = MGetRotX(rot.x); // X軸の回転行列
	MATRIX mRotY = MGetRotY(rot.y); // Y軸の回転行列
	MATRIX mRotZ = MGetRotZ(rot.z); // Z軸の回転行列
	MATRIX matrix = mRotZ * mRotX * mRotY * mTrans;
	return matrix;
}

VECTOR Object3D::CalculateModelSize()
{
	if (hModel_ <= 0) {
		return {0,0,0};
	}
	
	VECTOR overallMin = { FLT_MAX,FLT_MAX,FLT_MAX };
	VECTOR overallMax = { -FLT_MAX,-FLT_MAX,-FLT_MAX };

	VECTOR scale = MV1GetScale(hModel_);
	int meshCount = MV1GetMeshNum(hModel_);

	for (int i = 0;i < meshCount;i++) {
		VECTOR minV = MV1GetMeshMinPosition(hModel_, i);
		VECTOR maxV = MV1GetMeshMaxPosition(hModel_, i);

		if (minV.x < overallMin.x) overallMin.x = minV.x;
		if (minV.y < overallMin.y) overallMin.y = minV.y;
		if (minV.z < overallMin.z) overallMin.z = minV.z;

		if (maxV.x > overallMax.x) overallMax.x = maxV.x;
		if (maxV.y > overallMax.y) overallMax.y = maxV.y;
		if (maxV.z > overallMax.z) overallMax.z = maxV.z;
	}

	VECTOR modelSize;
	modelSize = (overallMax - overallMin) * scale;

	return modelSize;
}
