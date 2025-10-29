#include "TriggerSetUIFrame.h"

#include"TriggerIcons.h"

TriggerSetUIFrame::TriggerSetUIFrame(GameObject* parent) :Icon(parent)
{
	Load("Assets//Image//TriggerSetUIFrame.png");
	position = { 0,0,0 };
}

TriggerSetUIFrame::~TriggerSetUIFrame()
{
}

void TriggerSetUIFrame::Update()
{
	TriggerIcons* pTriggerIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TriggerIcons>();
	for (auto& itr : pTriggerIcons->GetpTIcons()) {
		XMFLOAT2 ti_pos = { itr->Get3DPosition().x,itr->Get3DPosition().y };
		XMFLOAT2 ti_gSize = { itr->GetGraphSizeF_2D().halfX,itr->GetGraphSizeF_2D().halfY };
		XMFLOAT2 ti_center = {ti_pos.x + ti_gSize.x , ti_pos.y + ti_gSize.y};
		XMFLOAT2 leftUp = { position.x, position.y };
		XMFLOAT2 distance = { graphSizeF_.x,graphSizeF_.y };
		if(PointInBox(ti_center,leftUp,distance)){
			trigger = itr->GetIconName();
		}
	}
}

void TriggerSetUIFrame::Draw()
{
	DrawGraph(position.x, position.y, hModel, TRUE);
}
