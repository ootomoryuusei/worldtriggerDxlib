#include "MoveSetIcons.h"

MoveSetIcons::MoveSetIcons(GameObject* parent) : GameObject(parent,"MoveSetIcons")
{
	int fontSize = 32;
	int fontThickness = 5;
	int fontHandle = CreateFontToHandle("行動設定フォント", fontSize, fontThickness, DX_FONTTYPE_NORMAL);

	for (int i = 0; i < MAX_SELECT_CHARACTER * 2; i++) {
		MoveSetIcon* pMoveSetIcon = Instantiate<MoveSetIcon>(this);
		pMoveSetIcon->SetFontHandle(fontHandle);
		pMoveSetIcon->SetCreateNum(i);
		pMoveSetIcons_.push_back(pMoveSetIcon);

	}
}

MoveSetIcons::~MoveSetIcons()
{
}

void MoveSetIcons::Update()
{
}
