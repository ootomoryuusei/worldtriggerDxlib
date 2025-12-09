#include "MoveSelectIcon.h"
#include "Mouse.h"
#include"MoveTypeIcons.h"
#include "Engine/Global.h"

MoveSelectIcon::MoveSelectIcon(GameObject* parent) : Object2D(parent)
{
	LoadSprite("Assets/Image/moveTypesIcon.png");
	transform_.position_ = { 100, 0, 0 };
	fontHandle_ = -1;
	iconName_ = "行動タイプ";
}

MoveSelectIcon::~MoveSelectIcon()
{
}

void MoveSelectIcon::Initialize()
{
	int fontSize = 32;
	int fontThickness = 5;
	fontHandle_ = CreateFontToHandle("行動選択フォント", fontSize, fontThickness, DX_FONTTYPE_NORMAL);
	pMoveTypeIcons_ = Instantiate<MoveTypeIcons>(this);
	Leave(); //updateを拒否
	Invisible(); //drawを拒否
}

void MoveSelectIcon::Update()
{
	int num = pMoveTypeIcons_->GetpMoveTypeIcons().size() - 1;
	scale_ = { 1.0f,1.0f + num * 0.5f };

	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	space = { (graphSizeF_.x - strSize.x) / 2,(graphSizeF_.y / 2 - strSize.y) / 2 };

	Object2D::Update();
}

void MoveSelectIcon::Draw()
{
	Object2D::Draw();
	XMFLOAT2 fontPos = position_ + space;
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_);
	DrawLineAA(position_.x, position_.y + GetGraphSizeF_2D().y / 2
		, position_.x + GetGraphSizeF_2D().x, position_.y + GetGraphSizeF_2D().y / 2, GetColor(0, 0, 0), 2.0);
#if 0
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x * scale_.x, position.y + graphSizeF_.y * scale_.y, GetColor(255, 0, 0), FALSE);
#endif
}

void MoveSelectIcon::Release()
{
}

void MoveSelectIcon::UpdateSub()
{
	for (auto* child : *GetChildList()) {
		if (IsEntered()) {
			child->Enter();
		}
		else {
			child->Leave();
		}
	}

	GameObject::UpdateSub();
}

void MoveSelectIcon::DrawSub()
{
	for (auto* child : *GetChildList()) {
		if (IsVisibled()) {
			child->Visible();
		}
		else {
			child->Invisible();
		}
	}

	GameObject::DrawSub();
}

void MoveSelectIcon::DeviceEvent(const DragEvent& event)
{
	XMFLOAT2 current_pos = event.current;
	XMFLOAT2 prev_pos = event.start;
	switch (event.button)
	{
	case LEFT:
		XMFLOAT2 mouseVariation = { current_pos.x - prev_pos.x,current_pos.y - prev_pos.y };
		SetPosition(transform_.position_.x + mouseVariation.x, transform_.position_.y + mouseVariation.y, transform_.position_.z);
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
	}
}

