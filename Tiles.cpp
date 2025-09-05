#include "Tiles.h"

Tiles::Tiles(GameObject* parent) : Object3D(parent)
{
}

Tiles::~Tiles()
{
}

void Tiles::Initialize()
{
	int count = 0;
	for (int y = 0; y < MAX_MAP_HIGHT; y++) {
		vector<Tile*> row;
		for (int x = 0; x < MAX_MAP_WIDTH; x++) {
			Tile* pTile = Instantiate<Tile>(this);
			VECTOR size = pTile->GetModelSize();
			VECTOR pos = { position.x - (size.x * (3.0/4.0)) * x,position.y,position.z + size.z * y };
			if (x % 2 == 1) {
				pos.z += size.z / 2;
			}
			pTile->Set3DPosition(pos);
			row.push_back(pTile);
		}
		pTiles.push_back(row);
	}
}

void Tiles::Update()
{
}

void Tiles::Draw()
{
}
