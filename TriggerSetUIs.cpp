#include "TriggerSetUIs.h"

TriggerSetUIs::TriggerSetUIs(GameObject* parent)
{
	for (int i = 0; i < MAX_SELECT_CHARACTER * 2; i++) { //�L�����N�^�[���̃g���K�[�Z�b�gUI�����̉�
		TriggerSetUI* pTSUI = Instantiate<TriggerSetUI>(this);
		pTSUIs.push_back(pTSUI);
	}
}

TriggerSetUIs::~TriggerSetUIs()
{
}

void TriggerSetUIs::Update()
{
}

void TriggerSetUIs::Draw()
{
}
