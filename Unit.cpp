#include "Unit.h"
#include"Mouse.h"

#include"SetIcons.h"
#include"GroupManager.h"
#include"CharacterData.h"

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
		pCIcon->Load(flPath);
		auto& data = pCIcon->GetpData();
		data->DefaultSetStatus(itr);
		SIZE_F_2D g_pos = pCIcon->GetGraphSizeF_2D();
		VECTOR graphPos = { 0,0,0 };
		if (num % 2 == 0) {
			graphPos = { graphPos_.x + g_pos.x * (num / 2),graphPos_.y + g_pos.y * 1 ,0 };
		}
		else {
			graphPos = { graphPos_.x + g_pos.x * (num / 2),graphPos_.y + g_pos.y * 0 ,0 };
		}
		pCIcon->Set3DPosition(graphPos);
		pCIcon->SetCreateNum(num);
		MYTRIGGER myTrigger;
		data->SelectSetMyTrigger(itr);
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
