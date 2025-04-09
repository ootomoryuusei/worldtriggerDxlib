#include "MoveTypesIcons.h"

MoveTypesIcons::MoveTypesIcons(GameObject* parent) : GameObject(parent,"MoveTypesIcons")
{
	int fontSize = 32;
	int fontThickness = 5;
	int fontHandle = CreateFontToHandle("行動タイプフォント", fontSize, fontThickness, DX_FONTTYPE_NORMAL);

	for (int i = 0; i < MAX_SELECT_CHARACTER * 2; i++) {
		MoveTypesIcon* pMoveTypesIcons = Instantiate<MoveTypesIcon>(this);
		pMoveTypesIcons->SetFontHandle(fontHandle);
		pMoveTypesIcons_.push_back(pMoveTypesIcons);
	}
}

MoveTypesIcons::~MoveTypesIcons()
{
}

void MoveTypesIcons::Update()
{
}

void MoveTypesIcons::Draw()
{
}
