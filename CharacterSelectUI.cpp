#include "CharacterSelectUI.h"

CharacterSelectUI::CharacterSelectUI(GameObject* parent) : Object3D(parent)
{
	hModel = LoadGraph("Assets//Image//CharacterSelectUI.png");
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2.0f;
	graphSize_.halfY = graphSize_.y / 2.0f;

	position = { 750, 350, 0 };
}

CharacterSelectUI::~CharacterSelectUI()
{
}

void CharacterSelectUI::Update()
{
}

void CharacterSelectUI::Draw()
{
	DrawGraph(position.x, position.y, hModel, TRUE);
}
