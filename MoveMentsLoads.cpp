#include "MoveMentsLoads.h"
#include"UnitIcons.h"

MoveMentsLoads::MoveMentsLoads(GameObject* parent)
{
}

MoveMentsLoads::~MoveMentsLoads()
{
}

void MoveMentsLoads::Initialize()
{
	for (int i = 0;i < MAX_SELECT_CHARACTER * 2;i++) {
		MoveMentsLoad* pMoveMentsLoad = Instantiate<MoveMentsLoad>(this);
		UnitIcons* pUnitIcons = /*GetParent()->*/GetParent()->FindGameObject<UnitIcons>();
		VECTOR u_pos = pUnitIcons->GetpUnitIcons()[i]->Get3DPosition();
		pMoveMentsLoad->Set3DPosition(u_pos);
		pMoveMentsLoad->SetCreateNum(i);
		pMoveMentsLoads_.push_back(pMoveMentsLoad);
	}
}

void MoveMentsLoads::Update()
{
}
