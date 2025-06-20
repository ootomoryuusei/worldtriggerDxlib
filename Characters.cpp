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

void Characters::CreateCharacterInstance(int _char_num)
{
	switch (_char_num)
	{
	case MIKUMO_OSAMU : 
	{
		Character* pCharacter = Instantiate<Mikumo_Osamu>(this);
		pCharacters_.push_back(pCharacter);
		break;
	}
	case AMATORI_CHIKA:
	{
		Character* pCharacter = Instantiate<Amatori_Chika>(this);
		pCharacters_.push_back(pCharacter);
		break;
	}
	case KUGA_YUUMA:
	{
		Character* pCharacter = Instantiate<Kuga_Yuuma>(this);
		pCharacters_.push_back(pCharacter);
		break;
	}
	default:
		break;
	}
}
