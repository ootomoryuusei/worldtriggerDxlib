#include "Object3D.h"

#include<cmath>

using std::lerp;

Object3D::Object3D(GameObject* parent) : GameObject(parent)
{
	hModel = -1;
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
}

Object3D::Object3D(GameObject* parent,const std::string& name) : GameObject(parent, name)
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

MATRIX Object3D::ToMATRIX(FLOAT3 pos, FLOAT3 rot)
{
	MATRIX mTrans = MGetTranslate(pos); // �ړ��s��
	MATRIX mRotX = MGetRotX(rot.x); // X���̉�]�s��
	MATRIX mRotY = MGetRotY(rot.y); // Y���̉�]�s��
	MATRIX mRotZ = MGetRotZ(rot.z); // Z���̉�]�s��
	MATRIX matrix = mRotZ * mRotX * mRotY * mTrans;
	return matrix;
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

VECTOR Object3D::Lerp3D(VECTOR& start, VECTOR& goal, float percent)
{
	return VECTOR{ lerp(start.x,goal.x,percent),
				  lerp(start.y,goal.y,percent),
				  lerp(start.z,goal.z,percent)
	};
}

VECTOR Object3D::CalculateModelSize()
{
	if (hModel <= 0) {
		return {0,0,0};
	}
	
	VECTOR overallMin = { FLT_MAX,FLT_MAX,FLT_MAX };
	VECTOR overallMax = { -FLT_MAX,-FLT_MAX,-FLT_MAX };

	VECTOR scale = MV1GetScale(hModel);
	int meshCount = MV1GetMeshNum(hModel);

	for (int i = 0;i < meshCount;i++) {
		VECTOR minV = MV1GetMeshMinPosition(hModel, i);
		VECTOR maxV = MV1GetMeshMaxPosition(hModel, i);

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
