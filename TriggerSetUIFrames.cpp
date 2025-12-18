#include "TriggerSetUIFrames.h"
#include"TriggerSetUI.h"

TriggerSetUIFrames::TriggerSetUIFrames(GameObject* parent) : Icon(parent)
{
	
}

TriggerSetUIFrames::~TriggerSetUIFrames()
{
}

void TriggerSetUIFrames::Initialize()
{
	TriggerSetUI* pUI = GetParent()->GetParent()->FindGameObject<TriggerSetUI>();
	XMFLOAT2 ui_pos = { pUI->GetPosition().x,pUI->GetPosition().y };
	OBJ_SIZE_F ui_size = pUI->GetBaseSizeF();
	for (int x = 0; x < (int)MAX; x++) { //TriggerSet‚ÌƒtƒŒ[ƒ€‚ÌˆÊ’uŒˆ‚ß
		for (int y = 0; y < MAX_CAN_SET_TRIGGER; y++) {
			TriggerSetUIFrame* pUIframe = Instantiate<TriggerSetUIFrame>(this);
			VECTOR graphPos = { 1110.0f - 330.0f * x, 50.0f + (pUIframe->GetBaseSizeF().y + 10) * y,0 };
			pUIframe->SetPosition(graphPos);
			pUIFrames_[x].push_back(pUIframe);
		}
	}
}

void TriggerSetUIFrames::Update()
{

}

void TriggerSetUIFrames::Draw()
{
}
