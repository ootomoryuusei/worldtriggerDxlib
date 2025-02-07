#include "TriggerSetButton.h"
#include"CharacterSetUIFrame.h"

TriggerSetButton::TriggerSetButton(GameObject* parent) : Object3D(parent)
{
	hModel = LoadGraph("Assets//Image//TriggerSetButton.png");
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2.0f;
	graphSize_.halfY = graphSize_.y / 2.0f;

	pCFrame_ = GetParent()->FindGameObject<CharacterSetUIFrame>();
	for (auto itr : pCFrame_->GetFramePosition()) {
		ButtonPosition_.push_back({ itr.x + 10,itr.y + pCFrame_->GetSIFGraphSize().y + 10 });
	}
	position = { 0 ,0, 0 };
}

TriggerSetButton::~TriggerSetButton()
{
}

void TriggerSetButton::Update()
{
}

void TriggerSetButton::Draw()
{
	for (auto itr : ButtonPosition_) {
		position = { itr.x,itr.y,0 };
		DrawGraph(position.x, position.y, hModel, TRUE);
	}
	

}
