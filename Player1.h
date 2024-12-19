#pragma once
#include "Object3D.h"



//class Tile;
class Icon;

class Player1 :
    public Object3D
{
public:
	Player1(GameObject* parent);
	~Player1();
	void Update() override;
	void Draw() override;

	CHARACTER_STATUS GetCStatus() { return cStatus; }

	VECTOR GetPosition() { return position; }

	void SetMyTrigger(MyTrigger _trigger);

	void DrawMyTrigger(MyTrigger _trigger);
private:
	int hBlade; // サーベルモデルのデータ

	int hShield;

	int hAsteroid;

	/*Tile* tile;*/
	Icon* icon;

	int hPIcon;

	bool prevKey;
	
	POSITION cPos;
	int prevX, prevY;

	float movetime;
	float flame;
	float time;

	/*int nowNum;*/

	CHARACTER_STATUS cStatus;
	
	MyTrigger Trigger;
};

