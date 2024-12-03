#include "Player1.h"
#include "Camera.h"

Player1::Player1(GameObject* parent) : Object3D(parent),hBlade(-1)
{
	hModel = MV1LoadModel("Assets//human.mv1");
	assert(hModel >= 0);
	hBlade = MV1LoadModel("Assets//Blade.mv1");
	assert(hBlade >= 0);
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
}

Player1::~Player1()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
	if (hBlade > 0) {
		MV1DeleteModel(hBlade);
		hBlade = -1;
	}
}

void Player1::Update()
{
	//// �J�����̐ݒ�
	//MATRIX mRot = MGetRotY(rotation.y);  // ��]�s��
	//// ����ĂȂ��Ƃ��A�v���C���[����ǂꂮ�炢���H���x�N�g��
	//VECTOR tmpP = VGet(0, 65, 0);
	//// ����ɉ�]�s���������
	//VECTOR pRot = tmpP * mRot;
	//// ����Ƀv���C���[�̍��W�𑫂��ƁA�J�����ʒu���o��
	//VECTOR vRot = VGet(0, 0, 3) * mRot;
	//SetCameraPositionAndTarget_UpVecY(position + pRot, position + vRot);
}

void Player1::Draw()
{
	Object3D::Draw(); // ���N���X�̊֐����Ăԁ�Player�L������`�悷��

	/*DrawCapsule3D(position, position + VGet(0, 160, 0), 30, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);*/

	int RightHand = MV1SearchFrame(hModel, "RightHand");
	assert(RightHand >= 0);
	MATRIX mBlade = MV1GetFrameLocalWorldMatrix(hModel, RightHand);


    if (hBlade > 0) { // ���f�������[�h����Ă����
		// �T�[�x����`�悷��
	/*	MV1SetMatrix(hBlade,ChangeFLOAT3ToMATRIX(position,rotation));
		MV1DrawModel(hBlade); ;*/
		// �T�[�x����`�悷��
		MV1SetMatrix(hBlade, mBlade);
		MV1DrawModel(hBlade);
	};

	// �T�[�x���̐n�́A(0,0,0)�`(0,-150,0)�ɂ���B�����mSabel��������ƁA���̍��W����ɓ���
	/*DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));*/

	/*int gHandle = LoadGraph("Assets\\TestCircle.png");
	DrawCircleGauge(position.x, position.y, 50.0, gHandle, 25.0);*/
}

