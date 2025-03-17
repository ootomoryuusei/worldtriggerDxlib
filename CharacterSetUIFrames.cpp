#include "CharacterSetUIFrames.h"
#include"OkButton.h"

CharacterSetUIFrames::CharacterSetUIFrames(GameObject* parent)
{
	for (int x = 0; x < MAX_SELECT_CHARACTER; x++) { //CharacerSetのフレームの位置決めとButtonの位置決め
		CharacterSetUIFrame* pCsuif = Instantiate<CharacterSetUIFrame>(this);
		VECTOR graphPos = { 780.0f + (pCsuif->GetGraphSizeF_2D().x + 30.0f) * x, 500 ,0 };
		pCsuif->Set3DPosition(graphPos);
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
	if (pCSUIFrames_[0]->GetIsSet() && pCSUIFrames_[1]->GetIsSet() && pCSUIFrames_[2]->GetIsSet()) { //全てのフレームにキャラクターがセットされたらokボタンが見えるフラグを立てる
		OkButton* pOkButton = GetParent()->FindGameObject<OkButton>();
		pOkButton->SetCanVisible(true);
	}
	else {
		OkButton* pOkButton = GetParent()->FindGameObject<OkButton>();
		pOkButton->SetCanVisible(false);
	}

}

void CharacterSetUIFrames::Draw()
{
}
