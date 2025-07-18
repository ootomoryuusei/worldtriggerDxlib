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
		for (auto& itr : members_) {
			for (auto& itrs : pUnitIcons->GetpUnitIcons()[index]->GetMoveMent()) {
				itr->AddMoveMent(itrs);
			}
			index++;
			itr->SetState(THIRD);
		}
		pUnitIcons->SetMoveMentSet(false);
	}
}

void CharacterGroup::Draw()
{
}