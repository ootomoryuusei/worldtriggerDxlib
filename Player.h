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
	int hSabel; // サーベルモデルのデータ

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

	// ステートパターン
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
	/// 敵に攻撃する
	/// </summary>
	/// <param name="p1">サーベルの根元の座標</param>
	/// <param name="p2">サーベルの先端の座標</param>
	void attack(VECTOR p1, VECTOR p2);
	VECTOR prevP1, prevP2;

	class AttackKey {
	public:
		AttackKey();
		void Update(); // ボタン情報の更新
		bool IsPush(); // 押した瞬間か？
		bool IsPress(); // 押しているか？
	private:
		bool current; // 今のキー情報
		bool previous; // 前のキー情報
	};
	AttackKey attKey;
};