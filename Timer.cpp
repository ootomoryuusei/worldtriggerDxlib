#include "Timer.h"
#include"Mouse.h"
#include"UnitIcons.h"

Timer::Timer(GameObject* parent) : Icon(parent)
{
	position = { 1050, 100, 0 };
	canVisible_ = true;

	/*iconName_ = "演習開始まで";*/

	iconName_ = "実行";

	boxSize = { 200,120 };
}

Timer::~Timer()
{
}

void Timer::Initialize()
{
	int fontSize = 20;
	int fontThickness = 9;
	int fontHandle = CreateFontToHandle("タイマーフォント", fontSize, fontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	fontHandle_ = fontHandle;
}

void Timer::Update()
{
	Mouse* pMouse = GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 m_pos = pMouse->GetMousePos();
	UnitIcons* pUnitIcons = GetParent()->FindGameObject<UnitIcons>();

	if (PointInBox(m_pos, { position.x, position.y }, boxSize)) {
		if (pMouse->IsDoubleClicked(Mouse::LEFT)) {
			pUnitIcons->SetMoveMentSet(true);
		}
	}
}

void Timer::Draw()
{
	//テキスト入り小box
	XMFLOAT2 pos = { position.x,position.y };
	XMFLOAT2 pos2 = { pos.x + boxSize.x,pos.y + boxSize.y };
	DrawBoxAA(pos.x, pos.y, pos2.x, pos2.y, GetColor(0, 0, 0), FALSE,1.5f);

	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	XMFLOAT2 space = { (boxSize.x - strSize.x) / 2,(boxSize.y - strSize.y) / 2 };
	VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_,GetColor(255,255,255));
}
