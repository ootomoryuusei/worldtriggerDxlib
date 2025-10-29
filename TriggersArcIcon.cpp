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
	pFirstSelect = nullptr;
}

void TriggersArcIcon::Update()
{
	const auto& u_icons = GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
	const auto& mouse = u_icons->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = mouse->GetMousePos();

	for (auto& arc_icon : pTriggerArcIcon) {
		if (PointInQuad(mousePos, arc_icon->GetBoxCorners())) {
			pFirstSelect = arc_icon;
			pFirstSelect->SetSelecting(true);
		}
		else if(pFirstSelect != nullptr){
			pFirstSelect->SetSelecting(false);
			pFirstSelect = nullptr;
		}
	}
}
