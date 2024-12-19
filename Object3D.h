#pragma once
// GameObject��Object3D��Player/Ground�̊֌W�ɂ���
#include "Engine/GameObject.h"

const int FREE = 500;
const int MOONBLADE = 501;
const int SHIELD = 502;
const int ASTEROID = 503;

const int z = 11;
const int x = 11;


struct MainTrigger {
	int mt1, mt2, mt3, mt4;
};

struct SubTrigger {
	int st1, st2, st3, st4;
};

struct MyTrigger {
	MainTrigger Main;
	SubTrigger Sub;
};

struct SIZE_2D {
	int x, y;
	int halfX, halfY;
};

struct POSITION {
	int x, y;
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
/// <param name="_handle"> �n���h�� </param>
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
/// ���f�������[�h����Ă����
/// </summary>
/// <param name="_handle"> �n���h��</param>
/// <param name="_matrix"> �}�g���N�X </param>
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
/// GameObject���p������3D���f���ɕK�v�ȕϐ��ƕ`���������N���X
/// </summary>
class Object3D : public GameObject {
public:
	Object3D(GameObject* parent);
	Object3D(GameObject* parent, std::string& name);
	virtual ~Object3D();

	/// <summary>
	/// 3D���f���̕`����s��
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

	// �����̐��ʂ��H
	bool InFront(VECTOR pos, float range);

	// �����̉E���H
	bool InRight(VECTOR pos);

	// �x�N�g���̕�������
	void HeadingTo(VECTOR vec);

	// �x�N�g���Ɍ������Ĉړ�����
	void MoveTo(VECTOR vec, float speed);

	MATRIX ChangeFLOAT3ToMATRIX(FLOAT3 pos, FLOAT3 rot);
protected:
	int hModel;  // ���f���f�[�^
	VECTOR position; // ���W
	VECTOR rotation; // ��]
};
