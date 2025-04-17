#include "MoveSelectIcon.h"
#include "Mouse.h"
#include"MoveTypesIcons.h"

MoveSelectIcon::MoveSelectIcon(GameObject* parent) : Icon(parent)
{
	Load("Assets/Image/moveTypesIcon.png");
	position = { 100, 0, 0 };
	canVisible_ = false;
	fontHandle_ = -1;
	iconName_ = "行動タイプ";
}

MoveSelectIcon::~MoveSelectIcon()
{
}

void MoveSelectIcon::Update()
{
	if (canVisible_) {

		MoveTypesIcons* pMoveTypesIcons = GetParent()->GetParent()->FindGameObject<MoveTypesIcons>();
		int num = pMoveTypesIcons->GetpMoveTypesIcons()[createNum_]->GetpMoveTypeIcons().size() - 1;
		scale_ = { 1.0f,1.0f + num * 0.5f };

		XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
		space = { (graphSizeF_.x - strSize.x) / 2,(graphSizeF_.y / 2 - strSize.y) / 2 };

		Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();
		
		if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x * scale_.x, graphSizeF_.y * scale_.y })) {
			if (pMouse->IsPressed(Mouse::LEFT)) {
				XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
				position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };

			}
			prevMousePos_ = mousePos;
		}
	}


}

void MoveSelectIcon::Draw()
{
	if (canVisible_) {
		DrawRotaGraph3(position.x, position.y,0,0, scale_.x,scale_.y,0.0,hModel, TRUE,FALSE);
		VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
		DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_);
		DrawLineAA(position.x, position.y + GetGraphSizeF_2D().y / 2
			, position.x + GetGraphSizeF_2D().x, position.y + GetGraphSizeF_2D().y / 2, GetColor(0, 0, 0), 2.0);
#if 1
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x * scale_.x, position.y + graphSizeF_.y * scale_.y, GetColor(255, 0, 0), FALSE);
#endif
	}
}
