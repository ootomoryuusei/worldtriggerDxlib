#include "SetIcons.h"
#include"TriggerSetUIs.h"
#include"Unit.h"

SetIcons::SetIcons(GameObject* parent) 
	: GameObject(parent),selectCharNum_(MAX_SELECT_CHARACTER * 2,-1)
{
}

SetIcons::~SetIcons()
{
}

void SetIcons::Initialize()
{
	csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");
	FNSCNLine = 0;
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "SelectCharacterNum") {
			FNSCNLine = x;
		}
	}

	for (int y = 0; y < MAX_SELECT_CHARACTER * 2; y++) {
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
	Unit* pUnit = GetParent()->GetParent()->FindGameObject<Unit>();
	XMFLOAT3 u_pos = pUnit->GetPosition();
	for (int y = 0; y < selectCharNum_.size(); y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, selectCharNum_[y]);
		std::string flPath;
		DLC = "Assets//Image//CharacterIcon//selectCIcon//";
		flPath = DLC + graphName;
		CharacterIcon* pCIcon = Instantiate<CharacterIcon>(this);
		pCIcon->LoadSprite(flPath);
		OBJ_SIZE_F IconSize = pCIcon->GetGraphSizeF_2D();
		VECTOR graphPos = {0,0,0};
		if (y % 2 == 0) {
			graphPos = { u_pos.x + IconSize.x * (y / 2),u_pos.y + IconSize.y * 1 ,u_pos.z };
		}
		else {
			graphPos = { u_pos.x + IconSize.x * (y / 2),u_pos.y + IconSize.y*0 ,u_pos.z};
		}
	
		pCIcon->SetPosition(graphPos);
		pCIcon->SetCreateNum(num);
		MYTRIGGER myTrigger;
		for (int x = 0;x < 4;x++) {
			string TriggerName = csv_->GetString(10 + x, selectCharNum_[y]);
			myTrigger.myTrigger[0].trigger[x].triggerName = TriggerName;
		}
		for (int x = 0;x < 4;x++) {
			string TriggerName = csv_->GetString(14 + x, selectCharNum_[y]);
			myTrigger.myTrigger[1].trigger[x].triggerName = TriggerName;
		}

		pCIcon->SetIconName(csv_->GetString(0, selectCharNum_[y]));
		pSelectCIcons_.push_back(pCIcon);
		num++;
	}
}

void SetIcons::Update()
{
}

void SetIcons::Draw()
{
}
