#include "MoveMentsLoad.h"
#include"UnitIcons.h"
#include"TileIcons.h"

MoveMentsLoad::MoveMentsLoad(GameObject* parent) : Icon(parent)
{
}

MoveMentsLoad::~MoveMentsLoad()
{
}

void MoveMentsLoad::Initialize()
{
}

void MoveMentsLoad::Update()
{
	UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();
	pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent();
}

void MoveMentsLoad::Draw()
{
	UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();
	TileIcons* pTileIcons = GetParent()->GetParent()->FindGameObject<TileIcons>();

	for (auto itr = pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent().rbegin();
		itr != pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent().rend();++itr){
		/*DrawBoxAA(pTileIcons->GetpTIcon()[*itr]->Get3DPosition().x, pTileIcons->GetpTIcon()[*itr]->Get3DPosition().y);*/
	}
}
