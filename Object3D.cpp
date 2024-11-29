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
	if (hModel > 0) { // ���f�������[�h����Ă����
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Object3D::Draw()
{
	if (hModel > 0) { // ���f�������[�h����Ă����
		MATRIX mTrans = MGetTranslate(position); // �ړ��s��
		MATRIX mRotX = MGetRotX(rotation.x); // X���̉�]�s��
		MATRIX mRotY = MGetRotY(rotation.y); // Y���̉�]�s��
		MATRIX mRotZ = MGetRotZ(rotation.z); // Z���̉�]�s��
		MATRIX m = mRotZ * mRotX * mRotY * mTrans;
		MV1SetMatrix(hModel, m);
		MV1DrawModel(hModel);
	}
}

bool Object3D::InFront(VECTOR pos, float range)
//                     ����̍��W  �͈́i���W�A���j
{
	VECTOR targetVec = ToTarget(pos); // ����ւ̃x�N�g�������߂�i����̍��W�[�����̍��W�j
	targetVec = VNorm(targetVec); // ����̒������P�ɂ���
	VECTOR front = FrontVec();// �����̐��ʃx�N�g�������iVGet(0,0,1)*Y����]�s��j
	// �i���ʃx�N�g���͂��łɒ������P�j
	float ip = VDot(targetVec, front);// �Q�̃x�N�g���̓��ς��Ƃ��āA�p�x��range��菬�������true��Ԃ�
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
