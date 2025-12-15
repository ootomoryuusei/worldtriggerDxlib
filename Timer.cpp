#include "Timer.h"
#include"Mouse.h"
#include"UnitIcons.h"

Timer::Timer(GameObject* parent) : Object2D(parent)
{
	transform_.position_ = { 1050, 100, 0 };

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
	Object2D::Update();
}

void Timer::Draw()
{
	//テキスト入り小box
	XMFLOAT2 pos = { position_.x,position_.y };
	XMFLOAT2 pos2 = pos + boxSize;
	DrawBoxAA(pos.x, pos.y, pos2.x, pos2.y, GetColor(0, 0, 0), FALSE,1.5f);

	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	XMFLOAT2 space = (boxSize - strSize) / 2;
	XMFLOAT2 fontPos =  position_ + space;
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_,GetColor(255,255,255));
}

void Timer::DeviceEvent(const DoubleClickEvent& event)
{
	switch (event.button)
	{
	case LEFT:
	{
		UnitIcons* pUnitIcons = GetParent()->FindGameObject<UnitIcons>();
		pUnitIcons->SetMoveMentSet(true);
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