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
	assert(csv_->Load("Assets//Character//DefaultData//Status.csv")); //未発見でエラー
	vector<Data> data = DataLoader::Load(*csv_); //キャラ事ステータスデータを読み込み
	c_status_ = DataLoader::GetByName<CharacterStatus, CharacterStatusFactory>("キャラ名",_name, data); //キャラ名一致のステータスデータを取得
}

void CharacterData::DefaultSetMyTrigger(string _name)
{
	assert(csv_->Load("Assets//Character//DefaultData//MainTrigger.csv")); //未発見でエラー
	vector<Data> data = DataLoader::Load(*csv_); //キャラ事ステータスデータを読み込み
	int findIndex = DataLoader::GetByIndex("キャラ名", _name, data);
	assert(findIndex >= 0); //未発見でエラー
	size_t size = csv_->GetWidth(findIndex + 1);

	size_t handIndex = ToIndex<HANDS>(HANDS::RIGHT_HAND);
	for (size_t x = 0;x < size;x++) {
		myTrigger_.myTrigger[handIndex].trigger[x].triggerName = csv_->GetString(x + 1,findIndex + 1);
	}

	assert(csv_->Load("Assets//Character//DefaultData//SubTrigger.csv")); //未発見でエラー
	data = DataLoader::Load(*csv_); //キャラ事ステータスデータを読み込み
	findIndex = DataLoader::GetByIndex("キャラ名", _name, data);
	assert(findIndex >= 0); //未発見でエラー
	size = csv_->GetWidth(findIndex + 1);

	handIndex = ToIndex<HANDS>(HANDS::LEFT_HAND);
	for (size_t x = 0;x < size;x++) {
		myTrigger_.myTrigger[handIndex].trigger[x].triggerName = csv_->GetString(x + 1,findIndex + 1);
	}

	assert(csv_->Load("Assets//Weapon//DefaultStatus.csv")); //未発見でエラー
	for (int hands = 0;hands < static_cast<size_t>(HANDS::MAX);hands++) {
		for (int i = 0;i < 4;i++) {
			int line = 0;
			for (int y = 1;y < csv_->GetHeight();y++) {
				string name = myTrigger_.myTrigger[hands].trigger[i].triggerName;
				vector<Data> data = DataLoader::Load(*csv_);
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
	size_t handIndex = ToIndex<HANDS>(HANDS::RIGHT_HAND);
	for (int x = 0;x < 4;x++) {
		myTrigger_.myTrigger[handIndex].trigger[x].triggerName = csv_->GetString(x + 1, line);
	}
	handIndex = ToIndex<HANDS>(HANDS::LEFT_HAND);
	for (int x = 0;x < 4;x++) {
		myTrigger_.myTrigger[handIndex].trigger[x].triggerName = csv_->GetString(4 + x + 1, line);
	}
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	for (int hands = 0;hands < static_cast<size_t>(HANDS::MAX);hands++) {
		for (int i = 0;i < 4;i++) {
			int line = 0;
			for (int y = 1;y < csv_->GetHeight();y++) {
				string name = myTrigger_.myTrigger[hands].trigger[i].triggerName;
				vector<Data> data = DataLoader::Load(*csv_);
				t_status_ = DataLoader::GetByName<TriggerStatus, TriggerStatusFactory>("WeaponName", name, data);
				myTrigger_.myTrigger[hands].trigger[i].arc.startPercent = t_status_.startPercent;
				myTrigger_.myTrigger[hands].trigger[i].arc.percent = t_status_.percent;
				myTrigger_.myTrigger[hands].trigger[i].arc.angle = t_status_.angle;
				myTrigger_.myTrigger[hands].trigger[i].arc.rangeSize = t_status_.rangeSize;
			}
		}
	}
}
