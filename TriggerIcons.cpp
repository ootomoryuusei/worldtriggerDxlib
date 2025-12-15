#include "TriggerIcons.h"
#include"CharacterSelectUI.h"
#include"TriggerSetButton.h"
#include"Engine/CsvReader.h"
#include"TriggerSetUI.h"

TriggerIcons::TriggerIcons(GameObject* parent) : Icon(parent)
{
}

TriggerIcons::~TriggerIcons()
{
}

void TriggerIcons::Initialize()
{
	firstSet = false;
}

void TriggerIcons::Update()
{
	if (!firstSet) { 
		DefaultSetTriggers(pCharacterIcon_,RIGHT_HAND);
		DefaultSetTriggers(pCharacterIcon_, LEFT_HAND);
		/*CreateCanSet(pCharacterIcon_,MAIN);
		CreateCanSet(pCharacterIcon_, SUB);*/
		firstSet = true;
	}

	TriggerSetUI* pUI = GetParent()->FindGameObject<TriggerSetUI>();
	
	
	for (int i = 0; i < (int)HANDS::MAX;i++) {
		int index = 0;
		for (auto& itr : pTIcons_[i]) {
			XMFLOAT3 position = pUI->GetpFrames()->GetpUIFrames()[i][index]->GetPosition();
			itr->SetPosition(position);
			index++;
		}
	
	}
}

void TriggerIcons::Draw()
{
}

void TriggerIcons::DefaultSetTriggers(CharacterIcon* pCharacterIcon,HANDS hands)
{
	/*MYTRIGGER myTrigger = pCharacterIcon->GetMyTrigger();
	csv_ = new CsvReader();
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	std::string DLC = "Assets//Image//TriggerIcon//";

	
	for (int i = 0;i < 4;i++) {
		for (int y = 1;y < csv_->GetHeight();y++) {
			if (csv_->GetString(0, y) == myTrigger.myTrigger[type].trigger[i].triggerName) {
				std::string graphName;
				graphName = csv_->GetString(1, y);
				std::string flPath;
				flPath = DLC + graphName;
				TriggerIcon* pTIcon = Instantiate<TriggerIcon>(this);
				pTIcon->Load(flPath);
				SIZE_F_2D IconSize = pTIcon->GetGraphSizeF_2D();
				VECTOR graphPos = { 0,0,0 };
				graphPos = { 0 + IconSize.x * (int)type,IconSize.y * pTIcons_[type].size() ,0 };
				pTIcon->SetInitialPosition(graphPos);
				pTIcon->Set3DPosition(graphPos);
				pTIcon->SetIconName(csv_->GetString(0, y));
				pTIcons_[type].push_back(pTIcon);
				pALLTIcons_.push_back(pTIcon);
			}
			
		}
	}*/
}

void TriggerIcons::SetTriggers(CharacterIcon* pCharacterIcon,HANDS hands)
{
	//MYTRIGGER myTrigger = pCharacterIcon->GetMyTrigger();
	//csv_ = new CsvReader();
	//csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	//std::string DLC = "Assets//Image//TriggerIcon//";

	//for (int y = 1;y < csv_->GetHeight();y++) {
	//	for (int i = 0;i < 4;i++) {
	//		if (csv_->GetString(0, y) == myTrigger.myTrigger[type].trigger[i].triggerName) {
	//			std::string graphName;
	//			graphName = csv_->GetString(1, y);
	//			std::string flPath;
	//			flPath = DLC + graphName;
	//			TriggerIcon* pTIcon = Instantiate<TriggerIcon>(this);
	//			pTIcon->Load(flPath);
	//			SIZE_F_2D IconSize = pTIcon->GetGraphSizeF_2D();
	//			VECTOR graphPos = { 0,0,0 };
	//			graphPos = { 0 + IconSize.x * (int)type,IconSize.y * pTIcons_[type].size() ,0 };
	//			pTIcon->SetInitialPosition(graphPos);
	//			pTIcon->Set3DPosition(graphPos);
	//			pTIcon->SetIconName(csv_->GetString(0, y));
	//			pTIcons_[type].push_back(pTIcon);
	//			pALLTIcons_.push_back(pTIcon);
	//		}
	//	}
	//}
}

void TriggerIcons::CreateCanSet(CharacterIcon* pCharacterIcon, HANDS hands)
{
	/*MYTRIGGER myTrigger = pCharacterIcon->GetMyTrigger();
	vector<string> canSet;
	csv_ = new CsvReader();
	csv_->Load("Assets//Character//CharacterStatus.csv");
	int findLine = 0;
	int canSetMainLine = 0;
	int canSetSubLine = 0;

	for (int y = 1;y < csv_->GetHeight() ; y++) {
		if (csv_->GetString(0, y) == pCharacterIcon->GetIconName()) {
			findLine = y;
		}
	}

	for (int x = 0;x<csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "CanSetMain") {
			canSetMainLine = x;
		}
	}

	for (int x = 0;x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "CanSetSub") {
			canSetSubLine = x;
		}
	}

	if (type == MAIN) {
		for (int x = canSetMainLine;x < canSetSubLine;x++) {
			canSet.push_back(csv_->GetString(x, findLine));
		}
	}
	else if (type == SUB) {
		for (int x = canSetSubLine;x < csv_->GetWidth(findLine);x++) {
			canSet.push_back(csv_->GetString(x, findLine));
		}
	}

	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	std::string DLC = "Assets//Image//TriggerIcon//";

	int i = 0;
	for (int y = 1;y < csv_->GetHeight();y++) {
		for(auto& itr : canSet){
			string name = csv_->GetString(0, y);
			if ( name == itr) {
				std::string graphName;
				graphName = csv_->GetString(1, y);
				std::string flPath;
				flPath = DLC + graphName;
				TriggerIcon* pTIcon = Instantiate<TriggerIcon>(this);
				pTIcon->Load(flPath);
				SIZE_F_2D IconSize = pTIcon->GetGraphSizeF_2D();
				VECTOR graphPos = { 0 + +IconSize.x * (int)type,300+IconSize.y * i,0};
				pTIcon->SetInitialPosition(graphPos);
				pTIcon->Set3DPosition(graphPos);
				pTIcon->SetIconName(csv_->GetString(0, y));
				pALLTIcons_.push_back(pTIcon);
				i++;
			}
		}

	}*/
}
