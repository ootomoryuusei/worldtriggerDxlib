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
		// 全アイコンを初期化（表示ON・選択解除）
		for (auto& itr : pTriggerArcIcon) {
			if (!itr->GetCanVisible()) {
				itr->SetCanVisible(true);
			}
			itr->SetSelecting(false); // まず全て非選択にする
		}

		// 1つだけ選択処理
		for (auto& itr : pTriggerArcIcon) {
			if (PointInQuad(mousePos, itr->GetBoxCorners())) {
				itr->SetSelecting(true); // 最初に見つけた1つだけ選択
				break; // 他の円弧は無視（同時選択防止）
			}
		}
	}
	else {
		for (auto& itr : pTriggerArcIcon) {
			itr->SetCanVisible(false);
		}
	}
}
