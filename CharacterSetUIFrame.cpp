#include "CharacterSetUIFrame.h"
#include"Player1.h"

CharacterSetUIFrame::CharacterSetUIFrame(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//CharacterSetUIFrame.png");
	position = { 0,0,0 };
	isSet_ = false;
}

CharacterSetUIFrame::~CharacterSetUIFrame()
{
}

void CharacterSetUIFrame::Update()
{
}

void CharacterSetUIFrame::Draw()
{
	/*for (auto itr : FramePosition_) {
		position = { itr.x,itr.y, 0.0f };
		DrawGraph(position.x, position.y, hModel, TRUE);
	}*/
	DrawGraph(position.x, position.y, hModel, TRUE);
}
