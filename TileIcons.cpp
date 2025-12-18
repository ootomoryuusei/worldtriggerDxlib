#include "TileIcons.h"
//#include"TileIcon.h"
#include"GroupManager.h"
#include"Map.h"
#include"Mouse.h"

TileIcons::TileIcons(GameObject* parent) : TypedGroup<TileIcon>()
{

}

TileIcons::~TileIcons()
{
}

void TileIcons::Initialize()
{
    const auto& pMap = GetParent()->GetParent()->FindGameObject<Map>();
    XMFLOAT2 boxPos = pMap->GetBoxPos(1);
	XMFLOAT2 boxSize = pMap->GetBoxSize(1);
	XMFLOAT2 space = { boxSize.x * 0.05f,boxSize.y * 0.05f };
    transform_.position_ = { boxPos.x + space.x, boxPos.y + space.y, 0 };
    int num = 0;
    for (int y = 0; y < MAX_MAP_HIGHT; y++) {
        vector<TileIcon*> row;
        for (int x = 0; x < MAX_MAP_WIDTH; x++) {
            TileIcon* pTIcon = Instantiate<TileIcon>(this);
            XMFLOAT2 size;
            size.x = (MAX_MAP_WIDTH - 1) * (3.0 / 4.0) * pTIcon->GetBaseSizeF().x + pTIcon->GetBaseSizeF().x;
            size.y = MAX_MAP_HIGHT * pTIcon->GetBaseSizeF().y + pTIcon->GetBaseSizeF().halfY();

            XMFLOAT2 scale;
            scale.x = (boxSize.x - space.x * 2) / size.x;
            scale.y = (boxSize.y - space.y * 2) / size.y;
            float m_scale = min(scale.x, scale.y);

            SetScale(m_scale, m_scale, m_scale); //タイルアイコンのスケールをセット
            SetBaseSizeF(pTIcon->GetBaseSizeF()); //タイルアイコンのサイズをセット
            pTIcon->SetScale(transform_.scale_);
            TILEDATA tile;
            XMFLOAT2 pos;
            pos.x = x * (3.0 / 4.0) * pTIcon->GetBaseSizeF().x * transform_.scale_.x;
            pos.y = y * pTIcon->GetBaseSizeF().y * transform_.scale_.y + (x % 2 == 1 ? pTIcon->GetBaseSizeF().y * transform_.scale_.y / 2.0 : 0);
            tile.pos = {transform_.position_.x + pos.x,transform_.position_.y + pos.y,0 };
            tile.num = num;
            tile.offset = VGet(x,y,0);
            pTIcon->SetTileData(tile);
            pTIcon->SetPosition(tile.pos);
            row.push_back(pTIcon);
            num++;
        }
        pTIcons_.push_back(row);
    }
    
}

void TileIcons::Update()
{

  /*  const auto& pMap = GetParent()->GetParent()->FindGameObject<Map>();
    XMFLOAT2 boxPos = pMap->GetBoxPos(1);
    XMFLOAT2 boxSize = pMap->GetBoxSize(1);
    XMFLOAT2 space = { boxSize.x * 0.05f,boxSize.y * 0.05f };
    transform_.position_ = { boxPos.x + space.x, boxPos.y + space.y, 0 };
    int y = 0;
    for (auto& column : pTIcons_) {
        int x = 0;
        for (auto& row : column) {
            TILEDATA tile;
            XMFLOAT2 pos;
            pos.x = x * (3.0 / 4.0) * row->GetGraphSizeF_2D().x * transform_.scale_.x;
            pos.y = y * row->GetGraphSizeF_2D().y * transform_.scale_.y + (x % 2 == 1 ? row->GetGraphSizeF_2D().y * transform_.scale_.y / 2.0 : 0);
            tile.pos = { transform_.position_.x + pos.x,transform_.position_.y + pos.y,0 };
            tile.offset = VGet(x,y,0);
            tile.num = row->GetTileData().num;
            row->SetTileData(tile);
            x++;
        }
        y++;
    }*/
    /*XMFLOAT2 mousePos = pMouse_->GetMousePos();
    for (auto& column : pTIcons_) {
        for (auto& row : column) {
            auto size = row->GetGraphSizeF_2D();
            auto pos = row->Get3DPosition();
            if (PointInBox(mousePos, { pos.x,pos.y }, { size.x,size.y })) {

            }
        }
    }*/

    for (auto& column : pTIcons_) {
        for (auto& row : column) {
            if (row->GetSelected()) {
                row->SetSelected(false);
                for (auto& column : pTIcons_) {
                    for (auto& row : column) {
                        row->SetSelect(false);
                    }
                }
                break;
            }
        }
    }
}

void TileIcons::Draw()
{
}
