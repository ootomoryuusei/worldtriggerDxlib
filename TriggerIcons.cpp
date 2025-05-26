#include "TriggerIcons.h"
#include"CharacterSelectUI.h"
#include"TriggerSetButton.h"
#include"Engine/CsvReader.h"

TriggerIcons::TriggerIcons(GameObject* parent) : Icon(parent)
{
}

TriggerIcons::~TriggerIcons()
{
}

void TriggerIcons::Initialize()
{
	canVisible_ = true;
	firstSet = false;
}

void TriggerIcons::Update()
{
	if (!firstSet) {
		DefaultSetTriggers(pCharacterIcon_);
		firstSet = true;
	}

	if (canVisible_) {
		//for (auto itr : pMainTIcons_) { //ボタンをクリックしたらトリガーセットできるようにフラグを立てる
		//	itr->SetCanVisible(true);
		//}
		//size_t index = 0;
		//for (auto itr : pMainTIcons_) {
		//	if (itr->GetAlreadySet()) {
		//		pSubTIcons_[index]->SetCanVisible(true);
		//	}
		//	else {
		//		pSubTIcons_[index]->SetCanVisible(false);
		//	}
		//	index++;
		//}
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

}

void TriggerIcons::DefaultSetTriggers(CharacterIcon* pCharacterIcon)
{
	MYTRIGGER myTrigger = pCharacterIcon->GetMyTrigger();
	csv_ = new CsvReader();
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	std::string DLC = "Assets//Image//TriggerIcon//";

	for (int y = 1;y < csv_->GetHeight();y++) {
		for (int i = 0;i < 4;i++) {
			if (csv_->GetString(0, y) == myTrigger.Main[i].trigger) {
				std::string graphName;
				graphName = csv_->GetString(1, y);
				std::string flPath;
				flPath = DLC + graphName;
				TriggerIcon* pTIcon = Instantiate<TriggerIcon>(this);
				pTIcon->Load(flPath);
				SIZE_F_2D IconSize = pTIcon->GetGraphSizeF_2D();
				VECTOR graphPos = { 0,IconSize.y * i ,0 };
				pTIcon->SetInitialPosition(graphPos);
				pTIcon->Set3DPosition(graphPos);
				pTIcon->SetIconName(csv_->GetString(0, y));
				pMainTIcons_.push_back(pTIcon);
				pTIcons_.push_back(pTIcon);
			}
		}
		
	}
	
	for (int y = 1;y < csv_->GetHeight();y++) {
		for (int i = 0;i < 4;i++) {
			if (csv_->GetString(0, y) == myTrigger.Sub[i].trigger) {
				std::string graphName;
				graphName = csv_->GetString(1, y);
				std::string flPath;
				flPath = DLC + graphName;
				TriggerIcon* pTIcon = Instantiate<TriggerIcon>(this);
				pTIcon->Load(flPath);
				SIZE_F_2D IconSize = pTIcon->GetGraphSizeF_2D();
				VECTOR graphPos = { IconSize.x,IconSize.y * i ,0 };
				pTIcon->SetInitialPosition(graphPos);
				pTIcon->Set3DPosition(graphPos);
				pTIcon->SetIconName(csv_->GetString(0,y));
				pSubTIcons_.push_back(pTIcon);
				pTIcons_.push_back(pTIcon);
			}
		}

	}
}

void TriggerIcons::SetTriggers(CharacterIcon* pCharacterIcon)
{
	MYTRIGGER myTrigger = pCharacterIcon->GetMyTrigger();
	csv_ = new CsvReader();
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	std::string DLC = "Assets//Image//TriggerIcon//";

	for (int y = 1;y < csv_->GetHeight();y++) {
		for (int i = 0;i < 4;i++) {
			if (csv_->GetString(0, y) == myTrigger.Main[i].trigger) {
				std::string graphName;
				graphName = csv_->GetString(1, y);
				std::string flPath;
				flPath = DLC + graphName;
				TriggerIcon* pTIcon = Instantiate<TriggerIcon>(this);
				pTIcon->Load(flPath);
				SIZE_F_2D IconSize = pTIcon->GetGraphSizeF_2D();
				VECTOR graphPos = { 0,IconSize.y * i ,0 };
				pTIcon->SetInitialPosition(graphPos);
				pTIcon->Set3DPosition(graphPos);
				pTIcon->SetIconName(csv_->GetString(0, y));
				pMainTIcons_.push_back(pTIcon);
				pTIcons_.push_back(pTIcon);
			}
		}

	}

	for (int y = 1;y < csv_->GetHeight();y++) {
		for (int i = 0;i < 4;i++) {
			if (csv_->GetString(0, y) == myTrigger.Sub[i].trigger) {
				std::string graphName;
				graphName = csv_->GetString(1, y);
				std::string flPath;
				flPath = DLC + graphName;
				TriggerIcon* pTIcon = Instantiate<TriggerIcon>(this);
				pTIcon->Load(flPath);
				SIZE_F_2D IconSize = pTIcon->GetGraphSizeF_2D();
				VECTOR graphPos = { IconSize.x,IconSize.y * i ,0 };
				pTIcon->SetInitialPosition(graphPos);
				pTIcon->Set3DPosition(graphPos);
				pTIcon->SetIconName(csv_->GetString(0, y));
				pSubTIcons_.push_back(pTIcon);
				pTIcons_.push_back(pTIcon);
			}
		}

	}
}
