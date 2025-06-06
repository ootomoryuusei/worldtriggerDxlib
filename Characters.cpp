#include "Characters.h"
#include"Engine/CsvReader.h"

#include"Mikumo_Osamu.h"
#include"Amatori_Chika.h"
#include"Kuga_Yuuma.h"

#include"Tile.h"

Characters::Characters(GameObject* parent) : Object3D(parent)
{
}

Characters::~Characters()
{
}

void Characters::Initialize()
{
	pTile_ = GetParent()->FindGameObject<Tile>();

	CsvReader* csv = new CsvReader();
	csv->Load("Assets//Character//SelectCharacter.csv");
	for (int y = 1;y < csv->GetHeight();y++) {
		CreateCharInstance(csv->GetInt(0, y));
	}

	int index = 0;
	for (auto& itr : pCharacters_) {
		int placementIndex = csv->GetInt(9, index + 1);

		int x = placementIndex % MAX_MAP_WIDTH;
		int y = placementIndex / MAX_MAP_WIDTH;

		VECTOR initialPosition = pTile_->GetTilesData(x, y).position;
		itr->Set3DPosition(initialPosition);

		index++;
	}
}

void Characters::Update()
{
}

void Characters::Draw()
{
}

void Characters::CreateCharInstance(int _char_num)
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
