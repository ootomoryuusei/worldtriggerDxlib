#include "CharacterIcon.h"
#include"Mouse.h"
#include "CharacterSetUIFrames.h"
#include"TriggerSetUIs.h"
#include"TriggerSetUIFrames.h"
#include"SetIcons.h"
#include"TriggerSetUIs.h"

CharacterIcon::CharacterIcon(GameObject* parent) : Icon(parent),inFrame_(MAX_SELECT_CHARACTER,false)
{
	position = { 0,0,0 };
	initialPosition_ = { 0,0,0 };
	settingNum_ = 0;
	for (int i = 0; i < MAX_SELECT_CHARACTER; i++) {
		alreadySet_[i] = false;
	}
	state_ = SELECT;
	isCatchIcon_ = false;
	num_ = -1;
	createNum_ = -1;
}

CharacterIcon::~CharacterIcon()
{
}

void CharacterIcon::Update()
{
	switch (state_)
	{
	case SELECT:
	{
		Mouse* pMouse = GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();
		CharacterSetUIFrames* pCSetUIFrames = GetParent()->GetParent()->FindGameObject<CharacterSetUIFrames>();
		if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x, graphSizeF_.y })) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
				position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };
				isCatchIcon_ = true;
			}
			else {
				int num = 0;
				for (auto itr : pCSetUIFrames->GetpCSUIFrames()) { //characterとフレームの当たり判定
					XMFLOAT2 leftUp = { itr->Get3DPosition().x, itr->Get3DPosition().y };
					XMFLOAT2 graphSize = { itr->GetGraphSizeF_2D().x,itr->GetGraphSizeF_2D().y };
					XMFLOAT2 graphCenter = { position.x + graphSizeF_.halfX,position.y + graphSizeF_.halfY };
					if (PointInBox({ graphCenter.x,graphCenter.y }, leftUp, graphSize)) { 
						position = { itr->Get3DPosition() };
						settingNum_ = num;
						alreadySet_[num] = true;
						itr->SetIsSet(true);

						inFrame_[num] = true;
					}
					else {
						inFrame_[num] = false;
						alreadySet_[num] = false;
					}
					num++;
				}
				isCatchIcon_ = false;	
			}
			prevMousePos_ = mousePos;
		}
		break;	
		//if (PointInBox(mousePos, { position.x,position.y }, { (float)graphSize_.x, (float)graphSize_.y })) { //キャラクターのアイコンにマウスがあるかどうか
		//	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		//		position = { mousePos.x - graphSize_.halfX,mousePos.y - graphSize_.halfY ,0.0f };
		//		isCatchIcon_ = true;
		//	}
		//	
	}
	case SET:
	{
		Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();
		if (PointInBox(mousePos, { position.x,position.y }, { (float)graphSize_.x, (float)graphSize_.y })) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				SetIcons* pSIcons = GetParent()->GetParent()->FindGameObject<SetIcons>();
				TriggerSetUIs* pTSUIs = GetParent()->FindGameObject<TriggerSetUIs>();
				pSIcons->GetFrames()[createNum_]->SetCanVisible(true);
				pSIcons->GetIcons()[createNum_]->SetCanVisible(true);
				pTSUIs->GetpTSUIS()[createNum_]->SetCanVisible(true);

			}
		}
		break;
	}
	default:
		break;
	}
}

void CharacterIcon::Draw()
{
	DrawGraph(position.x, position.y, hModel, TRUE);
}

