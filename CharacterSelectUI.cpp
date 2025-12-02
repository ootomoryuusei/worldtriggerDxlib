#include "CharacterSelectUI.h"

CharacterSelectUI::CharacterSelectUI(GameObject* parent) : Icon(parent)
{
}

CharacterSelectUI::~CharacterSelectUI()
{
}

void CharacterSelectUI::Initialize()
{
	LoadSprite("Assets//Image//CharacterSelectUI.png");
	transform_.position_ = { 750, 350, 0 };
}

void CharacterSelectUI::Update()
{
}