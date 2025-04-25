#include "TriggerArcIcon.h"
#include"Mouse.h"

TriggerArcIcon::TriggerArcIcon(GameObject* parent) : Icon(parent)
{
}

TriggerArcIcon::~TriggerArcIcon()
{
}

void TriggerArcIcon::Initialize()
{
}

void TriggerArcIcon::Update()
{
	if (canVisible_) {
		Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();
		if (IsInMousePoint(mousePos)) {

		}
	}
}

void TriggerArcIcon::Draw()
{
	DrawCircleGaugeF(position.x, position.y, 50.0, hModel, 25.0);
}
