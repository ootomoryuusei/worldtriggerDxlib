#pragma once
// GameObject→Object3D→Player/Groundの関係にする
#include "Engine/GameObject.h"

using std::string;

//const int FREE = 500;
//const int MOONBLADE = 501;
//const int SHIELD = 502;
//const int ASTEROID = 503;

const int z = 11;
const int x = 11;
const int MAX_SELECT_CHARACTER = 3;
const int MAX_TRIGGER_HANDS = 2;
const int MAX_CAN_SET_TRIGGER = 4;

//enum PLAY_SCENE_STATE {
//	SELECT,
//	STEP1,
//	MAXS
//};

struct TRIGGER {
	string trigger; //トリガー名
	bool IsSelected; //選択されているかどうか
	float angle; //アングル
	float startAngle; //はじめのアングル
	float rangeSize; //射程や警戒範囲の長さ
	int tNum; //triggerナンバー
};

struct MYTRIGGER {
	TRIGGER Main[4];
	TRIGGER Sub[4];
};

struct SIZE_2D {
	int x, y, halfX, halfY;
};

struct SIZE_F_2D {
	float x, y, halfX, halfY;
};

struct TILEDATA {
	VECTOR position;
	int num;
};

struct CHARACTER_STATUS
{
	int move, attack, speed, defense;
};

/// <summary>
/// 
/// </summary>
/// <param name="_handle"> ハンドル </param>
/// <param name="type"> graph : 0 , model : 1</param>
inline void DEL(int _handle ,int type) {
	switch (type) {
	case 0:
	{
		if (_handle > 0) {
			DeleteGraph(_handle);
			_handle = -1;
		}
		break;
	}
	case 1: 
	{
		if (_handle > 0) {
			MV1DeleteModel(_handle);
			_handle = -1;
		}
		break;
	}
	default:
		break;
	}
}

/// <summary>
/// モデルがロードされていれば
/// </summary>
/// <param name="_handle"> ハンドル</param>
/// <param name="_matrix"> マトリクス </param>
/// <param name="type"> graph : 0 , model : 1 </param>
inline void IsLoaded(int _handle, MATRIX _matrix , int type = 1) {
	switch (type) {
	case 0:
	{
		if (_handle > 0) {
		}
		break;
	}
	case 1:
	{
		if (_handle > 0) {
			MV1SetMatrix(_handle,_matrix);
			MV1DrawModel(_handle);
		}
		break;
	}
	default:
		break;
	}
}



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

	MATRIX ChangeFLOAT3ToMATRIX(FLOAT3 pos, FLOAT3 rot);

	/// <summary>
	/// 点と短形の当たり判定
	/// </summary>
	/// <param name="_point"> 点 </param>
	/// <param name="_leftUp"> 短形の左上座標 </param>
	/// <param name="_distance"> 短形の幅(x)と高さ(y) </param>
	/// <returns></returns>
	bool PointInBox(XMFLOAT2 point, XMFLOAT2 _leftUp, XMFLOAT2 _distance);

	void SetState_(int _state) { state_ = _state; }

	VECTOR Get3DPosition() { return position; }
	void Set3DPosition(VECTOR _position) { position = _position; }
protected:
	int hModel;  // モデルデータ
	VECTOR position; // 座標
	VECTOR rotation; // 回転
	int state_;
};
