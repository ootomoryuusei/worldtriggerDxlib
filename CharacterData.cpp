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
}

void CharacterData::Update()
{
}

void CharacterData::Draw()
{
}

void CharacterData::DefaultSetStatus(string _name)
{
	int line;
	csv_->Load("Assets//Character//CharacterStatus.csv");
	for (int y = 1;y < csv_->GetHeight();y++) {
		if (_name == csv_->GetString(0, y)) {
			line = y;
		}
	}

	for (int x = 0;x < STATUS_MAX;x++) {
		status_.status[x] = csv_->GetInt(x + 1, line);
	}
}

void CharacterData::DefaultSetMyTrigger(string _name)
{
	int line;
	csv_->Load("Assets//Character//CharacterStatus.csv");
	for (int y = 1;y < csv_->GetHeight();y++) {
		if (_name == csv_->GetString(0, y)) {
			line = y;
		}
	}
	for (int x = 1;x < 5;x++) {
		myTrigger_.myTrigger[MAIN].trigger[x].triggerName = csv_->GetString(STATUS_MAX + x + 1, line);
	}
	for (int x = 5;x < 9;x++) {
		myTrigger_.myTrigger[SUB].trigger[x].triggerName = csv_->GetString(STATUS_MAX + x + 1, line);
	}
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	for (int i = 0;i < MAX;i++) {
		for (int x = 0;x < 4;x++) {
			for (int y = 1;y < csv_->GetHeight();y++) {
				/*myTrigger_.myTrigger[i].trigger[x].arc.*/
			}
		}
	}
}
