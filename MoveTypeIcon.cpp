#include "MoveTypeIcon.h"
#include"Player1.h"
#include"MoveSelectIcons.h"

MoveTypeIcon::MoveTypeIcon(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//MoveTypeButton.png");
	position = { 0, 0, 0 };
	canVisible_ = false;
	fontHandle_ = -1;
	iconName_ = "";
}

MoveTypeIcon::~MoveTypeIcon()
{
}

void MoveTypeIcon::Update()
{
	if (canVisible_) {
		XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
		space = { (graphSizeF_.x - strSize.x) / 2,(graphSizeF_.y- strSize.y) /2};

		Player1* pPl1 = GetParent()->GetParent()->GetParent()->FindGameObject<Player1>();
		XMFLOAT2 mousePos = pPl1->GetMousePos();

		if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x,graphSizeF_.y })) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
				position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };
				clicked = true;
			}
			prevMousePos_ = mousePos;
		}
	}
}

void MoveTypeIcon::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
		VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
		DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_);
#if 0
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x, position.y + graphSizeF_.y, GetColor(255, 0, 0), FALSE);
#endif
	}
}
