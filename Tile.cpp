#include "Tile.h"
#include"Player1.h"
#include"PlayScene.h"
#include "ImGui/imgui.h"

Tile::Tile(GameObject* parent) : Object3D(parent)
{
	LoadModel("Assets//Model//Tile.mv1");

	transform_.position_ = { 0, 0, 0 };
	transform_.rotate_ = { 0,90,0 };
	size_ = CalculateModelSize();
}

Tile::~Tile()
{
	if(hModel_ > 0) {
		MV1DeleteModel(hModel_);
		hModel_ = -1;
	}
}

void Tile::Update()
{
	Object3D::Update();
}

void Tile::Draw()
{
	Object3D::Draw();
}
