#include "Map.h"
#include"TileIcons.h"
#include"GroupManager.h"
#include"Mouse.h"

Map::Map(GameObject* parent) : Object2D(parent,"MAP")
{
	/*position = { 100, 120, 0 };*/
	transform_.position_ = { 700, 120, 0 };

	boxSize[0] = { 90 ,40 };
	boxSize[1].x = 450;
	float a = boxSize[1].x / (1.5 * (MAX_MAP_WIDTH - 1) + 2);
	float h = sqrt(3.0) * a;
	float H = MAX_MAP_HIGHT * h;
	boxSize[1] = { boxSize[1].x,H };

	boxPos[0] = { transform_.position_.x + boxSize[0].x,transform_.position_.y + boxSize[0].y };
	boxPos[1] = { transform_.position_.x ,boxPos[0].y };
	iconName_ = "MAP";
}

Map::~Map()
{
}

void Map::Initialize()
{
	int fontSize = 30;
	int fontThickness = 9;
	fontHandle_ = CreateFontToHandle("MAPフォント", fontSize, fontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	pGroupManager_ = GetParent()->FindGameObject<GroupManager>();
	pTileIcons_ = Instantiate<TileIcons>(this);
	pGroupManager_->RegisterGroup<TileIcons>("TileIconGroup",pTileIcons_); //グループマネージャーでTileIconGroupを作成
}

void Map::Update()
{
	const auto& group = pGroupManager_->GetGroup("enemyGroup");
	/*Mouse* pMouse = GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();

	XMFLOAT2 size = { boxSize[0].x + boxSize[0].x,boxSize[1].y + boxSize[1].y };
	if (PointInBox(mousePos, { position.x, position.y }, {size.x,size.y})) {
		if (pMouse->IsPressed(Mouse::LEFT)) {
			XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
			position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };

		}
		prevMousePos_ = mousePos;
	}*/

	pTileIcons_->SetPosition(transform_.position_);

	boxPos[0] = { transform_.position_.x + boxSize[0].x,transform_.position_.y + boxSize[0].y };
	boxPos[1] = { transform_.position_.x, boxPos[0].y };
	Object2D::Update();
}

void Map::Draw()
{
	//テキスト入り小box
	DrawBoxAA(position_.x, position_.y, boxPos[0].x, boxPos[0].y, GetColor(0, 0, 0), TRUE);
	//大box
	DrawBoxAA(boxPos[1].x, boxPos[1].y, boxPos[1].x + boxSize[1].x, boxPos[1].y + boxSize[1].y
		, GetColor(0, 0, 0), TRUE);
	DrawGraph(boxPos[1].x + 10 / 2, boxPos[1].y + 10 / 2, hModel_, TRUE);

	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	XMFLOAT2 space = (boxSize[0] - strSize) / 2;
	XMFLOAT2 fontPos = position_ + space;
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(),
		GetColor(255, 255, 255), fontHandle_/*, GetColor(0, 0, 0)*/);
}
