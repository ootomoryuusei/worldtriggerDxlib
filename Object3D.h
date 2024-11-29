#pragma once
// GameObject→Object3D→Player/Groundの関係にする
#include "Engine/GameObject.h"

inline float ToRad(float deg) { return deg * XM_PI / 180.0f; }

inline VECTOR operator +(const VECTOR& a, const VECTOR& b) {
	return VAdd(a, b);
}

inline VECTOR operator -(const VECTOR& a, const VECTOR& b) {
	return VSub(a, b);
}

inline const VECTOR& operator +=(VECTOR& a, const VECTOR& b) {
	return a = VAdd(a, b);
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
public:
	Object3D(GameObject* parent);
	Object3D(GameObject* parent, std::string& name);
	virtual ~Object3D();

	/// <summary>
	/// 3Dモデルの描画を行う
	/// </summary>
	virtual void Draw() override;

	VECTOR ToTarget(VECTOR targetPos) {
		return targetPos - position;
	}

	VECTOR FrontVec() {
		return VGet(0, 0, 1) * MGetRotY(rotation.y);
	}

	VECTOR RightVec() {
		return VGet(1, 0, 0) * MGetRotY(rotation.y);
	}

	VECTOR GetPosition() { return position; }

	VECTOR GetRotation() { return rotation; }

	// 自分の正面か？
	bool InFront(VECTOR pos, float range);

	// 自分の右か？
	bool InRight(VECTOR pos);

	// ベクトルの方を向く
	void HeadingTo(VECTOR vec);

	// ベクトルに向かって移動する
	void MoveTo(VECTOR vec, float speed);
protected:
	int hModel;  // モデルデータ
	VECTOR position; // 座標
	VECTOR rotation; // 回転
};
