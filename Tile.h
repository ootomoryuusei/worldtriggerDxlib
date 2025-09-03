#pragma once
#include "Object3D.h"

class player1;

class Tile :
    public Object3D
{
public:
	Tile(GameObject* parent);
	~Tile();
	void Update() override;
	void Draw() override;
private:

	int hTile;
	int hTileFrame;
	int hPIcon;
};

