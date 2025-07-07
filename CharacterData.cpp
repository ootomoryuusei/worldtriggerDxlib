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
	int line = 0;
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
	int line = 0;
	csv_->Load("Assets//Character//CharacterStatus.csv");
	for (int y = 1;y < csv_->GetHeight();y++) {
		if (_name == csv_->GetString(0, y)) {
			line = y;
		}
	}
	for (int x = 0;x < 4;x++) {
		myTrigger_.myTrigger[RIGHT].trigger[x].triggerName = csv_->GetString(STATUS_MAX + x + 1, line);
	}
	for (int x = 0;x < 4;x++) {
		myTrigger_.myTrigger[LEFT].trigger[x].triggerName = csv_->GetString(11 + x + 1, line);
	}
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	for (int hands = 0;hands < MAX;hands++) {
		for (int i = 0;i < 4;i++) {
			int line = 0;
			for (int y = 1;y < csv_->GetHeight();y++) {
				string name = myTrigger_.myTrigger[hands].trigger[i].triggerName;
				if (csv_->GetString(0, y) == name) {
					line = y;
				}
				myTrigger_.myTrigger[hands].trigger[i].arc.startPercent = csv_->GetFloat(1, y);
				myTrigger_.myTrigger[hands].trigger[i].arc.percent = csv_->GetFloat(2, y);
				myTrigger_.myTrigger[hands].trigger[i].arc.rangeSize = csv_->GetFloat(3, y);
			}
			
		}
	}
}
