#pragma once
#include "Object3D.h"

class Icon;

class Character :
    public Object3D
{
protected:
	int hBlade; // サーベルモデルのデータ

	int hShield;

	int hAsteroid;

	/*Tile* tile;*/
	Icon* icon;

	int hPIcon;

	bool prevKey;

	XMINT2 cPos;
	int prevX, prevY;

	float movetime;
	float flame;
	float time;

	/*int nowNum;*/

	CHARACTER_STATUS cStatus;

	MYTRIGGER Trigger;

public:
	Character(GameObject* parent);
	~Character();
	void Update() override;
	void Draw() override;

	CHARACTER_STATUS GetCStatus() { return cStatus; }

	VECTOR GetPosition() { return position; }

	void SetMyTrigger(MYTRIGGER _trigger) { Trigger = _trigger; }

	void DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix);
private:
	
};

