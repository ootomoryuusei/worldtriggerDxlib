#pragma once
#include "Object3D.h"
#include<vector>
#include<deque>

class Icon;

using std::vector;
using std::deque;

class Character :
    public Object3D
{
protected:

	vector<int> moveMent;
	deque<int> dq_moveMent;

	bool firstSet;
	bool moveing;

	int maxMoveMent;

	float totalTime;
	float elapsedTime;

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

	void SetStatus(CHARACTER_STATUS _c_status) { cStatus = _c_status; }

	void DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix);
private:
	
};

