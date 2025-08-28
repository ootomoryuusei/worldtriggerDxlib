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
	XMFLOAT2 space = { boxSize.x * 0.05f,boxSize.y * 0.05f };
    transform_.position_ = { boxPos.x + space.x, boxPos.y + space.y, 0 };
    int num = 0;
    for (int y = 0; y < MAX_MAP_HIGHT; y++) {
        for (int x = 0; x < MAX_MAP_WIDTH; x++) {
            TileIcon* pTIcon = Instantiate<TileIcon>(this);
            XMFLOAT2 size;
            size.x = (MAX_MAP_WIDTH - 1) * (3.0 / 4.0) * pTIcon->GetGraphSizeF_2D().x + pTIcon->GetGraphSizeF_2D().x;
            size.y = MAX_MAP_HIGHT * pTIcon->GetGraphSizeF_2D().y + pTIcon->GetGraphSizeF_2D().halfY;

            XMFLOAT2 scale;
            scale.x = (boxSize.x - space.x * 2) / size.x;
            scale.y = (boxSize.y - space.y * 2) / size.y;
            float m_scale = min(scale.x, scale.y);

            pTIcon->SetScale({m_scale, m_scale, m_scale});
            TILEDATA tile;
            XMFLOAT2 pos;
            pos.x = x * (3.0 / 4.0) * pTIcon->GetGraphSizeF_2D().x * m_scale;
            pos.y = y * pTIcon->GetGraphSizeF_2D().y * m_scale + (x % 2 == 1 ? pTIcon->GetGraphSizeF_2D().y * m_scale / 2.0 : 0);
            tile.position = {transform_.position_.x + pos.x,transform_.position_.y + pos.y,0 };
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
