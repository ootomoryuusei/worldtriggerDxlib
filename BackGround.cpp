#include "BackGround.h"

BackGround::BackGround(GameObject* parent) : Object2D(parent)
{
	LoadSprite("Assets//Image//BackGround.png");
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
	Object2D::Update();
}

void BackGround::Draw()
{
	Object2D::Draw();
}
