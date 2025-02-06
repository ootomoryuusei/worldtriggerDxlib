#pragma once
#include "Object3D.h"
//class Tile;
class Icon;
//class CsvReader;

enum WEAPON {
	NONE,
	FREE,
	MOONBLADE,
	SHIELD,
	ASTEROID,
	MAX
};

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

	void SetMyTrigger(MYTRIGGER _trigger);

	void DrawMyTrigger(MYTRIGGER _trigger,MATRIX _leftMatrix,MATRIX _rightMatrix);

	void SetState_(int _state) { state_ = _state; }

	XMFLOAT2 GetMousePos() { return mousePos; }

private:
	int state_;

	int hBlade; // サーベルモデルのデータ

	int hShield;

	int hAsteroid;

	/*Tile* tile;*/
	Icon* icon;
	/*CsvReader* csv_;*/

	int hPIcon;

	bool prevKey;
	
	XMINT2 cPos;
	int prevX, prevY;

	float movetime;
	float flame;
	float time;

	int MouseX, MouseY; //マウス座標
	XMFLOAT2 mousePos;

	/*int nowNum;*/

	CHARACTER_STATUS cStatus;
	
	MYTRIGGER Trigger;

};

