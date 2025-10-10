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
