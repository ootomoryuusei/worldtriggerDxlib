#pragma once
#include "Object3D.h"
#include<vector>
#include<map>

const int z = 11;
const int x = 11;

class player1;

class Tile :
    public Object3D
{
public:
	Tile(GameObject* parent);
	~Tile();
	void Update() override;
	void Draw() override;

	VECTOR GetTileData(int _h, int _w) { return Tiles[_h][_w].position; }

	auto GetWay() { return way; }

	bool GetCompWay() { return compWay; }

	void SetCompWay(bool _compWay) { compWay = _compWay; }
private:
	struct TILEDATA {
		VECTOR position;
		int num;
	};
	int hTile;
	int hTileFrame;
	int hPIcon;

	TILEDATA Tiles[z][x];

	TILEDATA pTile[z][x];

	float tWSize, tHSize;
	
	int prevX, prevY;
	int cX, cY;
	bool prevKey;
	bool compWay;
	

	std::vector<POSITION> way;

	CHARACTER_STATUS getStatus;
};

