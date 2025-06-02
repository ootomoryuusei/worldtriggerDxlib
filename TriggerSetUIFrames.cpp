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
	XMFLOAT2 ui_pos = { pUI->Get3DPosition().x,pUI->Get3DPosition().y };
	SIZE_F_2D ui_size = pUI->GetGraphSizeF_2D();
	for (int x = 0; x < (int)MAX; x++) { //TriggerSet�̃t���[���̈ʒu����
		for (int y = 0; y < MAX_CAN_SET_TRIGGER; y++) {
			TriggerSetUIFrame* pUIframe = Instantiate<TriggerSetUIFrame>(this);
			VECTOR graphPos = { 1110.0f - 330.0f * x, 50.0f + (pUIframe->GetGraphSizeF_2D().y + 10) * y,0 };
			pUIframe->Set3DPosition(graphPos);
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
