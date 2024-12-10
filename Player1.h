#pragma once
#include "Object3D.h"

class Tile;




class Player1 :
    public Object3D
{
public:
	Player1(GameObject* parent);
	~Player1();
	void Update() override;
	void Draw() override;

	CHARACTER_STATUS GetCStatus() { return cStatus; }

	/*int GetNowNum() { return nowNum; }*/
	VECTOR GetPosition() { return position; }
private:
	int hBlade; // サーベルモデルのデータ

	int hShield;

	int hAsteroid;

	Tile* tile;

	int hPIcon;

	bool prevKey;
	
	POSITION cPos;
	int prevX, prevY;

	float movetime;
	float flame;
	float time;

	/*int nowNum;*/

	CHARACTER_STATUS cStatus;
	
};

