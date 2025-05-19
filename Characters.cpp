#include "Characters.h"
#include"Engine/CsvReader.h"

#include"Amatori_Chika.h"
#include"Kuga_Yuuma.h"
#include"Mikumo_Osamu.h"

Characters::Characters(GameObject* parent) : Object3D(parent)
{
}

Characters::~Characters()
{
}

void Characters::Initialize()
{
	CsvReader* csv = new CsvReader();
	csv->Load("Assets//Character//SelectCharacter.csv");
	for (int i = 0;i < MAX_SELECT_CHARACTER;i++) {
		int num = csv->GetInt(0, i + 1);
		for (int j = 0;j < 2;j++) {
			switch (num)
			{
			case 1:
			{
				Character* pCharacter = Instantiate<Mikumo_Osamu>(this);
				pCharacters.push_back(pCharacter);
				break;
			}
			case 2:
			{
				Character* pCharacter = Instantiate<Amatori_Chika>(this);
				pCharacters.push_back(pCharacter);
				break;
			}
			case 3:
			{
				Character* pCharacter = Instantiate<Kuga_Yuuma>(this);
				pCharacters.push_back(pCharacter);
				break;
			}
			default:
				break;
			}
		}
	}
}

void Characters::Update()
{
}

void Characters::Draw()
{
}
