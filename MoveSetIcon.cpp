#include "MoveSetIcon.h"
#include"player1.h"
#include"MoveSelectIcon.h"
#include"MoveTypeIcons.h"
#include"UnitIcons.h"
#include"HitSquare.h"

MoveSetIcon::MoveSetIcon(GameObject* parent) : Object2D(parent)
{
	Object2D::Initialize(); //raycaster2Dへ登録
	hitShape_ = new HitSquare(); // 当たり判定形状を四角形に設定
	LoadSprite("Assets/Image/moveSetIcon.png");
	transform_.position_ = { 0, 0, 0 };
	fontHandle_ = -1;
	iconName_ = "行動設定";
}

MoveSetIcon::~MoveSetIcon()
{
}

void MoveSetIcon::Initialize()
{
	Object2D::Initialize();
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
	space = { (baseSize_.x - strSize.x) / 2,(baseSize_.y / 2 - strSize.y) / 2 };

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
	Object2D::Update();
}

void MoveSetIcon::Draw()
{
	Object2D::Draw();
	XMFLOAT2 fontPos = position_ + space;
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_);

	int num = 1;
	for (auto& itr : movement) {
		string move = std::to_string(num) + " : " + itr.movename;
		XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * move.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
		XMFLOAT2 Space = { (baseSize_.x - strSize.x) / 2,(baseSize_.y /2  - strSize.y) / 2 };
		XMFLOAT2 moveFontPos = { position_.x + Space.x, position_.y + baseSize_.halfY() * num + Space.y};

		DrawStringToHandle(moveFontPos.x,moveFontPos.y,move.c_str(), GetColor(0, 0, 0), fontHandle_);
		num++;
	}
#if 0
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x * scale_.x, position.y + graphSizeF_.y * scale_.y, GetColor(255, 0, 0), FALSE);
#endif
}

void MoveSetIcon::DeviceEvent(const DragEvent& event)
{
	XMFLOAT2 offset = event.delta;
	switch (event.button)
	{
	case LEFT:
		SetPosition(transform_.position_.x + offset.x, transform_.position_.y + offset.y, transform_.position_.z);
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
	}
}
