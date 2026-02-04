#include "CharacterGroup.h"
#include"Engine/CsvReader.h"
#include"UnitIcons.h"
#include"Tile.h"

CharacterGroup::CharacterGroup(GameObject* parent) : TypedGroup<Character>()
{
}

CharacterGroup::~CharacterGroup()
{
}

void CharacterGroup::Initialize()
{
}

void CharacterGroup::Update()
{
	UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();

	int index = 0;
	if (pUnitIcons->GetMoveMentSet()) {
		auto& unit_icons = pUnitIcons->GetpUnitIcons();
		for (auto& member : members_) {
			for (auto& arc_icon : unit_icons[index]->GetpTriggersArcIcon()->GetpTriggerArcIcon()) {
				arc_icon->SetStep(STEP::THIRD);
			}
			for (auto& movement : unit_icons[index]->GetMoveMent()) {
				member->AddMoveMent(movement.movement);
			}
			unit_icons[index]->SetStep(STEP::THIRD);
			member->SetStep(STEP::THIRD);
			index++;
		}
		pUnitIcons->SetMoveMentSet(false);
	}
}

void CharacterGroup::Draw()
{
}