#include "TriggersArcIcon.h"

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
	pTriggerArcIcon.pMainArc = pMainTriggerArcIcon;
	pTriggerArcIcon.pSubArc = pSubTriggerArcIcon;
}

void TriggersArcIcon::Update()
{
	if (canVisible_) {
		pTriggerArcIcon.pMainArc->SetCanVisible(true);
		pTriggerArcIcon.pSubArc->SetCanVisible(true);
	}
	else {
		pTriggerArcIcon.pMainArc->SetCanVisible(true);
		pTriggerArcIcon.pSubArc->SetCanVisible(true);
	}
}
