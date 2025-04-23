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

	
	if (!pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent().empty()) {

		for (auto itr = pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent().rbegin();
			itr != pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent().rend();++itr) {
			XMFLOAT2 endPoint = { pTileIcons->GetpTIcon()[*itr]->Get3DPosition().x, pTileIcons->GetpTIcon()[*itr]->Get3DPosition().y };

			XMFLOAT2 maxlength = { pTileIcons->GetpTIcon()[pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent().size()]->Get3DPosition().x,
			pTileIcons->GetpTIcon()[pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent().size()]->Get3DPosition().y };
			int num = 0;
			int space = 0;
			space = 5 - 1;
			num = 5 + space;
			XMFLOAT2 pos1;
			XMFLOAT2 pos2;
			for (int i = 0; i < num; i++) {

				XMFLOAT2 onePice = { maxlength.x / num ,maxlength.y / num };
				pos1 = { endPoint.x + onePice.x * i,endPoint.y + onePice.y * i };
				pos2 = { pos1.x + onePice.x,pos1.y + onePice.y };
				if (i % 2 == 1) {
					DrawBoxAA(endPoint.x, endPoint.y, endPoint.x + onePice.x, endPoint.y + onePice.y, GetColor(255, 0, 0), TRUE);
				}
			}
		}
	}
	
}
