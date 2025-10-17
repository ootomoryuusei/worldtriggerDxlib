#include "MoveMentsLoad.h"
#include"UnitIcons.h"
#include"TileIcons.h"
#include"TileIcon.h"
#include"GroupManager.h"

MoveMentsLoad::MoveMentsLoad(GameObject* parent) : Icon(parent)
{
}

MoveMentsLoad::~MoveMentsLoad()
{
}

void MoveMentsLoad::Initialize()
{
	pGroupManager_ = GetParent()->GetParent()->GetParent()->FindGameObject<GroupManager>();
	pTileIcons_ = dynamic_cast<TileIcons*>(pGroupManager_->GetGroup("TileIconGroup"));
}

void MoveMentsLoad::Update()
{
}

void MoveMentsLoad::Draw()
{
	DrawMoveLine();
}

void MoveMentsLoad::DrawMoveLine()
{
	if (movement_.empty()) return;

	

	XMFLOAT2 half_t_IconSize = {
		pTileIcons_->GetpTIcon()[0][0]->GetGraphSizeF_2D().halfX,
		pTileIcons_->GetpTIcon()[0][0]->GetGraphSizeF_2D().halfY
	};

	int pointNum = 5;
	int spaceNum = pointNum - 1;
	int num = pointNum + spaceNum;

	int totalPoints = (movement_.size() - 1) * pointNum;
	int pointIndex = 0; // ç≈å„ÇÃì_Ç™ pointIndex = 0

	for (int i = static_cast<int>(movement_.size()) - 1; i > 0; --i) {
		FLOAT3 prevTileNum = movement_[i - 1];
		FLOAT3 currTileNum = movement_[i];

		VECTOR startPoint = pTileIcons_->GetpTIcon()[currTileNum.x][currTileNum.y]->Get3DPosition();

		VECTOR endPoint = pTileIcons_->GetpTIcon()[prevTileNum.x][prevTileNum.y]->Get3DPosition();
		
		VECTOR vec = endPoint - startPoint;

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
