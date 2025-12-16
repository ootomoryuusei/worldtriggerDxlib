#include "TriggerIcon.h"
#include"Player1.h"
#include "Mouse.h"
#include"TriggerSetUI.h"

TriggerIcon::TriggerIcon(GameObject* parent) : Object2D(parent)
{
	transform_.position_ = { 0,0,0 };
	initialPosition_ = { 0,0,0 };
	alreadySet_ = false;
	settingNum_ = 0;
}

TriggerIcon::~TriggerIcon()
{
}

void TriggerIcon::Update()
{
	TriggerSetUI* pUI = GetParent()->GetParent()->FindGameObject<TriggerSetUI>();

	for (int index = 0;index < (int)MAX;index++) {
		for (auto& itr : pUI->GetpFrames()->GetpUIFrames()[index]) {
			XMFLOAT2 leftUp = { itr->GetPosition().x,itr->GetPosition().y };
			XMFLOAT2 distance = { itr->GetGraphSizeF_2D().x,itr->GetGraphSizeF_2D().y };
			XMFLOAT2 center = { transform_.position_.x + graphSizeF_.halfX() ,transform_.position_.y + graphSizeF_.halfY()};
			if (PointInBox(center, leftUp, distance)) {
				transform_.position_ = { itr->GetPosition() };
				break;
			}
		}
	}
	/*if (position.x != initialPosition_.x && position.x != initialPosition_.y) {
		position = initialPosition_;
	}*/
	Object2D::Update();
}

void TriggerIcon::Draw()
{
	Object2D::Draw();
}

void TriggerIcon::DeviceEvent(const DragEvent& event)
{
	XMFLOAT2 offset = event.delta;
	switch (event.button)
	{
	case LEFT:
		transform_.position_ = { transform_.position_.x + offset.x, transform_.position_.y + offset.y, 0.0f };
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
	}
}
