#include "MoveTypesIcons.h"

MoveTypesIcons::MoveTypesIcons(GameObject* parent)
{
	for (int i = 0; i < MAX_SELECT_CHARACTER * 2; i++) {
		MoveTypeIcons* pMoveTypeIcons = Instantiate<MoveTypeIcons>(this);
		pMoveTypesIcons_.push_back(pMoveTypeIcons);
	}
}

MoveTypesIcons::~MoveTypesIcons()
{
}

void MoveTypesIcons::Update()
{
}
