#include "TriggerIcons.h"
#include"CharacterSelectUI.h"
#include"TriggerSetButton.h"
#include"Engine/CsvReader.h"

TriggerIcons::TriggerIcons(GameObject* parent) : Icon(parent)
{
	csv_ = new CsvReader();
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	FN2DLine = 0;
	std::string DLC = "Assets//Image//TriggerIcon//";
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "FileName2D") {
			FN2DLine = x;
		}
	}
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
		pMainTIcons_.push_back(pTIcon);
		pTIcons_.push_back(pTIcon);
	}

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
		pSubTIcons_.push_back(pTIcon);
		pTIcons_.push_back(pTIcon);
	}
	canVisible_ = false;
}

TriggerIcons::~TriggerIcons()
{
}

void TriggerIcons::Update()
{
	if (canVisible_) {
		for (auto itr : pMainTIcons_) { //ボタンをクリックしたらトリガーセットできるようにフラグを立てる
			itr->SetCanVisible(true);
		}
		size_t index = 0;
		for (auto itr : pMainTIcons_) {
			if (itr->GetAlreadySet()) {
				pSubTIcons_[index]->SetCanVisible(true);
			}
			else {
				pSubTIcons_[index]->SetCanVisible(false);
			}
			index++;
		}
	}
	else {
		for (auto itr : pMainTIcons_) {
			itr->SetCanVisible(false);
		}
		for (auto itr : pSubTIcons_) {
			itr->SetCanVisible(false);
		}
	}
}

void TriggerIcons::Draw()
{
	/*for (auto itr : pTIcons_) {
		itr->SetCanVisible(true);
	}*/
}