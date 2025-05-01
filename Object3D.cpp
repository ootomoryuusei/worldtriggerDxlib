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

MATRIX Object3D::ChangeFLOAT3ToMATRIX(FLOAT3 pos, FLOAT3 rot)
{
	MATRIX mTrans = MGetTranslate(pos); // �ړ��s��
	MATRIX mRotX = MGetRotX(rot.x); // X���̉�]�s��
	MATRIX mRotY = MGetRotY(rot.y); // Y���̉�]�s��
	MATRIX mRotZ = MGetRotZ(rot.z); // Z���̉�]�s��
	MATRIX matrix = mRotZ * mRotX * mRotY * mTrans;
	return matrix;
}

bool Object3D::PointInBox(XMFLOAT2 _point, XMFLOAT2 _LeftUp, XMFLOAT2 _distance)
{
	VECTOR P1P2, P2P3, P3P4, P4P1;
	VECTOR P1P, P2P, P3P, P4P;
	XMFLOAT2 P1, P2, P3, P4;

	P1 = { _LeftUp.x,  _LeftUp.y }; //����
	P2 = { _LeftUp.x + _distance.x,  _LeftUp.y }; //�E��
	P3 = { _LeftUp.x + _distance.x,  _LeftUp.y + _distance.y }; //�E��
	P4 = { _LeftUp.x,  _LeftUp.y + _distance.y }; //����

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
	// 4�̎O�p�`�ɕ����āA���ꂼ��̕������m�F�i�O�σx�[�X�j
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
