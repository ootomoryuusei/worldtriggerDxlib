#include "MoveSelectIcons.h"

MoveSelectIcons::MoveSelectIcons(GameObject* parent) : GameObject(parent,"MoveTypesIcons")
{
	int fontSize = 32;
	int fontThickness = 5;
	int fontHandle = CreateFontToHandle("行動選択フォント", fontSize, fontThickness, DX_FONTTYPE_NORMAL);

	for (int i = 0; i < MAX_SELECT_CHARACTER * 2; i++) {
		MoveSelectIcon* pMoveSelectIcon = Instantiate<MoveSelectIcon>(this);
		pMoveSelectIcon->SetFontHandle(fontHandle);
		pMoveSelectIcons_.push_back(pMoveSelectIcon);
	}
}

MoveSelectIcons::~MoveSelectIcons()
{
}

void MoveSelectIcons::Update()
{
}

void MoveSelectIcons::Draw()
{
}
