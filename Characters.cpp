#include "Characters.h"
#include"Engine/CsvReader.h"

#include"Mikumo_Osamu.h"
#include"Amatori_Chika.h"
#include"Kuga_Yuuma.h"

#include"UnitIcons.h"
#include"Tile.h"

Characters::Characters(GameObject* parent) : Object3D(parent)
{
}

Characters::~Characters()
{
}

void Characters::Initialize()
{
}

void Characters::Update()
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

void Characters::Draw()
{
}