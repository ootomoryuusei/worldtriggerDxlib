#include "CharacterData.h"
#include"Engine/CsvReader.h"
#include "DataLoader.h"


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
	CsvReader csv("Assets//Character//CharacterStatus.csv");
	vector<Data> data = DataLoader::Load(csv);
	c_status_ = DataLoader::GetByName<CharacterStatus, CharacterStatusFactory>("ƒLƒƒƒ‰–¼",_name, data);
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
				CsvReader csv("Assets/Weapon/DefaultWeaponStatus.csv");
				vector<Data> data = DataLoader::Load(csv);
				t_status_ = DataLoader::GetByName<TriggerStatus, TriggerStatusFactory>("WeaponName", name, data);
				myTrigger_.myTrigger[hands].trigger[i].arc.startPercent = t_status_.startPercent;
				myTrigger_.myTrigger[hands].trigger[i].arc.percent = t_status_.percent;
				myTrigger_.myTrigger[hands].trigger[i].arc.angle = t_status_.angle;
				myTrigger_.myTrigger[hands].trigger[i].arc.rangeSize = t_status_.rangeSize;
			}
			
		}
	}
}

void CharacterData::SelectSetMyTrigger(string _name)
{
	int line = 0;
	csv_->Load("Assets//Character//SelectCharacter.csv");
	for (int y = 1;y < csv_->GetHeight();y++) {
		if (_name == csv_->GetString(0, y)) {
			line = y;
		}
	}
	for (int x = 0;x < 4;x++) {
		myTrigger_.myTrigger[RIGHT].trigger[x].triggerName = csv_->GetString(x + 1, line);
	}
	for (int x = 0;x < 4;x++) {
		myTrigger_.myTrigger[LEFT].trigger[x].triggerName = csv_->GetString(4 + x + 1, line);
	}
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	for (int hands = 0;hands < MAX;hands++) {
		for (int i = 0;i < 4;i++) {
			int line = 0;
			for (int y = 1;y < csv_->GetHeight();y++) {
				string name = myTrigger_.myTrigger[hands].trigger[i].triggerName;
				CsvReader csv("Assets/Weapon/DefaultWeaponStatus.csv");
				vector<Data> data = DataLoader::Load(csv);
				t_status_ = DataLoader::GetByName<TriggerStatus, TriggerStatusFactory>("WeaponName", name, data);
				myTrigger_.myTrigger[hands].trigger[i].arc.startPercent = t_status_.startPercent;
				myTrigger_.myTrigger[hands].trigger[i].arc.percent = t_status_.percent;
				myTrigger_.myTrigger[hands].trigger[i].arc.angle = t_status_.angle;
				myTrigger_.myTrigger[hands].trigger[i].arc.rangeSize = t_status_.rangeSize;
			}
		}
	}
}
