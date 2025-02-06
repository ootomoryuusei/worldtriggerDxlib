#include "TriggerIcons.h"
#include"TriggerIcon.h"
#include"Engine/CsvReader.h"
#include"TriggerSetUI.h"
#include"TriggerSetUIFrame.h"
#include"CharacterSelectUI.h"

TriggerIcons::TriggerIcons(GameObject* parent) : Object3D(parent)
{
	csv_ = new CsvReader();
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	FN2DLine = 0;
	DLC = "Assets//Image//TriggerIcon//";
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "FileName2D") {
			FN2DLine = x;
		}
	}
	Instantiate<TriggerSetUI>(this);
	for (int y = 1; y < csv_->GetHeight(); y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, y);
		std::string flPath;
		flPath = DLC + graphName;
		TriggerIcon* pTIcon = Instantiate<TriggerIcon>(this);
		pTIcon->Load(flPath);
		SIZE_2D IconSize = pTIcon->GetIconSize();
		VECTOR graphPos = { 0,IconSize.y * (y - 1) ,0 };
		pTIcon->SetInitialPosition(graphPos);
		pTIcon->Set3DPosition(graphPos);
		pTIcons_.push_back(pTIcon);
	}
	Instantiate<TriggerSetUIFrame>(this);
	Instantiate<CharacterSelectUI>(this);
}

TriggerIcons::~TriggerIcons()
{
}

void TriggerIcons::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN)) { //Enterを押すとiconを置いた場所にtriggerがセットされる
		for (auto itr : pTIcons_) {
			int TriggerNameNum = 0;
			for (int y = 1; y < csv_->GetHeight(); y++) {
				int num = itr->GetFileName().find(DLC);
				std::string fOnlyName = itr->GetFileName().erase(num, DLC.size());
				if (fOnlyName == csv_->GetString(FN2DLine, y)) {
					TriggerNameNum = y;
				}
			}
			if (itr->GetSettingNum() > 3) {
				int mainNum = itr->GetSettingNum() - 4;
				trigger.Main[mainNum].trigger = csv_->GetString(0, TriggerNameNum);
			}
			else {
				int subNum = itr->GetSettingNum();
				trigger.Sub[subNum].trigger = csv_->GetString(0, TriggerNameNum);
			}


		}
	}
	
}

void TriggerIcons::Draw()
{
}