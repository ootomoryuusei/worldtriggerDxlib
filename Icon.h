#pragma once
#include "Object3D.h"
#include<vector>

class Icon :
    public Object3D
{
public:
	Icon(GameObject* parent);
	~Icon();
	void Update() override;
	void Draw() override;

	auto GetWay() { return way; }

	bool GetCompWay() { return compWay; }

	void SetCompWay(bool _compWay) { compWay = _compWay; }
private:
	int hTile;
	int hOnTile;
	int hTileFrame;
	int hPIcon;
	int hSelectIcon;

	int hMainCircle;
	int hSubCircle;

	int hATIcon;
	int hDTIcon;
	int hOTIcon;
	int hGTIcon;
	int hSTIcon;

	int prevX, prevY;
	int cX, cY;
	bool prevKey;
	bool compWay;

	float StartAngle, Angle;

	TILEDATA pTile[z][x];

	std::vector<POSITION> way;

	CHARACTER_STATUS getStatus;

	SIZE_2D PgraphSize; //プレイヤーアイコンの画像サイズ
	SIZE_2D MCgraphSize; //メインサークルの画像サイズ
	SIZE_2D SCgraphSize; //サブサークルの画像サイズ
	SIZE_2D TgraphSize; //タイルの画像サイズ

	MYTRIGGER SetTrigger;

	int MouseX, MouseY; //マウス座標

	void KeyInput();

	bool MousePointInBox(POSITION_F _mousePoint, POSITION_F _leftUp, POSITION_F _rightUp, POSITION_F _rightDown,POSITION_F _leftDown);

	void SetTriggerParam(MYTRIGGER& _myTrigger);

	XMINT2 GetSelectedTrigger(MYTRIGGER _myTrigger);
};

