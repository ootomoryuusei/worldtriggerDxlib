#include "Tile.h"
#include"Player1.h"
#include"PlayScene.h"
#include "ImGui/imgui.h"

Tile::Tile(GameObject* parent) : Object3D(parent)
{
	tWSize = 1.5;
	tHSize = 1.75;
	hModel = MV1LoadModel("Assets//Tile.mv1");
	assert(hModel >= 0);
	
	position = VGet(0, 0, 0);
	rotation.y = XMConvertToRadians(90.0f);
	int count = 0;
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			if (j % 2 == 1) {
				Tiles[i][j].position = { position.x + tWSize * j,position.y,position.z - tHSize/2 - tHSize * i };
			}
			else {
				Tiles[i][j].position = { position.x + tWSize * j,position.y,position.z - tHSize * i };
			}
			Tiles[i][j].num = count;
			count++;
		}
	}

	state_ = SELECT;
}

Tile::~Tile()
{
	if(hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Tile::Update()
{
}

void Tile::Draw()
{

	switch (state_)
	{
	case SELECT:
	{
		break;
	}
	case STEP1:
	{
		for (int i = 0; i < z; i++) {
			for (int j = 0; j < x; j++) {
				MV1SetMatrix(hModel, Object3D::ChangeFLOAT3ToMATRIX(Tiles[i][j].position, rotation));
				MV1DrawModel(hModel);
			}
		}
		break;
	}
	default:
		break;
	}
}
