#include "TriggerSetUIFrame.h"

TriggerSetUIFrame::TriggerSetUIFrame(GameObject* parent) :Icon(parent)
{
	Load("Assets//Image//TriggerSetUIFrame.png");
	position = { 0,0,0 };
	canVisible_ = false;
}

TriggerSetUIFrame::~TriggerSetUIFrame()
{
}

void TriggerSetUIFrame::Update()
{
}

void TriggerSetUIFrame::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
	}
}
