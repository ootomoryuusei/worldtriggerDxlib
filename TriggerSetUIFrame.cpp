#include "TriggerSetUIFrame.h"

TriggerSetUIFrame::TriggerSetUIFrame(GameObject* parent) :Icon(parent)
{
	hModel = LoadGraph("Assets//Image//TriggerSetUIFrame.png");
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2.0f;
	graphSize_.halfY = graphSize_.y / 2.0f;
	graphSizeF_ = { (float)graphSize_.x,(float)graphSize_.y, (float)graphSize_.halfX, (float)graphSize_.halfY };

	/*for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 4; y++) {
			SIUFPosition_.push_back({ 780.0f + 330.0f * x, 50 + (float)(graphSize_.y + 10) * y });
		}
	}*/
	position = { 0,0,0 };
}

TriggerSetUIFrame::~TriggerSetUIFrame()
{
}

void TriggerSetUIFrame::Update()
{
}

void TriggerSetUIFrame::Draw()
{
	/*for (auto itr : SIUFPosition_) {
		position = { itr.x,itr.y, 0.0f };
		DrawGraph(position.x,position.y,hModel, TRUE);
	}*/
	DrawGraph(position.x, position.y, hModel, TRUE);
}
