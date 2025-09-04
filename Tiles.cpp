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
	for (int i = 0; i < MAX_MAP_HIGHT; i++) {
		vector<Tile*> row;
		for (int j = 0; j < MAX_MAP_WIDTH; j++) {
			Tile* pTile = Instantiate<Tile>(this);
			VECTOR size = pTile->GetModelSize();
			VECTOR pos = { position.x - (size.x * (3.0/4.0)) * j,position.y,position.z + size.z * i };
			if (j % 2 == 1) {
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
