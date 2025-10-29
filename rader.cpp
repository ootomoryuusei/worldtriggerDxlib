#include "rader.h"

rader::rader(GameObject* parent) : Icon(parent)
{
	/*Load("Assets//Image//rader.png");*/
	/*position = { 1000, 20, 0 };*/

	boxSize[0] = { 80 ,30 };
	boxSize[1] = {300,300};

	position = { 700,100 };

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
}

void rader::Draw()
{
	//テキスト入り小box
	XMFLOAT2 pos = { position.x,position.y };
	boxPos[0] = { pos.x + boxSize[0].x,pos.y + boxSize[0].y };
	DrawBoxAA(pos.x, pos.y, boxPos[0].x, boxPos[0].y, GetColor(0, 0, 0), TRUE);
	//大box
	boxPos[1] = { pos.x, boxPos[0].y };
	DrawBoxAA(boxPos[1].x, boxPos[1].y, boxPos[1].x + boxSize[1].x, boxPos[1].y + boxSize[1].y
		, GetColor(0, 0, 0), TRUE);
	/*	DrawGraph(boxPos[1].x + 10 / 2, boxPos[1].y + 10 / 2, hModel, TRUE);*/

	XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
	XMFLOAT2 space = { (boxSize[0].x - strSize.x) / 2,(boxSize[0].y - strSize.y) / 2 };
	VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
	DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(),
	GetColor(255, 255, 255), fontHandle_, GetColor(0, 0, 0));
}
