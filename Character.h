#pragma once
#include "Object3D.h"
#include<vector>
#include<deque>
#include<list>
#include "Trigger.h"

class Icon;
class CsvReader;
class Tiles;
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
	vector<VECTOR> moveMent;
	deque<VECTOR> dq_moveMent;
	list<Character*> characterlist_;
	array<Trigger*, static_cast<size_t>(HANDS::MAX)> hands_;
	array<VECTOR, static_cast<size_t>(HANDS::MAX)> handsPostion_;
	array<array<Trigger*,4>, static_cast<size_t>(HANDS::MAX)> trigger_;
	OWENER owener_;

	Tiles* pTiles_;
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

	void CreateTriggerInstance();
	void AddMoveMent(VECTOR _movement) { moveMent.push_back(_movement); }

	void DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix);

	void SetOwener(OWENER _owener) { owener_ = _owener; }

	void MoveMent();
	void EnemyMoveMent();
private:
};

