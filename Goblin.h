#pragma once
//Goblin.h
#include "Object3D.h"
#include "Animator.h"

class Goblin : public Object3D
{
public:
	Goblin(GameObject* parent);
	~Goblin();
	void Update() override;

	/// <summary>
	/// �v���C���[�ɂ߂荞��ł���Ή������
	/// </summary>
	/// <param name="p1">�v���C���[�̉��̓_</param>
	/// <param name="p2">�v���C���[�̏�̓_</param>
	/// <param name="rad">�J�v�Z���̔��a</param>
	/// <returns>�����ꂽ��true</returns>
	bool PushByPlayer(VECTOR p1, VECTOR p2, float rad); // �v���C���[�ɉ������

	bool CheckAttacked(VECTOR playerPos, VECTOR p1, VECTOR p2, VECTOR p3, VECTOR p4);
private:

	enum AnimID {
		WAIT = 0,
		RUN,
		DAMAGE,
		BLOW_BEGIN,
		BLOW_LOOP,
		BLOW_END,
		DOWN,
		MAX
	};
	int hAnimData[MAX];
	Animator* animator;

	// �X�e�[�g�p�^�[��
	enum State {
		sNORMAL = 0,
		sDAMAGE,
	};
	State state;
	void updateNormal();
	void updateDamage();
};
