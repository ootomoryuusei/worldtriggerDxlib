#include "CharacterData.h"
#include"Engine/CsvReader.h"

CharacterData::CharacterData(GameObject* parent) : Object3D(parent)
{
}

CharacterData::~CharacterData()
{
	
}

void CharacterData::Initialize()
{
	csv_ = new CsvReader();
	csv_->Load("Assets//Character//CharacterStatus.csv");
	CHARACTER_STATUS line;
	for (int x = 0;x < csv_->GetWidth(0); x++) {
		if ("�s����" == csv_->GetString(x, 0)) {
			line.move = x;
		}
		if ("�g���I��" == csv_->GetString(x, 0)) {
			line.trion = x;
		}
		if ("�U��" == csv_->GetString(x, 0)) {
			line.attack = x;
		}
		if ("�h��" == csv_->GetString(x, 0)) {
			line.defense = x;
		}
		if ("���" == csv_->GetString(x, 0)) {
			line.avoidace = x;
		}
		if ("����" == csv_->GetString(x, 0)) {
			line.support = x;
		}
		if ("�Z�p" == csv_->GetString(x, 0)) {
			line.technique = x;
		}
	}
}

void CharacterData::Update()
{
}

void CharacterData::Draw()
{
}
