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

	std::string GetFilePath(CsvReader* _csv, std::string _DLC, std::string _wontLineName, int _y);
	/*int GetWNLine() { return WNLine; }
	int GetALine() { return ALine; }
	int GetSALine() { return SALine; }
	int GetRSLine() { return RSLine; }
	XMINT2 GetCSVSize() { return XMINT2(width, height); }*/
private:
	CsvReader* csv_;

	vector<int> hChSlIcon_;
	vector<SIZE_2D> hChSlGraphSize_;
	vector<XMFLOAT2> hChSlPos_;
	vector<XMFLOAT2> CSPosition_;

	vector<int> hWpSlIcon_;
	vector<SIZE_2D> hWpSlGraphSize_;
	vector<XMFLOAT2> hWpSlPos_;
	vector<XMFLOAT2> WSPosition_;

	

	int hTile;
	int hOnTile;
	int hTileFrame;
	int hPIcon;
	int hSlIcUI_;
	

	int hChSlUI_;

	int hMainCircle;
	int hSubCircle;

	int prevX, prevY;
	int cX, cY;
	bool prevKey;
	bool compWay;

	int WNLine, ALine, SALine, RSLine;
	int width, height;

	TILEDATA pTile[z][x];

	vector<XMINT2> way;

	CHARACTER_STATUS getStatus;

	SIZE_2D PgraphSize; //プレイヤーアイコンの画像サイズ
	SIZE_2D MCgraphSize; //メインサークルの画像サイズ
	SIZE_2D SCgraphSize; //サブサークルの画像サイズ
	SIZE_2D TgraphSize; //タイルの画像サイズ
	SIZE_2D CSgraphSize; //キャラクターセレクトUIの画像サイズ
	

	XMFLOAT2 MCircle;
	XMFLOAT2 SCircle;

	XMFLOAT2 TCenter;

	XMINT2 OtNum;

	XMFLOAT2 PIpos;

	MYTRIGGER SetTrigger;

	
	void KeyInput();

	void SetTriggerParam(MYTRIGGER& _myTrigger);

	XMINT2 GetSelectedTrigger(MYTRIGGER _myTrigger);

	XMINT2 GetPlayerOnTileNum();
	
	
};

