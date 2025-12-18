#pragma once
#include "Engine/GameObject.h"
#include"GameInfo.h"
#include"InputManager.h"
#include<array>
#include<unordered_map>

class Raycaster3D;

using std::string;
using std::array;
using std::unordered_map;

inline void DEL(int _handle) {
	if (_handle > 0) {
		MV1DeleteModel(_handle);
		_handle = -1;
	}
}

inline void IsLoaded(int _handle, MATRIX _matrix) {
	if (_handle > 0) {
		MV1SetMatrix(_handle, _matrix);
		MV1DrawModel(_handle);
	}
}

/// <summary>
/// 度に変換
/// </summary>
/// <param name="deg"></param>
/// <returns></returns>
inline float ToRad(float deg) { return deg * XM_PI / 180.0f; }

inline VECTOR operator +(const VECTOR& a, const VECTOR& b) {
	return VAdd(a, b);
}

/// <summary>
///　ベクトル同士の引き算
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
inline VECTOR operator -(const VECTOR& a, const VECTOR& b) { 
	return VSub(a, b);
}

inline const VECTOR& operator +=(VECTOR& a, const VECTOR& b) {
	return a = VAdd(a, b);
}

inline VECTOR operator *(const VECTOR& a,const VECTOR& b) {
	return VECTOR{ a.x * b.x,a.y * b.y,a.z * b.z };
}

inline VECTOR operator *(const VECTOR& a, const MATRIX& m) {
	return VTransform(a, m);
}

inline MATRIX operator *(const MATRIX& m1, const MATRIX& m2) {
	return MMult(m1, m2);
}

inline VECTOR operator *(const VECTOR& a, float sc) {
	return VScale(a, sc);
}

/// <summary>
/// GameObjectを継承して3Dモデルに必要な変数と描画をする基底クラス
/// </summary>
class Object3D : public GameObject {
protected:
	int hModel_;  // モデルハンドル
	VECTOR position_; // 座標
	VECTOR rotation_; // 回転
	VECTOR scale_; // スケール
	MATRIX matrix_; //　行列
	/*STEP step_;*/

	Raycaster3D* raycaster3D_; // Raycaster3D

	void RegisterToRaycaster(); // Raycasterに登録
	void UnregisterFromRaycaster(); // Raycasterから登録解除
public:
	Object3D(GameObject* parent);
	Object3D(GameObject* parent,const std::string& name);
	virtual ~Object3D();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;

	void LoadModel(const string& path);

	bool Raycast(const VECTOR& rayOrigin, const VECTOR& rayDir, float& outDist);

	VECTOR ToTarget(XMFLOAT3 targetPos) {
		XMFLOAT3 toTarget = targetPos - transform_.position_;
		return VGet(toTarget.x,toTarget.y,toTarget.z);
	}

	VECTOR FrontVec() {
		return VGet(0, 0, 1) * MGetRotY(position_.y);
	}

	VECTOR RightVec() {
		return VGet(1, 0, 0) * MGetRotY(position_.y);
	}

	// 自分の正面か？
	bool InFront(XMFLOAT3 pos, float range);

	// 自分の右か？
	bool InRight(XMFLOAT3 pos);

	// ベクトルの方を向く
	void HeadingTo(VECTOR vec);

	// ベクトルに向かって移動する
	void MoveTo(VECTOR vec, float speed);

	// マトリクスへ変換
	MATRIX ToMATRIX(FLOAT3 pos, FLOAT3 rot);

	/*void SetStep(STEP _step) { step_ = _step; }
	int GetStep() { return step_; }*/

	XMFLOAT3 CalculateModelSize();
};
