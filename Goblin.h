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
	/// プレイヤーにめり込んでいれば押される
	/// </summary>
	/// <param name="p1">プレイヤーの下の点</param>
	/// <param name="p2">プレイヤーの上の点</param>
	/// <param name="rad">カプセルの半径</param>
	/// <returns>押されたらtrue</returns>
	bool PushByPlayer(VECTOR p1, VECTOR p2, float rad); // プレイヤーに押される

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

	// ステートパターン
	enum State {
		sNORMAL = 0,
		sDAMAGE,
	};
	State state;
	void updateNormal();
	void updateDamage();
};
