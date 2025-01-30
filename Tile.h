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

	//VECTOR GetTileData(int _h, int _w) { return Tiles[_h][_w].position; }

	

	TILEDATA GetTilesData(int _h, int _w) { return Tiles[_h][_w]; }

	const int GetTileX() { return x; }
	const int GetTileZ() { return z; }
private:

	int hTile;
	int hTileFrame;
	int hPIcon;

	TILEDATA Tiles[z][x];

	float tWSize, tHSize;
};

