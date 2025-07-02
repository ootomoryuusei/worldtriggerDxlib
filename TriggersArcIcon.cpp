#include "TriggersArcIcon.h"
#include"UnitIcons.h"
#include"Mouse.h"

TriggersArcIcon::TriggersArcIcon(GameObject* parent) : Icon(parent)
{
}

TriggersArcIcon::~TriggersArcIcon()
{
}

void TriggersArcIcon::Initialize()
{
	TriggerArcIcon* pMainTriggerArcIcon = Instantiate<TriggerArcIcon>(this);
	pMainTriggerArcIcon->Load("Assets//Image//MainTriggerCircle.png");
	TriggerArcIcon* pSubTriggerArcIcon = Instantiate<TriggerArcIcon>(this);
	pSubTriggerArcIcon->Load("Assets//Image//SubTriggerCircle.png");
	pTriggerArcIcon[RIGHT] = pMainTriggerArcIcon;
	pTriggerArcIcon[LEFT] = pSubTriggerArcIcon;
	pTriggerArcIcon[RIGHT]->SetCreateNum(0);
	pTriggerArcIcon[LEFT]->SetCreateNum(1);
	canVisible_ = true;
}

void TriggersArcIcon::Update()
{
	UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();
	VECTOR UnitPos = pUnitIcons->GetpUnitIcons()[createNum_]->Get3DPosition();

	Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();

	for (auto& itr : pTriggerArcIcon) {
		itr->Set3DPosition(UnitPos);
	}

	if (canVisible_) {
		// �S�A�C�R�����������i�\��ON�E�I�������j
		for (auto& itr : pTriggerArcIcon) {
			if (!itr->GetCanVisible()) {
				itr->SetCanVisible(true);
			}
			itr->SetSelecting(false); // �܂��S�Ĕ�I���ɂ���
		}

		// 1�����I������
		for (auto& itr : pTriggerArcIcon) {
			if (PointInQuad(mousePos, itr->GetBoxCorners())) {
				itr->SetSelecting(true); // �ŏ��Ɍ�����1�����I��
				break; // ���̉~�ʂ͖����i�����I��h�~�j
			}
		}
	}
	else {
		for (auto& itr : pTriggerArcIcon) {
			itr->SetCanVisible(false);
		}
	}
}
