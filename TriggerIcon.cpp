#include "TriggerIcon.h"
#include"Player1.h"
//#include"TriggerIcons.h"
#include"TriggerSetUIFrames.h"
#include "Mouse.h"

TriggerIcon::TriggerIcon(GameObject* parent) : Icon(parent)
{
	position = { 0,0,0 };
	initialPosition_ = { 0,0,0 };
	alreadySet_ = false;
	settingNum_ = 0;
	canVisible_ = true;
}

TriggerIcon::~TriggerIcon()
{
}

void TriggerIcon::Update()
{
	if (canVisible_) {
		Mouse* pMouse = GetParent()->GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();
		/*TriggerSetUIFrames* pTSUIFs = FindGameObject<TriggerSetUIFrames>();*/
		if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x, graphSizeF_.y })) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
				position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };

			}
			/*else {
				int num = 0;
				for (auto itr : pTSUIFs->GetpTSUIFrames()) {
					XMFLOAT2 leftUp = { itr->Get3DPosition().x,itr->Get3DPosition().y };
					XMFLOAT2 graphSize = { itr->GetGraphSizeF_2D().x,itr->GetGraphSizeF_2D().y };
					if (PointInBox({ position.x,position.y }, leftUp, graphSize)) {
						position = { itr->Get3DPosition() };
						settingNum_ = num;
						alreadySet_ = true;
						break;
					}
					else {
						alreadySet_ = false;
					}
					num++;
				}
			}*/
			prevMousePos_ = mousePos;
		}
		//if (PointInBox(mousePos, { position.x,position.y }, { (float)graphSize_.x, (float)graphSize_.y })) {
		//	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		//		position = { mousePos.x - graphSize_.halfX,mousePos.y - graphSize_.halfY ,0.0f };
		//	}
		//	
		//}
	}
	
	/*if (position.x != initialPosition_.x && position.x != initialPosition_.y) {
		position = initialPosition_;
	}*/
}

void TriggerIcon::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
	}
}
