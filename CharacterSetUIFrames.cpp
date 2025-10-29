#include "CharacterSetUIFrames.h"
#include"OkButton.h"

CharacterSetUIFrames::CharacterSetUIFrames(GameObject* parent)
{
	for (int x = 0; x < MAX_SELECT_CHARACTER; x++) { //CharacerSet�̃t���[���̈ʒu���߂�Button�̈ʒu����
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
	for (auto& frame : pCSUIFrames_) {
		if (!frame->GetIsSet()) { //��ł����Z�b�g�������
			for (auto& frame : pCSUIFrames_) { //�S�t���[����draw����
				if (frame->IsVisibled()) frame->Invisible();
			}
			return;
		}
	}
	for (auto& frame : pCSUIFrames_) { //�S�t���[��draw����
		if (!frame->IsVisibled()) {
			frame->Visible();
		}
	}
}

void CharacterSetUIFrames::Draw()
{
}
