#include "TriggerSetUI.h"
#include"Player1.h"
#include"ImGui/imgui.h"

#include"CharacterIcons.h"
#include"TriggerSetUIFrames.h"

TriggerSetUI::TriggerSetUI(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//TriggerSetUI.png");
	position = { 750,0 , 0 };
	canVisible_ = true;
}

TriggerSetUI::~TriggerSetUI()
{
}

void TriggerSetUI::Initialize()
{
	p_frames_ = Instantiate<TriggerSetUIFrames>(this);
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
