#include "BackGround.h"

BackGround::BackGround(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//BackGround.png");
	canVisible_ = true;
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
}