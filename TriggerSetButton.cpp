#include "TriggerSetButton.h"
#include"CharacterSetUIFrame.h"
#include"Player1.h"

TriggerSetButton::TriggerSetButton(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//TriggerSetButton.png");
	position = { 0 ,0, 0 };
	canVisible_ = false;
	clicked_ = false;
	prevClicked_ = false;
}

TriggerSetButton::~TriggerSetButton()
{
}

void TriggerSetButton::Update()
{
	if (canVisible_) {
		Player1* pPlayer = GetParent()->GetParent()->FindGameObject<Player1>();
		if (PointInBox(pPlayer->GetMousePos(), { position.x,position.y }, { graphSizeF_.x,graphSizeF_.y })) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				if (!prevClicked_) {
					clicked_ = !clicked_;
					prevClicked_ = true;
				}
			}
			else {
				prevClicked_ = false;
			}

		}
	}
}

void TriggerSetButton::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
	}
}
