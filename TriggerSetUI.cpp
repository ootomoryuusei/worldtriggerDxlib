#include "TriggerSetUI.h"
#include"Player1.h"
#include"ImGui/imgui.h"

#include"CharacterIcons.h"
#include"TriggerSetUIFrames.h"

TriggerSetUI::TriggerSetUI(GameObject* parent) : Icon(parent)
{
	LoadSprite("Assets//Image//TriggerSetUI.png");
	transform_.position_ = { 750,0 , 0 };
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
	Object2D::Update();
}

void TriggerSetUI::Draw()
{
	Object2D::Draw();
}
