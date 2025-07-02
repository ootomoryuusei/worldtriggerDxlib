#pragma once
#include "Object3D.h"
#include<list>

class CsvReader;
class CharacterGroup;
class Character;
class Tile;
class Enemy;

using std::list;

class Player1 :
    public Object3D
{
public:
	Player1(GameObject* parent);
	~Player1();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void SetState_(int _state) { state_ = _state; }

private:
	CsvReader* csv_;
	CharacterGroup* pGroup_;
	list<Character*> characters_;
	Character* pSelectingCharacter_;
	Tile* pTile_;

	float movetime;
	float flame;
	float time;

	Enemy* pEnemy_;
};

