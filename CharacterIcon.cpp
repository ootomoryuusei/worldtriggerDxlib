#include "CharacterIcon.h"
#include"Player1.h"
#include"TriggerIcons.h"

CharacterIcon::CharacterIcon(GameObject* parent) : Icon(parent)
{
	position = { 0,0,0 };
	initialPosition_ = { 0,0,0 };
	settingNum_ = 0;
	for (int i = 0; i < MAX_SELECT_CHARACTER; i++) {
		alreadySet_[i] = false;
	}
	
}

CharacterIcon::~CharacterIcon()
{
}

void CharacterIcon::Update()
{
	Player1* pPl1 = GetParent()->GetParent()->FindGameObject<Player1>();
	XMFLOAT2 mousePos = pPl1->GetMousePos();
	TriggerIcons* pTIcons = GetParent()->GetParent()->FindGameObject<TriggerIcons>();
	if (PointInBox(mousePos , { position.x,position.y }, { (float)graphSize_.x, (float)graphSize_.y })) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			position = { mousePos.x - graphSize_.halfX,mousePos.y - graphSize_.halfY ,0.0f };
		}
		else {
			int num = 0;
			for (auto itr : pTIcons->GetpCSUIFrames()) {
				XMFLOAT2 leftUp = { itr->Get3DPosition().x, itr->Get3DPosition().y};
				XMFLOAT2 graphSize = { itr->GetGraphSizeF_2D().x,itr->GetGraphSizeF_2D().y};
				if (PointInBox({ position.x,position.y }, leftUp,graphSize)) {
					position = { itr->Get3DPosition()};
					settingNum_ = num;
					alreadySet_[num] = true;
				}
				else {
					alreadySet_[num] = false;
				}
				num++;
			}
		}
	}
}

void CharacterIcon::Draw()
{
	DrawGraph(position.x, position.y, hModel, TRUE);
}
