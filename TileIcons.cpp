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
	XMFLOAT2 boxPos = pMap->GetBoxPos(1);
	XMFLOAT2 space = { boxSize.x / (MAX_MAP_WIDTH + 2),boxSize.y / (MAX_MAP_HIGHT + 2) };
    transform_.position_ = { boxPos.x + space.x, boxPos.y + space.y, 0 };
    int num = 0;
    for (int y = 0; y < MAX_MAP_HIGHT; y++) {
        for (int x = 0; x < MAX_MAP_WIDTH; x++) {
            TileIcon* pTIcon = Instantiate<TileIcon>(this);
            VECTOR scale = {
                space.x / pTIcon->GetGraphSizeF_2D().x,space.y / pTIcon->GetGraphSizeF_2D().y,1};
            pTIcon->SetScale(scale);
            // スケーリング後のサイズ
            XMFLOAT2 scaledSize = {
                pTIcon->GetGraphSizeF_2D().x * scale.x,
                pTIcon->GetGraphSizeF_2D().y * scale.y
            };
            TILEDATA tile;
            if (x % 2 == 1) {
                tile.position = {
                    transform_.position_.x + scaledSize.x * 0.75f * x,
                    transform_.position_.y + scaledSize.y * y + scaledSize.y * 0.5f,
                    0.0f
                };
            }
            else {
                tile.position = {
                    transform_.position_.x + scaledSize.x * 0.75f * x,
                    transform_.position_.y + scaledSize.y * y,
                    0.0f
                };
            }
            tile.num = num;
            pTIcon->SetTileData(tile);
            pTIcon->Set3DPosition(tile.position);
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
