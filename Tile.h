#pragma once
#include "Object3D.h"

const int z = 11;
const int x = 11;


class Tile :
    public Object3D
{
public:
	Tile(GameObject* parent);
	~Tile();
	void Update() override;
	void Draw() override;

	VECTOR GetTileData(int _h, int _w) { return Tiles[_h][_w].position; }
private:
	struct TILEDATA {
		VECTOR position;
		int num;
	};
	int hTile;

	TILEDATA Tiles[z][x];

	float tWSize, tHSize;
	
};

