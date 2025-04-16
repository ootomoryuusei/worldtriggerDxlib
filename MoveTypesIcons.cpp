#include "MoveTypesIcons.h"

MoveTypesIcons::MoveTypesIcons(GameObject* parent)
{
	
}

MoveTypesIcons::~MoveTypesIcons()
{
}

void MoveTypesIcons::Initialize()
{
	for (int i = 0; i < MAX_SELECT_CHARACTER * 2; i++) {
		MoveTypeIcons* pMoveTypeIcons = Instantiate<MoveTypeIcons>(this);
		pMoveTypeIcons->SetCreateNum(i);
		pMoveTypesIcons_.push_back(pMoveTypeIcons);
	}
}

void MoveTypesIcons::Update()
{
}
