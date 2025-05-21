#include "TriggerSetUI.h"
#include"Player1.h"
#include"ImGui/imgui.h"

#include"CharacterIcons.h"

TriggerSetUI::TriggerSetUI(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//TriggerSetUI.png");
	position = { 750,0 , 0 };
	canVisible_ = false;
}

TriggerSetUI::~TriggerSetUI()
{
}

void TriggerSetUI::Initialize()
{
}

void TriggerSetUI::Update()
{
	CharacterIcons* pC_Icons = GetParent()->GetParent()->FindGameObject<CharacterIcons>();
	for(auto& itr : pC_Icons->GetpCIcons())
}

void TriggerSetUI::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
	}
}
