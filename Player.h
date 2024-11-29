#pragma once
#include "Object3D.h"
#include "Animator.h"

class Player : public Object3D
{
public:
	Player(GameObject* parent);
	~Player();
	void Update() override;
	void Draw() override;
private:
	int hSabel; // �T�[�x�����f���̃f�[�^

	/*enum AnimID {
		WAIT = 0,
		RUN,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		MAX
	};
	int hAnimData[MAX];
	Animator* animator;*/

	// �X�e�[�g�p�^�[��
	enum State {
		sNORMAL,
		sATTACK1,
		sATTACK2,
		sATTACK3,
	};
	State state;
	void updateNormal();
	void updateAttack1();
	void updateAttack2();
	void updateAttack3();

	/// <summary>
	/// �G�ɍU������
	/// </summary>
	/// <param name="p1">�T�[�x���̍����̍��W</param>
	/// <param name="p2">�T�[�x���̐�[�̍��W</param>
	void attack(VECTOR p1, VECTOR p2);
	VECTOR prevP1, prevP2;

	class AttackKey {
	public:
		AttackKey();
		void Update(); // �{�^�����̍X�V
		bool IsPush(); // �������u�Ԃ��H
		bool IsPress(); // �����Ă��邩�H
	private:
		bool current; // ���̃L�[���
		bool previous; // �O�̃L�[���
	};
	AttackKey attKey;
};