#include "BackGround.h"

BackGround::BackGround(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//BackGround.png");
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
}

void BackGround::Draw()
{
	Icon::Draw();
}
