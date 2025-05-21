#include "TriggerSetUIFrames.h"

TriggerSetUIFrames::TriggerSetUIFrames(GameObject* parent) : Icon(parent)
{
	for (int x = 0; x < MAX_TRIGGER_HANDS; x++) { //TriggerSet‚ÌƒtƒŒ[ƒ€‚ÌˆÊ’uŒˆ‚ß
		for (int y = 0; y < MAX_CAN_SET_TRIGGER; y++) {
			TriggerSetUIFrame* pTsuif = Instantiate<TriggerSetUIFrame>(this);
			VECTOR graphPos = { 780.0f + 330.0f * x, 50.0f + (pTsuif->GetGraphSizeF_2D().y + 10) * y,0 };
			pTsuif->Set3DPosition(graphPos);
			pTSUIFrames_.push_back(pTsuif);
		}
	}
}

TriggerSetUIFrames::~TriggerSetUIFrames()
{
}

void TriggerSetUIFrames::Update()
{
	if (canVisible_) {
		for (auto& itr : pTSUIFrames_) {
			itr->SetCanVisible(true);
		}
	}
	else {
		for (auto& itr : pTSUIFrames_) {
			itr->SetCanVisible(true);
		}
	}
}

void TriggerSetUIFrames::Draw()
{
}
