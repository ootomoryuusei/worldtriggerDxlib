#include "rader.h"

rader::rader(GameObject* parent) : Object2D(parent)
{
	/*Load("Assets//Image//rader.png");*/
	/*position = { 1000, 20, 0 };*/

	boxSize[0] = { 80 ,30 };
	boxSize[1] = {300,300};

	transform_.position_ = { 700,100 ,0};

	iconName_ = "レーダー";
}

rader::~rader()
{
}

void rader::Initialize()
{
	int fontSize = 12;
	int fontThickness = 9;
	int fontHandle = CreateFontToHandle("レーダーフォント", fontSize, fontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	fontHandle_ = fontHandle;
}

void rader::Update()
{
	Object2D::Update();
}

void rader::Draw()
{
	//テキスト入り小box
	XMFLOAT2 pos = { position_.x,position_.y };
	boxPos[0] = pos + boxSize[0];
	DrawBoxAA(pos.x, pos.y, boxPos[0].x, boxPos[0].y, GetColor(0, 0, 0), TRUE);
	//大box
	boxPos[1] = { pos.x, boxPos[0].y };
	DrawBoxAA(boxPos[1].x, boxPos[1].y, boxPos[1].x + boxSize[1].x, boxPos[1].y + boxSize[1].y
		, GetColor(0, 0, 0), TRUE);
	/*	DrawGraph(boxPos[1].x + 10 / 2, boxPos[1].y + 10 / 2, hModel, TRUE);*/

	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	XMFLOAT2 space = (boxSize[0] - strSize) / 2;
	XMFLOAT2 fontPos = position_ + space;
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(),
	GetColor(255, 255, 255), fontHandle_, GetColor(0, 0, 0));
}
