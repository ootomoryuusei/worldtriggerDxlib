#include "CharacterSetUIFrame.h"

CharacterSetUIFrame::CharacterSetUIFrame(GameObject* parent) : Icon(parent)
{
	hModel = LoadGraph("Assets//Image//CharacterSetUIFrame.png");
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2.0f;
	graphSize_.halfY = graphSize_.y / 2.0f;
	graphSizeF_ = { (float)graphSize_.x,(float)graphSize_.y, (float)graphSize_.halfX, (float)graphSize_.halfY };
	/*for (int x = 0; x < 3; x++) {
		FramePosition_.push_back({ 780.0f + (graphSize_.x + 30.0f) * x , 500});
	}*/
	position = { 0,0,0 };
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
