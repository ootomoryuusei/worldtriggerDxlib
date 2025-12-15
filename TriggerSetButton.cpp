#include "TriggerSetButton.h"
#include"CharacterSetUIFrame.h"
#include"Player1.h"
#include "Mouse.h"

TriggerSetButton::TriggerSetButton(GameObject* parent) : Icon(parent)
{
	LoadSprite("Assets//Image//TriggerSetButton.png");
	transform_.position_ = { 0 ,0, 0 };
	clicked_ = false;
	prevClicked_ = false;
}

TriggerSetButton::~TriggerSetButton()
{
}

void TriggerSetButton::Update()
{
	prevClicked_ = false;
	Object2D::Update();
}

void TriggerSetButton::Draw()
{
	Object2D::Draw();
}

void TriggerSetButton::DeviceEvent(const ClickEvent& event)
{
	switch (event.button)
	{
	case LEFT:
		if (!prevClicked_) {
			clicked_ = !clicked_;
			prevClicked_ = true;
		}
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
	}
}
