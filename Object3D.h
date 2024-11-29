#pragma once
// GameObject��Object3D��Player/Ground�̊֌W�ɂ���
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
protected:
	int hModel;  // ���f���f�[�^
	VECTOR position; // ���W
	VECTOR rotation; // ��]
};
