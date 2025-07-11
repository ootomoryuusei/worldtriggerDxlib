#pragma once
#include "Object3D.h"
#include<vector>
#include<deque>
#include<list>
#include "Trigger.h"

class Icon;
class CsvReader;
class Tile;
class CharacterData;
class Enemy;

using std::vector;
using std::deque;
using std::list;

class Character :
    public Object3D
{
	enum OWENER {
		PLAYER = 0,
		ENEMY
	};
protected:

	VECTOR dir_;
	vector<int> moveMent;
	deque<int> dq_moveMent;
	list<Character*> characterlist_;
	array<Trigger*, MAX> hands_;
	array<VECTOR, MAX> handsPostion_;
	array<array<Trigger*,4>, MAX> trigger_;
	OWENER owener_;

	Tile* tile_;
	CsvReader* csv_;

	CharacterData* pData_;

	bool firstSet;
	bool moveing;

	float totalTime;
	float elapsedTime;

	float movetime;
	float flame;
	float time;
public:
	Character(GameObject* parent);
	~Character();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	VECTOR GetPosition() { return position; }

	void CreateTriggerInstance();
	void AddMoveMent(int _movement) { moveMent.push_back(_movement); }

	void DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix);

	void SetOwener(OWENER _owener) { owener_ = _owener; }

	void MoveMent();
	void EnemyMoveMent();
private:
};

