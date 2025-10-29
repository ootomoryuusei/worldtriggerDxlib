#include "TriggerSetButton.h"
#include"CharacterSetUIFrame.h"
#include"Player1.h"
#include "Mouse.h"

TriggerSetButton::TriggerSetButton(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//TriggerSetButton.png");
	position = { 0 ,0, 0 };
	clicked_ = false;
	prevClicked_ = false;
}

TriggerSetButton::~TriggerSetButton()
{
}

void TriggerSetButton::Update()
{
	Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();
	if (PointInBox(mousePos, { position.x,position.y }, { graphSizeF_.x,graphSizeF_.y })) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (!prevClicked_) {
				clicked_ = !clicked_;
				prevClicked_ = true;
			}
		}else {
			prevClicked_ = false;
		}
	}
}

void TriggerSetButton::Draw()
{
	DrawGraph(position.x, position.y, hModel, TRUE);
}
