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
private:
	int hBlade; // サーベルモデルのデータ
	Tile* tile;

	int hPIcon;

	bool prevKey;
	
	int cX, cY;
	int prevX, prevY;

	CHARACTER_STATUS cStatus;
	
};

