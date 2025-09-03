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
			VECTOR pos = pTile->GetPosition();
			VECTOR size = pTile->GetModelSize();
			if (j % 2 == 1) {
				pTile->Set3DPosition(VGet(pos.x - size.x * j, pos.y, pos.z + size.z / 2 + size.y * i));
			}
			else {
				pTile->Set3DPosition(VGet(position.x - size.x * j, position.y, position.z + size.z * i));
			}
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
