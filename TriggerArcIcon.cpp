#include "TriggerArcIcon.h"
#include"Mouse.h"
#include"TileIcons.h"
#include"UnitIcons.h"

TriggerArcIcon::TriggerArcIcon(GameObject* parent) : Icon(parent)
{
}

TriggerArcIcon::~TriggerArcIcon()
{
}

void TriggerArcIcon::Initialize()
{
	percent = 50.0f;
	startPercent = 25.0f;
}

void TriggerArcIcon::Update()
{
	if (canVisible_) {
		Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();
		TileIcons* pTileIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TileIcons>();
		SIZE_F_2D tileSize = pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D();
		XMFLOAT2 DrawCenterPos = { position.x + (graphSizeF_.halfX - tileSize.halfX),
			position.y + (graphSizeF_.halfY - tileSize.halfY) };
		XMFLOAT2 leftUp = { DrawCenterPos.x - graphSizeF_.halfX,DrawCenterPos.y - graphSizeF_.halfY};

		if (PointInBox(mousePos,leftUp,{graphSizeF_.halfX,graphSizeF_.halfY})) {
			if (pMouse->IsPressed(Mouse::LEFT)) {

			}
		}
	}
}

void TriggerArcIcon::Draw()
{
	TileIcons* pTileIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TileIcons>();
	SIZE_F_2D tileSize = pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D();
	XMFLOAT2 DrawCenterPos = { position.x + (graphSizeF_.halfX -  tileSize.halfX ),
		position.y + (graphSizeF_.halfY - tileSize.halfY) };
	DrawCircleGaugeF(DrawCenterPos.x, DrawCenterPos.y, percent, hModel, startPercent);
#if 1
	DrawBoxAA(DrawCenterPos.x - graphSizeF_.halfX, DrawCenterPos.y - graphSizeF_.halfY,
		DrawCenterPos.x - graphSizeF_.halfX + graphSizeF_.halfX, DrawCenterPos.y - graphSizeF_.halfY + graphSizeF_.halfY
		, GetColor(255, 0, 0), FALSE);
#endif
	
}