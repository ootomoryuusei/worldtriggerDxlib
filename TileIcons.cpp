#include "TileIcons.h"
#include"TileIcon.h"
#include"Map.h"

TileIcons::TileIcons(GameObject* parent) : GameObject(parent)
{

}

TileIcons::~TileIcons()
{
}

void TileIcons::Initialize()
{
	pMap = GetParent()->FindGameObject<Map>();
	VECTOR MapPos = pMap->Get3DPosition();
	XMFLOAT2 boxSize = pMap->GetBoxSize(1);
	float x = boxSize.x / 15 * 14;
	transform_.position_ = { MapPos.x + x,MapPos.y + boxSize.y,MapPos.z };
	int num = 0;
	for (int y = 0; y < MAX_MAP_HIGHT; y++) {
		for (int x = 0; x < MAX_MAP_WIDTH; x++) {
			TileIcon* pTIcon = Instantiate<TileIcon>(this);
			TILEDATA tile;
			if (x % 2 == 1) {
				tile.position = { transform_.position_.x - (pTIcon->GetGraphSizeF_2D().x - 7) * x ,transform_.position_.y - pTIcon->GetGraphSizeF_2D().halfY - pTIcon->GetGraphSizeF_2D().y * y ,0.0f };
			}
			else {
				tile.position = { transform_.position_.x - (pTIcon->GetGraphSizeF_2D().x - 7) * x , transform_.position_.y - pTIcon->GetGraphSizeF_2D().y * y ,0.0f };
			}
			tile.num = num;
			pTIcon->SetTileData(tile);
			pTIcon->Set3DPosition({ tile.position.x, tile.position.y,tile.position.z });
			pTIcons_.push_back(pTIcon);
			num++;
		}
	}
}

void TileIcons::Update()
{
	for (auto& itr : pTIcons_) {
		if (itr->GetSelected()) {
			itr->SetSelected(false);
			for (auto& itr : pTIcons_) {
				itr->SetSelect(false);

			}
		}
	}
}
