#include "CharacterGroup.h"
#include"Engine/CsvReader.h"

#include"Mikumo_Osamu.h"
#include"Amatori_Chika.h"
#include"Kuga_Yuuma.h"

#include"UnitIcons.h"
#include"Tile.h"

CharacterGroup::CharacterGroup(GameObject* parent) : Object3D(parent)
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
		for (auto& itr : pCharacters_) {
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