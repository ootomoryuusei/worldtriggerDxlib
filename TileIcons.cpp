#include "TileIcons.h"
//#include"TileIcon.h"
#include"GroupManager.h"
#include"Map.h"

TileIcons::TileIcons(GameObject* parent) : Icon(parent)
{

}

TileIcons::~TileIcons()
{
}

void TileIcons::Initialize()
{
    const auto& pMap = GetParent()->GetParent()->FindGameObject<Map>();
	XMFLOAT2 boxSize = pMap->GetBoxSize(1);
	XMFLOAT2 space = { boxSize.x * 0.05f,boxSize.y * 0.05f };
    position = { position.x + space.x, position.y + space.y, 0 };
    int num = 0;
    for (int y = 0; y < MAX_MAP_HIGHT; y++) {
        vector<TileIcon*> row;
        for (int x = 0; x < MAX_MAP_WIDTH; x++) {
            TileIcon* pTIcon = Instantiate<TileIcon>(this);
            XMFLOAT2 size;
            size.x = (MAX_MAP_WIDTH - 1) * (3.0 / 4.0) * pTIcon->GetGraphSizeF_2D().x + pTIcon->GetGraphSizeF_2D().x;
            size.y = MAX_MAP_HIGHT * pTIcon->GetGraphSizeF_2D().y + pTIcon->GetGraphSizeF_2D().halfY;

            XMFLOAT2 scale;
            scale.x = (boxSize.x - space.x * 2) / size.x;
            scale.y = (boxSize.y - space.y * 2) / size.y;
            float m_scale = min(scale.x, scale.y);

            scale_ = { m_scale ,m_scale ,m_scale };
            pTIcon->SetScale(scale_);
            TILEDATA tile;
            XMFLOAT2 pos;
            pos.x = x * (3.0 / 4.0) * pTIcon->GetGraphSizeF_2D().x * scale_.x;
            pos.y = y * pTIcon->GetGraphSizeF_2D().y * scale_.y + (x % 2 == 1 ? pTIcon->GetGraphSizeF_2D().y * scale_.y / 2.0 : 0);
            tile.pos = {position.x + pos.x,position.y + pos.y,0 };
            tile.num = num;
            pTIcon->SetTileData(tile);
            pTIcon->Set3DPosition(tile.pos);
            row.push_back(pTIcon);
            num++;
        }
        pTIcons_.push_back(row);
    }
}

void TileIcons::Update()
{
    const auto& pMap = GetParent()->GetParent()->FindGameObject<Map>();
    XMFLOAT2 boxSize = pMap->GetBoxSize(1);
    XMFLOAT2 space = { boxSize.x * 0.05f,boxSize.y * 0.05f };
    position = { position.x + space.x, position.y + space.y, 0 };

    int y = 0;
    for (auto& column : pTIcons_) {
        int x = 0;
        for (auto& row : column) {
            TILEDATA tile;
            XMFLOAT2 pos;
            pos.x = x * (3.0 / 4.0) * row->GetGraphSizeF_2D().x * scale_.x;
            pos.y = y * row->GetGraphSizeF_2D().y * scale_.y + (x % 2 == 1 ? row->GetGraphSizeF_2D().y * scale_.y / 2.0 : 0);
            tile.pos = { position.x + pos.x,position.y + pos.y,0 };
            tile.offset = VGet(x,y,0);
            row->SetTileData(tile);
            x++;
        }
        y++;
    }
    for (auto& column : pTIcons_) {
        for (auto& row : column) {
            if (row->GetSelected()) {
                row->SetSelected(false);
                for (auto& row : column) {
                    row->SetSelect(false);
                }
            }
        }
    }
	/*for (auto& itr : pTIcons_) {
		if (itr->GetSelected()) {
			itr->SetSelected(false);
			for (auto& itr : pTIcons_) {
				itr->SetSelect(false);

			}
		}
	}*/
}
