#pragma once
// GameObject��Object3D��Player/Ground�̊֌W�ɂ���
#include "Engine/GameObject.h"
#include<array>
#include<unordered_map>

using std::string;
using std::array;
using std::unordered_map;

const int MAX_SELECT_CHARACTER = 3;
const int MAX_TRIGGER_HANDS = 2;
const int MAX_CAN_SET_TRIGGER = 4;

struct ARC_DATA {
	float percent;
	float startPercent;
	float angle;
	float rangeSize;
};

struct TRIGGER {
	string triggerName; //�g���K�[��
	bool IsSelected; //�I������Ă��邩�ǂ���
	ARC_DATA arc; //�g���K�[�͈̔�(�~�ʂ̃f�[�^)
};

struct TRIGGERS {
	TRIGGER trigger[4];
};

struct MYTRIGGER {
	TRIGGERS myTrigger[2];
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

enum STATUS {
	MOVE = 0,
	TRION,
	ATTACK,
	AVOIDANCE,
	DEFENCE,
	SUPPORT,
	TECHNIQUE,
	STATUS_MAX
};
struct CHARACTER_STATUS
{
	int status[STATUS_MAX];
};

enum STEP {
	FIRST = 0,
	SECONDE,
	THIRD,
	STEP_MAX
};


enum HANDS {
	RIGHT = 0,
	LEFT,
	MAX
};

enum WEAPON {
	FREE,
	KOGETSU,
	SHIELD,
	ASTEROID,
	EAGLET,
	WEAPON_MAX
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


/// <summary>
/// �x�ɕϊ�
/// </summary>
/// <param name="deg"></param>
/// <returns></returns>
inline float ToRad(float deg) { return deg * XM_PI / 180.0f; }

inline VECTOR operator +(const VECTOR& a, const VECTOR& b) {
	return VAdd(a, b);
}

/// <summary>
///�@�x�N�g�����m�̈����Z
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

	/// <summary>
	/// �_�ƒZ�`�̓����蔻��
	/// </summary>
	/// <param name="_point"> �_ </param>
	/// <param name="_leftUp"> �Z�`�̍�����W </param>
	/// <param name="_distance"> �Z�`�̕�(x)�ƍ���(y) </param>
	/// <returns></returns>
	bool PointInBox(XMFLOAT2 point, XMFLOAT2 _leftUp, XMFLOAT2 _distance);

	bool PointInQuad(XMFLOAT2 point, const array<XMFLOAT2, 4>& corners);

	VECTOR Lerp3D(VECTOR& start, VECTOR& goal, float percent);

	void SetState(int _state) { state_ = _state; }

	VECTOR Get3DPosition() { return position; }
	void Set3DPosition(VECTOR _position) { position = _position; }

protected:
	int hModel;  // ���f���f�[�^
	VECTOR position; // ���W
	VECTOR rotation; // ��]
	MATRIX matrix; //�s��
	int state_;
};
