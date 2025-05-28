#include "CharacterIcon.h"
#include"Mouse.h"
#include "CharacterSetUIFrames.h"
#include"TriggerSetUI.h"
#include"TriggerIcons.h"

CharacterIcon::CharacterIcon(GameObject* parent) : Icon(parent),inFrame_(MAX_SELECT_CHARACTER,false),pT_Icons_(nullptr)
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

	createUI = false;
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
		Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();
		CharacterSetUIFrames* pCSetUIFrames = GetParent()->GetParent()->FindGameObject<CharacterSetUIFrames>();
		if (selecting_) {
			if (pMouse->IsPressed(Mouse::LEFT)) {
				XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
				position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };
				isCatchIcon_ = true;
			}
			else {
				int num = 0;
				for (auto itr : pCSetUIFrames->GetpCSUIFrames()) { //characterとフレームの当たり判定
					XMFLOAT2 leftUp = { itr->Get3DPosition().x, itr->Get3DPosition().y };
					XMFLOAT2 distance = { itr->GetGraphSizeF_2D().x,itr->GetGraphSizeF_2D().y };
					XMFLOAT2 graphCenter = { position.x + graphSizeF_.halfX,position.y + graphSizeF_.halfY };
					if (PointInBox({ graphCenter.x,graphCenter.y }, leftUp, distance)) {
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
	}
	case SET:
	{
		Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();
		if (IsInMousePoint(mousePos)) { 
			if (pMouse->IsDoubleClicked(Mouse::LEFT)) { //範囲内をダブルクリックしたらセット用UI生成
				if (!createUI && pT_SetUI_ == nullptr && pT_Icons_ == nullptr) { 
					pT_SetUI_ = Instantiate<TriggerSetUI>(this);
					pT_Icons_ = Instantiate<TriggerIcons>(this);
					pT_Icons_->SetpCharacterIcon_(this);
					createUI = true;
				}
			}
		//}else if (pMouse->IsClicked(Mouse::LEFT)) { //範囲外をクリックしたら消す
		//	if (createUI) { 
		//		pT_SetUI_->KillMe();
		//		pT_Icons_->KillMe();
		//		createUI = false;
		//		pT_SetUI_ = nullptr;
		//		pT_Icons_ = nullptr;
		//	}			
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

