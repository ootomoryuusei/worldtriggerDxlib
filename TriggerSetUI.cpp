#include "TriggerSetUI.h"
#include"Player1.h"

TriggerSetUI::TriggerSetUI(GameObject* parent) : Icon(parent)
{
	/*hModel = LoadGraph("Assets//Image//TriggerSetUI.png");
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2.0f;
	graphSize_.halfY = graphSize_.y / 2.0f;*/
	Load("Assets//Image//TriggerSetUI.png");
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
	DrawGraph(position.x, position.y, hModel, TRUE);
	
}
