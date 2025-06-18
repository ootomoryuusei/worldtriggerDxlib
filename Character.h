#pragma once
#include "Object3D.h"
#include<vector>
#include<deque>

class Icon;
class CsvReader;
class Tile;

using std::vector;
using std::deque;

class Character :
    public Object3D
{
protected:

	vector<int> moveMent;
	deque<int> dq_moveMent;

	Tile* tile_;
	CsvReader* csv_;

	bool firstSet;
	bool moveing;

	int maxMoveMent;

	float totalTime;
	float elapsedTime;

	float movetime;
	float flame;
	float time;

	/*int nowNum;*/

	CHARACTER_STATUS cStatus;

	MYTRIGGER myTrigger_;

public:
	Character(GameObject* parent);
	~Character();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	CHARACTER_STATUS GetCStatus() { return cStatus; }

	VECTOR GetPosition() { return position; }

	void ReadMyTrigger(int _createNum);

	void CreateTriggerInstance();
	void SetMyTrigger(MYTRIGGER _trigger) { myTrigger_ = _trigger; }

	void SetStatus(CHARACTER_STATUS _c_status) { cStatus = _c_status; }

	void AddMoveMent(int _movement) { moveMent.push_back(_movement); }

	void DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix);

	void MoveMent();
private:
};

