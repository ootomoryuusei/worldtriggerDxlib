#include "TriggerSetUI.h"
#include"Player1.h"

TriggerSetUI::TriggerSetUI(GameObject* parent) : Object3D(parent)
{
	hModel = LoadGraph("Assets//Image//TriggerSetUI.png");
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2.0f;
	graphSize_.halfY = graphSize_.y / 2.0f;

	hSlIcUIFrame_ = LoadGraph("Assets//Image//TriggerSetUIFrame.png");
	assert(hSlIcUIFrame_ >= 0);
	GetGraphSize(hSlIcUIFrame_, &SIFgraphSize.x, &SIFgraphSize.y);
	SIFgraphSize.halfX = SIFgraphSize.x / 2.0f;
	SIFgraphSize.halfY = SIFgraphSize.y / 2.0f;

	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 4; y++) {
			SIUFPosition_.push_back({ 780.0f + 330.0f * x, 50 + (float)(SIFgraphSize.y + 10) * y });
		}
	}
	position = { 750,0 , 0 };
}

TriggerSetUI::~TriggerSetUI()
{
}

void TriggerSetUI::Update()
{
}

void TriggerSetUI::Draw()
{
	DrawGraph(position.x, position.z, hModel, TRUE);
	for (auto itr : SIUFPosition_) {
		DrawGraph(itr.x, itr.y, hModel, TRUE);
	}
	
}
