#include "TriggersArcIcons.h"
#include"UnitIcons.h"

TriggersArcIcons::TriggersArcIcons(GameObject* parent) : GameObject(parent)
{
}

TriggersArcIcons::~TriggersArcIcons()
{
}

void TriggersArcIcons::Initialize()
{
	UnitIcons* pUnitIcons = /*GetParent()->GetParent()->*/GetParent()->FindGameObject<UnitIcons>();
	
	for (int i = 0;i < MAX_SELECT_CHARACTER * 2;i++) {
		TriggersArcIcon* pTriggersArcIcon = Instantiate<TriggersArcIcon>(this);
		VECTOR UnitPos = pUnitIcons->GetpUnitIcons()[i]->Get3DPosition();
		pTriggersArcIcon->GetpTriggerArcIcon().pMainArc->Set3DPosition(UnitPos);
		pTriggersArcIcon->GetpTriggerArcIcon().pSubArc->Set3DPosition(UnitPos);
		pTriggersArcIcon_.push_back(pTriggersArcIcon);
	}
}

void TriggersArcIcons::Update()
{
}
