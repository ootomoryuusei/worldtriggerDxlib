#pragma once
#include "Object3D.h"
#include<vector>

using std::vector;

class CsvReader;

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

	XMFLOAT2 GetPIconPos();

	/*int GetWNLine() { return WNLine; }
	int GetALine() { return ALine; }
	int GetSALine() { return SALine; }
	int GetRSLine() { return RSLine; }
	XMINT2 GetCSVSize() { return XMINT2(width, height); }*/
private:
	int state_;
	CsvReader* csv_;

	vector<int> hChSlIcon_;

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

	int WNLine, ALine, SALine, RSLine;
	int width, height;

	TILEDATA pTile[z][x];

	std::vector<XMINT2> way;

	CHARACTER_STATUS getStatus;

	SIZE_2D PgraphSize; //プレイヤーアイコンの画像サイズ
	SIZE_2D MCgraphSize; //メインサークルの画像サイズ
	SIZE_2D SCgraphSize; //サブサークルの画像サイズ
	SIZE_2D TgraphSize; //タイルの画像サイズ

	XMFLOAT2 MCircle;
	XMFLOAT2 SCircle;

	XMFLOAT2 TCenter;

	XMINT2 OtNum;

	XMFLOAT2 PIpos;

	MYTRIGGER SetTrigger;

	int MouseX, MouseY; //マウス座標

	void KeyInput();

	bool MousePointInBox(XMFLOAT2 _mousePoint, XMFLOAT2 _leftUp,XMFLOAT2 _distance);

	void SetTriggerParam(MYTRIGGER& _myTrigger);

	XMINT2 GetSelectedTrigger(MYTRIGGER _myTrigger);

	XMINT2 GetPlayerOnTileNum();
};

