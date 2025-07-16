#include "TriggersArcIcons.h"
#include"UnitIcons.h"

TriggersArcIcons::TriggersArcIcons(GameObject* parent) : Icon(parent)
{
}

TriggersArcIcons::~TriggersArcIcons()
{
}

void TriggersArcIcons::Initialize()
{
	for (int i = 0;i < MAX_SELECT_CHARACTER * 2;i++) {
		TriggersArcIcon* pTriggersArcIcon = Instantiate<TriggersArcIcon>(this);
		pTriggersArcIcon->SetCreateNum(i);
		pTriggersArcIcon_.push_back(pTriggersArcIcon);
	}
}

void TriggersArcIcons::Update()
{
	UnitIcons* pUnitIcon = GetParent()->FindGameObject<UnitIcons>();
	if (pUnitIcon->GetMoveMentSet()) {
		for (auto& itr : pTriggersArcIcon_) {
			itr->GetpTriggerArcIcon()[0]->SetStep(THIRD);
			itr->GetpTriggerArcIcon()[1]->SetStep(THIRD);
		}
	}
}
