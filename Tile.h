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

	const int GetTileX() { return MAX_MAP_WIDTH; }
	const int GetTileZ() { return MAX_MAP_HIGHT; }
private:

	int hTile;
	int hTileFrame;
	int hPIcon;

	TILEDATA Tiles[MAX_MAP_HIGHT][MAX_MAP_WIDTH];

	float tWSize, tHSize;
};

