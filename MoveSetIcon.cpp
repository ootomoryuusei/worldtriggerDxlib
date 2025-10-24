#include "MoveSetIcon.h"
#include"player1.h"
#include"MoveSelectIcon.h"
#include"MoveTypeIcons.h"
#include"UnitIcons.h"
#include "Mouse.h"

MoveSetIcon::MoveSetIcon(GameObject* parent) : Icon(parent)
{
	Load("Assets/Image/moveSetIcon.png");
	position = { 0, 0, 0 };
	canVisible_ = false;
	fontHandle_ = -1;
	iconName_ = "行動設定";
}

MoveSetIcon::~MoveSetIcon()
{
}

void MoveSetIcon::Initialize()
{
	int fontSize = 32;
	int fontThickness = 5;
	fontHandle_ = CreateFontToHandle("行動設定フォント", fontSize, fontThickness, DX_FONTTYPE_NORMAL);

	/*UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();
	string WhoIcon = pUnitIcons->GetpUnitIcons()[createNum_]->GetIconName();
	csv_ = new CsvReader();
	csv_->Load("Assets/Character/CharacterStatus.csv");
	int num = 0;
	int moveNum = 0;
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if ("行動力" == csv_->GetString(x, 0)) {
			moveNum = x;
		}
	}
	for (int y = 1; y < csv_->GetHeight() ; y++) {
		if ( WhoIcon == csv_->GetString(1, y)) {
			num = y;
		}
	}*/
	/*maxSetMove = csv_->GetInt(moveNum, num);*/
	Leave();
	Invisible();
}

void MoveSetIcon::Update()
{
	scale_ = { 1.0f,1.0f + movement.size() * 0.5f };

	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	space = { (graphSizeF_.x - strSize.x) / 2,(graphSizeF_.y / 2 - strSize.y) / 2 };

	Mouse* pMouse = GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();

	if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x * scale_.x, graphSizeF_.y * scale_.y})) {
		if (pMouse->IsPressed(Mouse::LEFT)) {
			XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
			position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };

		}
		prevMousePos_ = mousePos;
	}

	UnitIcons* pUnitIcons = GetParent()->FindGameObject<UnitIcons>();
	const auto& select_unit = pUnitIcons->GetpSelecting_ptr();
	if (select_unit != nullptr) {
		auto m_ment = select_unit->GetMoveMent();
		m_ment.erase(m_ment.begin());
		movement = m_ment;
	}
	else {
		movement.empty();
	}
}

void MoveSetIcon::Draw()
{
	DrawRotaGraph3(position.x, position.y,0,0, scale_.x, scale_.y, 0.0, hModel, TRUE, FALSE);
	VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_);
	DrawLineAA(position.x, position.y + GetGraphSizeF_2D().y / 2
		, position.x + GetGraphSizeF_2D().x, position.y + GetGraphSizeF_2D().y / 2, GetColor(0, 0, 0),2.0);
	int num = 1;
	for (auto& itr : movement) {
		string move = std::to_string(num) + " : " + itr.movename;
		XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * move.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
		XMFLOAT2 Space = { (graphSizeF_.x - strSize.x) / 2,(graphSizeF_.y /2  - strSize.y) / 2 };
		VECTOR moveFontPos = { position.x + Space.x, position.y + ( graphSizeF_.y / 2 ) * num + Space.y,position.z };

		DrawStringToHandle(moveFontPos.x,moveFontPos.y,move.c_str(), GetColor(0, 0, 0), fontHandle_);
		num++;
	}
#if 0
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x * scale_.x, position.y + graphSizeF_.y * scale_.y, GetColor(255, 0, 0), FALSE);
#endif
}
