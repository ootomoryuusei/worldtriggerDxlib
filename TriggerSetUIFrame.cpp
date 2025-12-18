#include "TriggerSetUIFrame.h"

#include"TriggerIcons.h"

TriggerSetUIFrame::TriggerSetUIFrame(GameObject* parent) :Icon(parent)
{
	LoadSprite("Assets//Image//TriggerSetUIFrame.png");
	transform_.position_ = { 0,0,0 };
}

TriggerSetUIFrame::~TriggerSetUIFrame()
{
}

void TriggerSetUIFrame::Update()
{
	TriggerIcons* pTriggerIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TriggerIcons>();
	for (auto& itr : pTriggerIcons->GetpTIcons()) {
		XMFLOAT2 ti_pos = { itr->GetPosition().x,itr->GetPosition().y };
		XMFLOAT2 ti_gSize = { itr->GetBaseSizeF().halfX(),itr->GetBaseSizeF().halfY()};
		XMFLOAT2 ti_center = {ti_pos.x + ti_gSize.x , ti_pos.y + ti_gSize.y};
		XMFLOAT2 leftUp = { transform_.position_.x, transform_.position_.y };
		XMFLOAT2 distance = { baseSize_.x,baseSize_.y };
		if(PointInBox(ti_center,leftUp,distance)){
			trigger = itr->GetIconName();
		}
	}
}

void TriggerSetUIFrame::Draw()
{
	DrawGraph(position_.x, position_.y, hModel_, TRUE);
}
