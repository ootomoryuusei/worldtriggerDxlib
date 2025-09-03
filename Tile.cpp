#include "Tile.h"
#include"Player1.h"
#include"PlayScene.h"
#include "ImGui/imgui.h"

Tile::Tile(GameObject* parent) : Object3D(parent)
{
	hModel = MV1LoadModel("Assets//Model//Tile.mv1");
	assert(hModel >= 0);
	
	position = VGet(0, 0, 0);
	rotation = VGet(0, XMConvertToRadians(90.0f), 0);
	size = CalculateModelSize();
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
	MV1SetMatrix(hModel,ToMATRIX(position, rotation));
	MV1DrawModel(hModel);
}
