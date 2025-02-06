#include "TriggerIcons.h"
#include"TriggerIcon.h"
#include"Engine/CsvReader.h"
#include"TriggerSetUI.h"
#include"TriggerSetUIFrame.h"

TriggerIcons::TriggerIcons(GameObject* parent) : Object3D(parent)
{
	CsvReader* csv_ = new CsvReader();
	Instantiate<TriggerSetUI>(this);
	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	int FN2DLine = 0;
	string DLC = "Assets//Image//TriggerIcon//";
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
		SIZE_2D IconSize = pTIcon->GerGraphSize();
		VECTOR graphPos = { 0,IconSize.y * (y - 1) ,0 };
		pTIcon->SetInitialPosition(graphPos);
		pTIcon->Set3DPosition(graphPos);
		pTIcons_.push_back(pTIcon);
	}
	TriggerSetUIFrame* pTSUF = Instantiate<TriggerSetUIFrame>(this);
}

TriggerIcons::~TriggerIcons()
{
}

void TriggerIcons::Update()
{
	for (auto itr : pTIcons_) {
		itr->GetSettingNum();
	}
}

void TriggerIcons::Draw()
{
}