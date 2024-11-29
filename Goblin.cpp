#include "Goblin.h"
#include <assert.h>
#include "Ground.h"
#include "Player.h"

Goblin::Goblin(GameObject* parent) : Object3D(parent)
{
	hModel = MV1LoadModel("Assets/Character/Goblin/Goblin.mv1");
	assert(hModel > 0);
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	static const std::string folder = "Assets/Character/Goblin/";
	static const std::string filename[MAX] = {
		"Anim_Neutral.mv1",
		"Anim_Run.mv1",
		"Anim_Damage.mv1",
		"Anim_Blow_In.mv1",
		"Anim_Blow_Loop.mv1",
		"Anim_Blow_Out.mv1",
		"Anim_Down_Loop.mv1",

	};

	for (int n = 0; n < MAX; n++) {
		hAnimData[n] = MV1LoadModel((folder + filename[n]).c_str());
		assert(hAnimData[n] > 0);
	}
	animator = new Animator();
	animator->SetModel(hModel); // ��̃��f���f�[�^
	animator->Play(hAnimData[WAIT]); // �A�j���[�V�����Đ�

	position = VGet(0, 100, 500);
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	animator->Update();

	switch (state) {
	case sNORMAL:
		updateNormal();
		break;
	case sDAMAGE:
		updateDamage();
		break;
	}
}

bool Goblin::PushByPlayer(VECTOR p1, VECTOR p2, float rad)
{
	VECTOR g1 = position;
	VECTOR g2 = position + VGet(0, 160, 0);
	float dist = Segment_Segment_MinLength(p1, p2, g1, g2);
	if (dist < rad + 30) {
		VECTOR dir = g1 - p1; //�����������ƍ��̋����������Ă���
		dir.y = 0;
		float len = VSize(dir); // ���̋���
		float pushLen = rad + 30 - len; // ��������

		dir = VNorm(dir); // ������1�ɂ���i���ꂪ������\���j
		VECTOR push = dir * pushLen;
		position += push;
		// �������Ă�
		return true;
	}
	// �������ĂȂ�
	return false;
}

bool Goblin::CheckAttacked(VECTOR playerPos, VECTOR p1, VECTOR p2, VECTOR p3, VECTOR p4)
{
	//4���_�̃|���S���ƁA�J�v�Z�����������Ă��邩
	VECTOR begin = position + VGet(0, 0, 0);
	VECTOR end = position + VGet(0, 100, 0);
	float r1 = Segment_Triangle_MinLength(begin, end, p1, p2, p3);
	float r2 = Segment_Triangle_MinLength(begin, end, p2, p3, p4);
	if (r1 < 30 || r2 < 30) {
		animator->Play(hAnimData[DAMAGE], false); // �A�j���[�V�����Đ�
		state = sDAMAGE;
		// �@�S�u�����̓v���C���[�̕������� �v���C���[�̍��W��playerPos, �����̍��W��position�ɂ���B�����́Arotation.y�ɑ������
		VECTOR direction = playerPos - position; // �S�u��������v���C���[�ւ̃x�N�g��
		rotation.y = atan2f(direction.x, direction.z);
		// �A�S�u�����͔w�����Ƀm�b�N�o�b�N����
		VECTOR push = VNorm(direction) * -30.0f;
		position += push;
		return true;
	}
	return false;
}

void Goblin::updateNormal()
{
	// �v���C���[�Ɍ������Ă�������
	Player* pPl = GetParent()->FindGameObject<Player>();
	VECTOR playerPos = pPl->GetPosition(); // �v���C���[�̍��W
	if (InFront(playerPos, ToRad(10.0f))) { 
		position += FrontVec() * 2.0f; // �v���C���[�����ʂɋ���ΑO�ɐi��
	}
	else {
		if (InRight(playerPos)) { // �v���C���[�̕����������Ƃ���
			rotation.y += ToRad(3.0f);
		}
		else {
			rotation.y -= ToRad(3.0f);
		}
	}

	// �n�ʂ̏�ɏ悹��
	Ground* pG = GetParent()->FindGameObject<Ground>();
	if (pG != nullptr) {
		VECTOR hit;
		if (pG->CheckRayCollision(position + VGet(0, 100, 0), position + VGet(0, -30, 0), &hit)) {
			position = hit;
		}
	}
}

void Goblin::updateDamage()
{
	if (animator->IsEnd()) {
		state = sNORMAL;
		animator->Play(hAnimData[WAIT]);
	}
}
