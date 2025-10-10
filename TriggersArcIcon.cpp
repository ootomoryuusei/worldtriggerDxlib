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
	const auto& pMainTriggerArcIcon = Instantiate<TriggerArcIcon>(this);
	pMainTriggerArcIcon->Load("Assets//Image//MainTriggerCircle.png");
	const auto& pSubTriggerArcIcon = Instantiate<TriggerArcIcon>(this);
	pSubTriggerArcIcon->Load("Assets//Image//SubTriggerCircle.png");
	pTriggerArcIcon[RIGHT] = pMainTriggerArcIcon;
	pTriggerArcIcon[LEFT] = pSubTriggerArcIcon;
	pTriggerArcIcon[RIGHT]->SetHand(RIGHT);
	pTriggerArcIcon[LEFT]->SetHand(LEFT);
}

void TriggersArcIcon::Update()
{
	const auto& u_icons = GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
	const auto& mouse = u_icons->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = mouse->GetMousePos();

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
