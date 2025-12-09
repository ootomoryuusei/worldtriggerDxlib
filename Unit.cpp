#include "Unit.h"
#include"Mouse.h"

#include"SetIcons.h"
#include"GroupManager.h"
#include"CharacterData.h"

Unit::Unit(GameObject* parent) : Icon(parent)
{
	LoadSprite("Assets//Image//unit.png");

	transform_.position_ = { 700,450 ,0};

	boxSize[0] = { 100 ,40 };
	boxSize[1] = { graphSizeF_.x + 10,graphSizeF_.y + 10 };

	boxPos[0] = { transform_.position_.x + boxSize[0].x,transform_.position_.y + boxSize[0].y };
	boxPos[1] = { transform_.position_.x, boxPos[0].y };

	transform_.position_ = { boxPos[1].x + 10 / 2, boxPos[1].y + 10 / 2 ,0};

	iconName_ = "出撃ユニット";
}

Unit::~Unit()
{
}

void Unit::Initialize()
{
	int fontSize = 12;
	int fontThickness = 9;
	fontHandle_ = CreateFontToHandle("出撃ユニットフォント", fontSize, fontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	GroupManager* pGroupManager_ = GetParent()->FindGameObject<GroupManager>();

	CsvReader* csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");
	
	vector<string> name;
	for (int y = 1; y < csv_->GetHeight(); y++) {
		name.push_back(csv_->GetString(0, y));
	}

	csv_->Load("Assets//Character//CharacterStatus.csv");

	int num = 0;
	for (auto& itr : name) {
		string graphName;
		graphName = itr + ".png";
		string flPath;
		string DLC = "Assets//Image//CharacterIcon//selectCIcon//";
		flPath = DLC + graphName;
		CharacterIcon* pCIcon = Instantiate<CharacterIcon>(this);
		pCIcon->LoadSprite(flPath);
		auto& data = pCIcon->GetpData();
		data->DefaultSetStatus(itr);
		SIZE_F_2D g_pos = pCIcon->GetGraphSizeF_2D();
		VECTOR graphPos = { 0,0,0 };
		if (num % 2 == 0) {
			graphPos = { transform_.position_.x + g_pos.x * (num / 2),transform_.position_.y + g_pos.y * 1 ,0 };
		}
		else {
			graphPos = { transform_.position_.x + g_pos.x * (num / 2),transform_.position_.y + g_pos.y * 0 ,0 };
		}
		pCIcon->SetPosition(graphPos);
		pCIcon->SetCreateNum(num);
		MYTRIGGER myTrigger;
		data->SelectSetMyTrigger(itr);
		num++;
	}
}

void Unit::Update()
{
	Icon::Update();
}

void Unit::Draw()
{
	//テキスト入り小box
	XMFLOAT2 pos = { position_.x,position_.y };
	DrawBoxAA(pos.x, pos.y, boxPos[0].x, boxPos[0].y, GetColor(0, 0, 0), TRUE);

	//大box
	DrawBoxAA(boxPos[1].x, boxPos[1].y, boxPos[1].x + boxSize[1].x, boxPos[1].y + boxSize[1].y
		, GetColor(0, 0, 0), TRUE);

	Icon::Draw();

	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	XMFLOAT2 space = { (boxSize[0].x - strSize.x) / 2,(boxSize[0].y - strSize.y) / 2 };
	VECTOR fontPos = { position_.x + space.x, position_.y + space.y,0 };
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(),
		GetColor(255, 255, 255), fontHandle_,GetColor(0,0,0));
}

