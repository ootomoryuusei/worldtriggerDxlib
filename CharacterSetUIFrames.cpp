#include "CharacterSetUIFrames.h"
#include"OkButton.h"

CharacterSetUIFrames::CharacterSetUIFrames(GameObject* parent)
{
	for (int x = 0; x < MAX_SELECT_CHARACTER; x++) { //CharacerSetのフレームの位置決めとButtonの位置決め
		CharacterSetUIFrame* pCsuif = Instantiate<CharacterSetUIFrame>(this);
		VECTOR graphPos = { 780.0f + (pCsuif->GetBaseSizeF().x + 30.0f) * x, 500 ,0 };
		pCsuif->SetPosition(graphPos);
		pCSUIFrames_.push_back(pCsuif);
	/*	TriggerSetButton* pTsb = Instantiate<TriggerSetButton>(this);
		VECTOR ButtonPos = { graphPos.x + 10,graphPos.y + pCsuif->GetGraphSizeF_2D().y + 10 };
		pTsb->Set3DPosition(ButtonPos);
		pTSButtons_.push_back(pTsb);*/
	}
}

CharacterSetUIFrames::~CharacterSetUIFrames()
{
}

void CharacterSetUIFrames::Update()
{
	for (auto& frame : pCSUIFrames_) {
		if (!frame->GetIsSet()) { //一つでも未セットがあれば
			for (auto& frame : pCSUIFrames_) { //全フレームをdraw拒否
				if (frame->IsVisibled()) frame->Invisible();
			}
			return;
		}
	}
	for (auto& frame : pCSUIFrames_) { //全フレームdraw許可
		if (!frame->IsVisibled()) {
			frame->Visible();
		}
	}
}

void CharacterSetUIFrames::Draw()
{
}
