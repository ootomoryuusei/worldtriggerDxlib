#include "CharacterSetUIFrame.h"
#include"Player1.h"

CharacterSetUIFrame::CharacterSetUIFrame(GameObject* parent) : Icon(parent)
{
}

CharacterSetUIFrame::~CharacterSetUIFrame()
{
}

void CharacterSetUIFrame::Initialize()
{
	LoadSprite("Assets//Image//CharacterSetUIFrame.png");
	transform_.position_ = { 0,0,0 };;
	isSet_ = false;
}

void CharacterSetUIFrame::Update()
{
}
