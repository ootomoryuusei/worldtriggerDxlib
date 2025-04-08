#include "SetIcons.h"
#include"BackGround.h"
#include"TriggerSetUIs.h"

SetIcons::SetIcons(GameObject* parent) 
	: GameObject(parent),selectCharNum_(MAX_SELECT_CHARACTER,-1)
{
	Instantiate<BackGround>(this);

	csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");
	FNSCNLine = 0;
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "SelectCharacterNum") {
			FNSCNLine = x;
		}
	}

	for (int y = 0; y < MAX_SELECT_CHARACTER; y++) {
		selectCharNum_[y] = (csv_->GetInt(FNSCNLine, y + 1));
	}

	csv_->Load("Assets//Character//CharacterStatus.csv");

	FN2DLine = 0;
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "FileName2D") {
			FN2DLine = x;
		}
	}

	int num = 0;
	for (int y = 0; y < MAX_SELECT_CHARACTER; y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, selectCharNum_[y]);
		std::string flPath;
		DLC = "Assets//Image//CharacterIcon//selectCIcon//";
		flPath = DLC + graphName;
		for (int j = 0; j < 2; j++) {
			CharacterIcon* pCIcon = Instantiate<CharacterIcon>(this);
			pCIcon->Load(flPath);
			SIZE_2D IconSize = pCIcon->GetIconSize();
			VECTOR graphPos = { 0 + IconSize.x*(j),300 + IconSize.y * (y) ,0};
			pCIcon->SetInitialPosition(graphPos);
			pCIcon->Set3DPosition(graphPos);
			pCIcon->SetState(SET);
			pCIcon->SetCreateNum(num);
			pSelectCIcons_.push_back(pCIcon);
			num++;
		}
	}
	Instantiate<TriggerSetUIs>(this);
	for (int i = 0; i < MAX_SELECT_CHARACTER * 2; i++) { //キャラクター分のトリガーアイコンを実体化
		TriggerIcons* pTIcons = Instantiate<TriggerIcons>(this);
		pTIcons_.push_back(pTIcons);
	}

	for (int i = 0; i < MAX_SELECT_CHARACTER * 2; i++) {
		TriggerSetUIFrames* pTSUIFs = Instantiate<TriggerSetUIFrames>(this);
		pTSUIFSs_.push_back(pTSUIFs);
	}
}

SetIcons::~SetIcons()
{
}

void SetIcons::Update()
{
}

void SetIcons::Draw()
{
}
