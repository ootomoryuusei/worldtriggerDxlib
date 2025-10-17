#include "Map.h"
#include"TileIcons.h"
#include"GroupManager.h"

Map::Map(GameObject* parent) : Icon(parent,"MAP")
{
	/*position = { 100, 120, 0 };*/
	position = { 700, 120, 0 };
	canVisible_ = true;

	boxSize[0] = { 90 ,40 };
	boxSize[1].x = 450;
	float a = boxSize[1].x / (1.5 * (MAX_MAP_WIDTH - 1) + 2);
	float h = sqrt(3.0) * a;
	float H = MAX_MAP_HIGHT * h;
	boxSize[1] = { boxSize[1].x,H };

	boxPos[0] = { position.x + boxSize[0].x,position.y + boxSize[0].y };
	boxPos[1] = { position.x ,boxPos[0].y };
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

	/*pTileIcons_ = Instantiate<TileIcons>(this);*/
	pGroupManager_ = GetParent()->FindGameObject<GroupManager>();
	pTileIcons_ = pGroupManager_->CreateGroup<TileIcons>("TileIconGroup"); //グループマネージャーでTileIconGroupを作成
}

void Map::Update()
{
	pTileIcons_->SetPosition(position.x,position.y,position.z);

	boxPos[0] = { position.x + boxSize[0].x,position.y + boxSize[0].y };
	boxPos[1] = { position.x, boxPos[0].y };
}

void Map::Draw()
{
	//テキスト入り小box
	DrawBoxAA(position.x, position.y, boxPos[0].x, boxPos[0].y, GetColor(0, 0, 0), TRUE);
	//大box
	DrawBoxAA(boxPos[1].x, boxPos[1].y, boxPos[1].x + boxSize[1].x, boxPos[1].y + boxSize[1].y
		, GetColor(0, 0, 0), TRUE);
	DrawGraph(boxPos[1].x + 10 / 2, boxPos[1].y + 10 / 2, hModel, TRUE);

	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	XMFLOAT2 space = { (boxSize[0].x - strSize.x) / 2,(boxSize[0].y - strSize.y) / 2 };
	VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(),
		GetColor(255, 255, 255), fontHandle_/*, GetColor(0, 0, 0)*/);
}
