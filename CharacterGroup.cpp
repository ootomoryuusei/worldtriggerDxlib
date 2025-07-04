#include "CharacterGroup.h"
#include"Engine/CsvReader.h"

#include"UnitIcons.h"
#include"Tile.h"

CharacterGroup::CharacterGroup(GameObject* parent) : GroupBase(parent)
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
	list<Character*> characters = FindGameObjects<Character>();

	int index = 0;
	if (pUnitIcons->GetMoveMentSet()) {
		for (auto& itr : characters) {
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