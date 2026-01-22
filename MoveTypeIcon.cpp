#include "MoveTypeIcon.h"
#include"Player1.h"
#include"MoveSelectIcon.h"
#include"Mouse.h"
#include"UnitIcons.h"
#include"TileIcons.h"
#include"TriggersArcIcon.h"
#include"GroupManager.h"
#include<algorithm>
#include <queue>
#include <set>

MoveTypeIcon::MoveTypeIcon(GameObject* parent) : Object2D(parent)
{
	LoadSprite("Assets//Image//MoveTypeButton.png");
	transform_.position_ = { 0, 0, 0 };
	fontHandle_ = -1;
	iconName_ = "";
	hImage = LoadGraph("Assets//Image//MoveTypeDownButton.png");
	assert(hImage >= 0);
}

MoveTypeIcon::~MoveTypeIcon()
{
}

void MoveTypeIcon::Initialize()
{
	Object2D::Initialize(); //raycaster2DÇ÷ìoò^
	const auto& pGroupManager_ = GetParent()->GetParent()->GetParent()->FindGameObject<GroupManager>();
	pTileIcons_ = dynamic_cast<TileIcons*>(pGroupManager_->GetGroup("TileIconGroup"));
	Leave();
	Invisible();
}

void MoveTypeIcon::Update()
{
	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	space = { (hitSize_.x - strSize.x) / 2,(hitSize_.y - strSize.y) / 2 };

	clicked = false;

	Object2D::Update();
}

void MoveTypeIcon::Draw()
{
	Object2D::Draw();

	/*if (IsInMousePoint(mousePos)) {
		DrawGraph(position.x, position.y, hImage, TRUE);
	}
	else {
		DrawGraph(position.x, position.y, hModel, TRUE);
	}*/
	XMFLOAT2 fontPos = position_ + space;
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_);
#if 0
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x, position.y + graphSizeF_.y, GetColor(255, 0, 0), FALSE);
#endif
}

void MoveTypeIcon::DeviceEvent(const DoubleClickEvent& event)
{
	switch (event.button)
	{
	case LEFT:
	{
		int CenterNum = -1;
		const auto& pUnitIcons = GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
		auto& select_uniticon = pUnitIcons->GetpSelecting_ptr();
		XMFLOAT3 UnitPos = select_uniticon->GetPosition();
		for (auto& column : pTileIcons_->GetpTIcon()) {
			for (auto& row : column) {
				if (row->GetPosition() == UnitPos) {
					CenterNum = row->GetTileData().num;
				}
			}
		}
		serchAroundTileNum = SerchAroundTileNum(CenterNum, 1);
		for (auto& itrs : serchAroundTileNum) {
			for (auto& column : pTileIcons_->GetpTIcon()) {
				for (auto& row : column) {
					if (row->GetTileData().num == itrs) {
						row->SetSelect(true);
					}
				}
			}
		}
		clicked = true;

		auto& arcs_icon = select_uniticon->GetpTriggersArcIcon();
		for (auto& itr : arcs_icon->GetpTriggerArcIcon()) {
			itr->SetAngle({ itr->GetArcData().startPercent,itr->GetArcData().percent });
		}
	}
		break;
	case RIGHT:
	{
	}
		break;
	case MIDDLE:
	{
	}
		break;
	default:
		break;
	}
}

vector<int> MoveTypeIcon::SerchAroundTileNum(int _CenterNum, int _range)
{
	const int even_directions[6][2] = {
		{+1,  0}, {0, +1}, {-1, 0},
		{-1, -1}, {0, -1}, {+1, -1}
	};

	// x Ç™äÔêî (odd)ÇÃÇ∆Ç´
	const int odd_directions[6][2] = {
		{+1, +1}, {0, +1}, {-1, +1},
		{-1, 0}, {0, -1}, {+1, 0}
	};
	std::vector<int> result;
	int cx = _CenterNum % MAX_MAP_WIDTH;
	int cy = _CenterNum / MAX_MAP_WIDTH;

	std::queue<std::pair<int, int>> open;
	std::set<std::pair<int, int>> visited;

	open.push({ cx, cy });
	visited.insert({ cx, cy });

	for (int r = 0; r < _range; ++r) {
		int size = open.size();
		for (int i = 0; i < size; ++i) {
			auto [x, y] = open.front(); open.pop();

			const int(*dirs)[2] = (x % 2 == 0) ? even_directions : odd_directions;

			for (int d = 0; d < 6; ++d) {
				int nx = x + dirs[d][0];
				int ny = y + dirs[d][1];

				if (nx >= 0 && nx < MAX_MAP_WIDTH && ny >= 0 && ny < MAX_MAP_HIGHT) {
					std::pair<int, int> np = { nx, ny };
					if (visited.count(np) == 0) {
						open.push(np);
						visited.insert(np);
					}
				}
			}
		}
	}

	for (auto& [x, y] : visited) {
		if (x == cx && y == cy) continue; // íÜêSÇèúÇ≠
		int num = y * MAX_MAP_WIDTH + x;
		result.push_back(num);
	}

	return result;
}

void MoveTypeIcon::TypeMove()
{
}

void MoveTypeIcon::SimpleMove()
{
}
