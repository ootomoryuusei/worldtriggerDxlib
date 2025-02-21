#include "TriggerSetUI.h"
#include"Player1.h"
#include"ImGui/imgui.h"

TriggerSetUI::TriggerSetUI(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//TriggerSetUI.png");
	position = { 750,0 , 0 };
	canVisible_ = false;
}

TriggerSetUI::~TriggerSetUI()
{
}

void TriggerSetUI::Update()
{
}

void TriggerSetUI::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
	}
}
