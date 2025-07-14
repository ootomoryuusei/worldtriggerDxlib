#include "Unit.h"
#include"Mouse.h"

#include"SetIcons.h"
#include"GroupManager.h"
#include"IconGroup.h"

Unit::Unit(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//unit.png");

	canVisible_ = true;

	position = { 700,450 };

	boxSize[0] = { 100 ,40 };
	boxSize[1] = { graphSizeF_.x + 10,graphSizeF_.y + 10 };

	boxPos[0] = { position.x + boxSize[0].x,position.y + boxSize[0].y };
	boxPos[1] = { position.x, boxPos[0].y };

	graphPos_ = { boxPos[1].x + 10 / 2, boxPos[1].y + 10 / 2 };

	iconName_ = "出撃ユニット";
}

Unit::~Unit()
{
}

void Unit::Initialize()
{
	int fontSize = 12;
	int fontThickness = 9;
	int fontHandle = CreateFontToHandle("出撃ユニットフォント", fontSize, fontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	fontHandle_ = fontHandle;

	GroupManager* pGroupManager_ = GetParent()->FindGameObject<GroupManager>();
	auto* sortieUnitGroup = pGroupManager_->CreateGroup<IconGroup>("sortieUnitGroup"); //グループマネージャーでplayerGroupを作成

	CsvReader* csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");
	
	vector<string> name;
	for (int y = 1; y < csv_->GetHeight(); y++) {
		name.push_back(csv_->GetString(0, y));
	}

	csv_->Load("Assets//Character//CharacterStatus.csv");

	int num = 0;
	Unit* pUnit = GetParent()->GetParent()->FindGameObject<Unit>();
	XMFLOAT2 u_pos = pUnit->GetGraphPos();
	for (auto& itr : name) {
		string graphName;
		graphName = itr + ".png";
		string flPath;
		string DLC = "Assets//Image//CharacterIcon//selectCIcon//";
		flPath = DLC + graphName;
		CharacterIcon* pCIcon = Instantiate<CharacterIcon>(this);
		pCIcon->Load(flPath);
		SIZE_F_2D IconSize = pCIcon->GetGraphSizeF_2D();
		VECTOR graphPos = { 0,0,0 };
		if (y % 2 == 0) {
			graphPos = { u_pos.x + IconSize.x * (y / 2),u_pos.y + IconSize.y * 1 ,0 };
		}
		else {
			graphPos = { u_pos.x + IconSize.x * (y / 2),u_pos.y + IconSize.y * 0 ,0 };
		}

		pCIcon->Set3DPosition(graphPos);
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

void Unit::Update()
{
	/*if (canVisible_) {
		Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();
		XMFLOAT2 pos = { position.x,position.y };
		XMFLOAT2 distance = {}
		if (PointInBox(mousePos,pos,)) {

		}
	}*/
}

void Unit::Draw()
{
	if (canVisible_) {
		//テキスト入り小box
		XMFLOAT2 pos = { position.x,position.y };
		DrawBoxAA(pos.x, pos.y, boxPos[0].x, boxPos[0].y, GetColor(0, 0, 0), TRUE);

		//大box
		DrawBoxAA(boxPos[1].x, boxPos[1].y, boxPos[1].x + boxSize[1].x, boxPos[1].y + boxSize[1].y
			, GetColor(0, 0, 0), TRUE);

		DrawGraph(graphPos_.x, graphPos_.y, hModel, TRUE);

		XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
		XMFLOAT2 space = { (boxSize[0].x - strSize.x) / 2,(boxSize[0].y - strSize.y) / 2 };
		VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
		DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(),
			GetColor(255, 255, 255), fontHandle_,GetColor(0,0,0));
	}
}
