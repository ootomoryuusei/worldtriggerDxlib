#include "MoveTypeIcon.h"
#include"Player1.h"
#include"MoveSelectIcons.h"
#include"Mouse.h"
#include"UnitIcons.h"
#include"TileIcons.h"
#include<algorithm>

MoveTypeIcon::MoveTypeIcon(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//MoveTypeButton.png");
	position = { 0, 0, 0 };
	canVisible_ = false;
	fontHandle_ = -1;
	iconName_ = "";
}

MoveTypeIcon::~MoveTypeIcon()
{
}

void MoveTypeIcon::Update()
{
	if (canVisible_) {
		XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
		space = { (graphSizeF_.x - strSize.x) / 2,(graphSizeF_.y- strSize.y) /2};

		Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();

		if (pMouse->IsDoubleClicked(Mouse::LEFT)) {
			if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x,graphSizeF_.y })) {
				int CenterNum = -1;
				UnitIcons* pUnitIcons = GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
				VECTOR UnitPos = pUnitIcons->GetpUnitIcons()[createNum_]->Get3DPosition();
				TileIcons* pTileIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TileIcons>();
				for (auto& itr : pTileIcons->GetpTIcon()) {
					if (itr->Get3DPosition().x == UnitPos.x && itr->Get3DPosition().y == UnitPos.y && itr->Get3DPosition().z == UnitPos.z) {
						CenterNum = itr->GetTileData().num;
					}
				}
				serchAroundTileNum = SerchAroundTileNum(CenterNum,1);
				for (auto& itrs : serchAroundTileNum) {
					for (auto& itr : pTileIcons->GetpTIcon()) {
						if (itr->GetTileData().num == itrs) {
							itr->SetSelect(true);
						}
					}
				}
				clicked = true;
			}
		}
		else {
			clicked = false;
		}
	}
}

void MoveTypeIcon::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
		VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
		DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_);
#if 0
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x, position.y + graphSizeF_.y, GetColor(255, 0, 0), FALSE);
#endif
	}
}

vector<int> MoveTypeIcon::SerchAroundTileNum(int _CenterNum, int _renge)
{
	std::vector<int> result;
	int cx = _CenterNum % MAX_MAP_WIDTH;
	int cy = _CenterNum / MAX_MAP_WIDTH;

	for (int dx = -_renge; dx <= _renge; ++dx) {
		for (int dy = max(-_renge, -dx - _renge); dy <= min(_renge, -dx + _renge); ++dy) {
			int x = cx + dx;
			int y = cy + dy;

			if (x >= 0 && x < MAX_MAP_WIDTH && y >= 0 && y < MAX_MAP_HIGHT) {
				int num = y * MAX_MAP_WIDTH + x;
				result.push_back(num);
			}
		}
	}

	return result;
}

void MoveTypeIcon::TypeMove()
{
	//	int nowPosnum = -1;
	//	UnitIcons* pUnitIcons = GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
	//	VECTOR UnitPos = pUnitIcons->GetpUnitIcons()[createNum_]->Get3DPosition();
	//	TileIcons* pTileIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TileIcons>();
	//	for (auto& itr : pTileIcons->GetpTIcon()) {
	//		if (itr->Get3DPosition().x == UnitPos.x && itr->Get3DPosition().y == UnitPos.y && itr->Get3DPosition().z == UnitPos.z) {
	//			nowPosnum = itr->GetTileData().num;
	//		}
	//	}
	//	vector<int> aroundNum;
	//	if (nowPosnum % 2 == 0) { //‹ô”
	//		aroundNum.push_back(nowPosnum + MAX_MAP_WIDTH - 1);
	//		aroundNum.push_back(nowPosnum + MAX_MAP_WIDTH);
	//		aroundNum.push_back(nowPosnum + MAX_MAP_WIDTH + 1);
	//		aroundNum.push_back(nowPosnum + 1);
	//		aroundNum.push_back(nowPosnum - MAX_MAP_WIDTH);
	//		aroundNum.push_back(nowPosnum - 1);
	//	}
	//	else { //Šï”
	//		aroundNum.push_back(nowPosnum - 1);
	//		aroundNum.push_back(nowPosnum + MAX_MAP_WIDTH);
	//		aroundNum.push_back(nowPosnum + 1);
	//		aroundNum.push_back(nowPosnum - MAX_MAP_WIDTH - 1);
	//		aroundNum.push_back(nowPosnum - MAX_MAP_WIDTH);
	//		aroundNum.push_back(nowPosnum - MAX_MAP_WIDTH + 1);
	//	}
	//	
	//	for (auto& itrs : aroundNum) {
	//		for (auto& itr : pTileIcons->GetpTIcon()) {
	//			if (itr->GetTileData().num == itrs) {
	//				itr->SetSelect(true);
	//			}
	//		}
	//	}

}

void MoveTypeIcon::SimpleMove()
{
}
