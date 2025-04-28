#include "TriggersArcIcon.h"
#include"UnitIcons.h"

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
	UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();
	VECTOR UnitPos = pUnitIcons->GetpUnitIcons()[createNum_]->Get3DPosition();
	pTriggerArcIcon.pMainArc->Set3DPosition(UnitPos);
	pTriggerArcIcon.pSubArc->Set3DPosition(UnitPos);

	if (canVisible_) {
		
		pTriggerArcIcon.pMainArc->SetCanVisible(true);
		pTriggerArcIcon.pSubArc->SetCanVisible(true);
	}
	else {
		pTriggerArcIcon.pMainArc->SetCanVisible(true);
		pTriggerArcIcon.pSubArc->SetCanVisible(true);
	}
}
