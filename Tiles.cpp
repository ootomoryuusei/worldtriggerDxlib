#include "Tiles.h"

Tiles::Tiles(GameObject* parent) : Object3D(parent)
{
}

Tiles::~Tiles()
{
}

void Tiles::Initialize()
{
	tWSize = 1.5;
	tHSize = 1.75;
	hModel = MV1LoadModel("Assets//Model//Tile.mv1");
	assert(hModel >= 0);

	position = VGet(0, 0, 0);
	rotation.y = XMConvertToRadians(90.0f);
	int count = 0;
	for (int i = 0; i < MAX_MAP_HIGHT; i++) {
		for (int j = 0; j < MAX_MAP_WIDTH; j++) {
			if (j % 2 == 1) {
				Tiles[i][j].position = { position.x - tWSize * j,position.y,position.z + tHSize / 2 + tHSize * i };
			}
			else {
				Tiles[i][j].position = { position.x - tWSize * j,position.y,position.z + tHSize * i };
			}
			Tiles[i][j].num = count;
			count++;
		}
	}
}

void Tiles::Update()
{
}

void Tiles::Draw()
{
}
