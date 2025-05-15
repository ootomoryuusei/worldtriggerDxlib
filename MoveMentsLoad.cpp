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
	DrawMoveLine();
}

void MoveMentsLoad::DrawMoveLine()
{
	UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();
	TileIcons* pTileIcons = GetParent()->GetParent()->FindGameObject<TileIcons>();

	const auto& movement = pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent();

	if (movement.empty()) return;

	XMFLOAT2 half_t_IconSize = {
		pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().halfX,
		pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().halfY
	};

	int pointNum = 5;
	int spaceNum = pointNum - 1;
	int num = pointNum + spaceNum;

	int totalPoints = (movement.size() - 1) * pointNum;
	int pointIndex = 0; // ç≈å„ÇÃì_Ç™ pointIndex = 0

	for (int i = static_cast<int>(movement.size()) - 1; i > 0; --i) {
		int prevTileNum = movement[i - 1];
		int currTileNum = movement[i];

		XMFLOAT2 startPoint = {
			pTileIcons->GetpTIcon()[currTileNum]->Get3DPosition().x,
			pTileIcons->GetpTIcon()[currTileNum]->Get3DPosition().y
		};

		XMFLOAT2 endPoint = {
			pTileIcons->GetpTIcon()[prevTileNum]->Get3DPosition().x,
			pTileIcons->GetpTIcon()[prevTileNum]->Get3DPosition().y
		};

		XMFLOAT2 vec = {
			endPoint.x - startPoint.x,
			endPoint.y - startPoint.y
		};

		float maxlength = sqrt(vec.x * vec.x + vec.y * vec.y);
		if (maxlength == 0) continue;

		XMFLOAT2 dir = {
			vec.x / maxlength,
			vec.y / maxlength
		};


		float interval = maxlength / (num - 1);

		for (int j = 0; j < num; ++j) {
			if (j % 2 == 0) {
				XMFLOAT2 pos = {
					startPoint.x + dir.x * interval * j + half_t_IconSize.x,
					startPoint.y + dir.y * interval * j + half_t_IconSize.y
				};

				// ç≈å„Ç™1.0, ç≈èâÇ™0.0Ç…ãﬂÇ≠Ç»ÇÈÇÊÇ§Ç…ìßñæìxÇåvéZ
				float alpha = 1.0f - static_cast<float>(pointIndex) / totalPoints;

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * alpha);
				DrawCircleAA(pos.x, pos.y, interval / 2.0f, 20, GetColor(255, 0, 0), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

				pointIndex++;
			}
		}
	}
}
