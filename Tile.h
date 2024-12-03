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
private:

	struct TILEDATA {
		VECTOR position;
		int num;
	};

	TILEDATA Tiles[z][x];

	float tWSize, tHSize;
	
};

