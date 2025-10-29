#include "TriggerIcon.h"
#include"Player1.h"
#include "Mouse.h"
#include"TriggerSetUI.h"

TriggerIcon::TriggerIcon(GameObject* parent) : Icon(parent)
{
	position = { 0,0,0 };
	initialPosition_ = { 0,0,0 };
	alreadySet_ = false;
	settingNum_ = 0;
}

TriggerIcon::~TriggerIcon()
{
}

void TriggerIcon::Update()
{
	Mouse* pMouse = GetParent()->GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();
	TriggerSetUI* pUI = GetParent()->GetParent()->FindGameObject<TriggerSetUI>();

	if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x, graphSizeF_.y })) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
			position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };
		}else {
			for (int index = 0;index < (int)MAX;index++) {
				for (auto& itr : pUI->GetpFrames()->GetpUIFrames()[index]) {
					XMFLOAT2 leftUp = { itr->Get3DPosition().x,itr->Get3DPosition().y };
					XMFLOAT2 distance = { itr->GetGraphSizeF_2D().x,itr->GetGraphSizeF_2D().y };
					XMFLOAT2 center = { position.x + graphSizeF_.halfX ,position.y + graphSizeF_.halfY };
					if (PointInBox(center, leftUp, distance)) {
						position = { itr->Get3DPosition() };
						break;
					}
				}
			}
		}
		prevMousePos_ = mousePos;
		
	}
	/*if (position.x != initialPosition_.x && position.x != initialPosition_.y) {
		position = initialPosition_;
	}*/
}

void TriggerIcon::Draw()
{
	DrawGraph(position.x, position.y, hModel, TRUE);
}
