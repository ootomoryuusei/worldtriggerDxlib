#include "Icon.h"
#include"Tile.h"
#include"Player1.h"
#include "ImGui/imgui.h"



Icon::Icon(GameObject* parent) : Object3D(parent)
{
	hTile = LoadGraph("Assets//Image//Tile.png");
	assert(hTile >= 0);
	hOnTile = LoadGraph("Assets//Image//OnTile.png");
	assert(hOnTile >= 0);
	hTileFrame = LoadGraph("Assets//Image//TileSelectFrame.png");
	assert(hTileFrame >= 0);
	hPIcon = LoadGraph("Assets//Image//pIcon.png");
	assert(hPIcon >= 0);
	hATIcon = LoadGraph("Assets//Image//TriggerIcon//AttackerTrigger0.png");
	assert(hATIcon >= 0);
	hSelectIcon = LoadGraph("Assets//Image//TriggerSetUI.png");
	assert(hSelectIcon >= 0);
	hMainCircle = LoadGraph("Assets//Image//MainTriggerCircle.png");
	assert(hMainCircle >= 0);
	hSubCircle = LoadGraph("Assets//Image//SubTriggerCircle.png");
	assert(hSubCircle >= 0);

	int count = 0;
	float xpos = 1100;
	float ypos = 600;
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			if (j % 2 == 1) {
				pTile[i][j].position = { xpos - j * 26, ypos - 28 / 2 - i * 28 };
			}
			else {
				pTile[i][j].position = { xpos - j * 26, ypos - i * 28 };
			}
			pTile[i][j].num = count;
			count++;
		}
	}
	prevKey = false;
	prevX = 0;
	prevY = 0;
	cX = 0;
	cY = 0;
	compWay = false;

	//アイコンの画像サイズの取得とセット
	GetGraphSize(hPIcon, &PgraphSize.x, &PgraphSize.y);
	PgraphSize.halfX = PgraphSize.x / 2.0f;
	PgraphSize.halfY = PgraphSize.y / 2.0f;
	GetGraphSize(hMainCircle, &MCgraphSize.x, &MCgraphSize.y);
	MCgraphSize.halfX = MCgraphSize.x / 2.0f;
	MCgraphSize.halfY = MCgraphSize.y / 2.0f;
	GetGraphSize(hSubCircle, &SCgraphSize.x, &SCgraphSize.y);
	SCgraphSize.halfX = SCgraphSize.x / 2.0f;
	SCgraphSize.halfY = SCgraphSize.y / 2.0f;
	GetGraphSize(hTile, &TgraphSize.x, &TgraphSize.y);
	TgraphSize.halfX = TgraphSize.x / 2.0f;
	TgraphSize.halfY = TgraphSize.y / 2.0f;

	StartAngle = -15.0;
	Angle = 15.0;

	SetTrigger = { { {ASTEROID,false},{MOONBLADE,true},{FREE,false},{SHIELD,false} }, //Mainの初期化,
		{ {MOONBLADE,false},{FREE,true},{SHIELD,false},{ ASTEROID,false} } }; //Subの初期化

	SetTriggerParam(SetTrigger);

	PIpos = { 0, 0 };
}

Icon::~Icon()
{
	if (hTile > 0) {
		DeleteGraph(hTile);
		hTile = -1;
	}
	if (hTileFrame > 0) {
		DeleteGraph(hTileFrame);
		hTileFrame = -1;
	}
	if (hPIcon > 0) {
		DeleteGraph(hPIcon);
		hPIcon = -1;
	}
	DEL(hSubCircle, 0);
}

void Icon::Update()
{
	SetMouseDispFlag(true); //マウスを表示させるフラグ関数

	GetMousePoint(&MouseX, &MouseY);
	XMFLOAT2 mousePos = { (float)MouseX,(float)MouseY };

	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	VECTOR Tposition;
	VECTOR Pposition = pl1->GetPosition();
	/*OtNum = { GetPlayerOnTileNum() };
	TCenter = { pTile[OtNum.x][OtNum.y].position.x + TgraphSize.halfX, pTile[OtNum.x][OtNum.y].position.y + TgraphSize.halfY };*/

	
	

	/*if (MousePointInBox(mousePos, PIpos, { (float)MCgraphSize.x, (float)MCgraphSize.y })) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			StartAngle -= 0.1f;
			Angle -= 0.1f;
		}
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
			StartAngle += 0.1f;
			Angle += 0.1f;
		}
	}*/

	if (MousePointInBox(mousePos, PIpos, { (float)PgraphSize.x, (float)PgraphSize.y })){
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			PIpos = { mousePos.x - PgraphSize.halfX,mousePos.y - PgraphSize.halfY};
			//pl1->SetPosition(mousePos.x,0.0,mousePos.y);
		}
		else {
			for (int i = 0; i < z; i++) {
				for (int j = 0; j < x; j++) {
					if (z - i <= 2 || z - i >= 10) {
						if (MousePointInBox(mousePos, { pTile[i][j].position.x,pTile[i][j].position.y }
							, { (float)TgraphSize.x,(float)TgraphSize.y })) {
							PIpos = { pTile[i][j].position.x ,pTile[i][j].position.y  };
						}
					}
				}
			}
		}
	}
	KeyInput();

	ImGui::Begin("position");
	ImGui::InputFloat("X", &PIpos.x);
	ImGui::InputFloat("Y", &PIpos.y);
	ImGui::End();
}

void Icon::Draw()
{
	int main, sub;
	main = GetSelectedTrigger(SetTrigger).x;
	sub = GetSelectedTrigger(SetTrigger).y;
	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	VECTOR Tposition;
	VECTOR Pposition = pl1->GetPosition();

	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			DrawGraph(pTile[i][j].position.x, pTile[i][j].position.y, hTile, TRUE);
			if (z - i <= 2 || z - i >= 10) {
				DrawGraph(pTile[i][j].position.x, pTile[i][j].position.y, hOnTile, TRUE);
#if 0 
				DrawBoxAA(pTile[i][j].position.x, pTile[i][j].position.y, pTile[i][j].position.x + TgraphSize.x, pTile[i][j].position.y + TgraphSize.y
					, GetColor(0, 0, 255), FALSE); //tileのボックス
#endif
			}
		}
	}
	XMFLOAT2 PICenter = { PIpos.x + PgraphSize.halfX, PIpos.y + PgraphSize.halfY };
	
	DrawCircleGauge(PICenter.x + PgraphSize.halfX, PICenter.y + PgraphSize.halfY, SetTrigger.Main[main].angle, hMainCircle, SetTrigger.Main[main].startAngle, SetTrigger.Main[main].rangeSize);
	DrawCircleGauge(PICenter.x + PgraphSize.halfX, PICenter.y + PgraphSize.halfY, SetTrigger.Sub[sub].angle, hSubCircle, SetTrigger.Sub[sub].startAngle, SetTrigger.Sub[sub].rangeSize);
	/*DrawGraph(pTile[cY][cX].position.x, pTile[cY][cX].position.y, hTileFrame, TRUE);*/
	/*DrawGraph(0, 0, hSelectIcon, TRUE);
	DrawGraph(0, 0, hATIcon, TRUE);*/
	DrawGraph(PICenter.x, PICenter.y, hPIcon, TRUE);
#if 0 //ボックス
	DrawBoxAA(PIpos.x, PIpos.y,
		PIpos.x + PgraphSize.x, PIpos.y + PgraphSize.y, GetColor(0, 0, 255), FALSE); //playerIconのボックス
	DrawBoxAA(TCenter.x - MCgraphSize.halfX * SetTrigger.Main[main].rangeSize, TCenter.y - MCgraphSize.halfY * SetTrigger.Main[main].rangeSize,
		TCenter.x + MCgraphSize.halfX * SetTrigger.Main[main].rangeSize, TCenter.y + MCgraphSize.halfY * SetTrigger.Main[main].rangeSize, GetColor(255, 0, 0), FALSE); //メインサークルのボックス
	DrawBoxAA(TCenter.x - SCgraphSize.halfX * SetTrigger.Sub[sub].rangeSize, TCenter.y - SCgraphSize.halfY * SetTrigger.Sub[sub].rangeSize,
		TCenter.x + SCgraphSize.halfX * SetTrigger.Sub[sub].rangeSize, TCenter.y + SCgraphSize.halfY * SetTrigger.Sub[sub].rangeSize, GetColor(0, 0, 255), FALSE); //サブサークルのボックス

#endif
}

XMFLOAT2 Icon::GetPIconPos()
{
	XMFLOAT2 tile3DPosition;
	Tile* tile = GetParent()->FindGameObject<Tile>();
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			if (pTile[i][j].position.x == PIpos.x && pTile[i][j].position.y == PIpos.y) {
				tile3DPosition = { tile->GetTilesData(i, j).position.x,tile->GetTilesData(i, j).position.z};
				return tile3DPosition;
			}
		}
	}
	return XMFLOAT2(0,0);
}

void Icon::KeyInput()
{
	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	getStatus = pl1->GetCStatus();
	int size = way.size();

	if (CheckHitKey(KEY_INPUT_UP)) {
		if (prevKey == false) {
			prevY = cY;
			cY += 1;
			if (cY > z - 1) {
				cY = prevY;
			}
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN)) {
		if (prevKey == false) {
			prevY = cY;
			cY -= 1;
			if (cY < 0) {
				cY = prevY;
			}
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		if (prevKey == false) {
			prevX = cX;
			cX += 1;
			if (cX > x - 1) {
				cX = prevX;
			}
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (prevKey == false) {
			prevX = cX;
			cX -= 1;
			if (cX < 0) {
				cX = prevX;
			}
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_RETURN)) {
		if (prevKey == false) {

			if (size < getStatus.move) {
				way.push_back({ cX,cY });
			}
		}
		prevKey = true;
	}
	else {
		prevKey = false;
	}

	if (size >= getStatus.move) {
		compWay = true;
	}

	pl1->SetMyTrigger(SetTrigger);
}

bool Icon::MousePointInBox(XMFLOAT2 _mousePoint, XMFLOAT2 _LeftUp, XMFLOAT2 _distance)
{
	VECTOR P1P2, P2P3, P3P4, P4P1;
	VECTOR P1P, P2P, P3P, P4P;
	XMFLOAT2 P1, P2, P3, P4;

	P1 = { _LeftUp.x,  _LeftUp.y }; //左上
	P2 = { _LeftUp.x + _distance.x,  _LeftUp.y }; //右上
	P3 = { _LeftUp.x + _distance.x,  _LeftUp.y + _distance.y}; //右下
	P4 = { _LeftUp.x,  _LeftUp.y + _distance.y}; //左下

	P1P2 = { P2.x - P1.x, P2.y - P1.y };
	P2P3 = { P3.x - P2.x, P3.y - P2.y };
	P3P4 = { P4.x - P3.x, P4.y - P3.y };
	P4P1 = { P1.x - P4.x, P1.y - P4.y };

	P1P = { _mousePoint.x - P1.x,_mousePoint.y - P1.y };
	P2P = { _mousePoint.x - P2.x,_mousePoint.y - P2.y };
	P3P = { _mousePoint.x - P3.x,_mousePoint.y - P3.y };
	P4P = { _mousePoint.x - P4.x,_mousePoint.y - P4.y };

	if (VCross(P1P2, P1P).z >= 0 && VCross(P2P3, P2P).z >= 0 && VCross(P3P4, P3P).z >= 0 && VCross(P4P1, P4P).z >= 0)
	{
		return true;
	}
	return false;
}

void Icon::SetTriggerParam(MYTRIGGER& _myTrigger)
{
	for (int i = 0; i < 4; i++) {
		switch (_myTrigger.Main[i].trigger)
		{
		case FREE:
		{
			_myTrigger.Main[i].angle = 0;
			_myTrigger.Main[i].startAngle = 0;
			_myTrigger.Main[i].rangeSize = 0;
			break;
		}
		case MOONBLADE:
		{
			_myTrigger.Main[i].angle = 15;
			_myTrigger.Main[i].startAngle = -15;
			_myTrigger.Main[i].rangeSize = 1;
			break;
		}
		case SHIELD:
		{
			_myTrigger.Main[i].angle = 15;
			_myTrigger.Main[i].startAngle = -15;
			_myTrigger.Main[i].rangeSize = 1;
			break;
		}
		case ASTEROID:
		{
			_myTrigger.Main[i].angle = 15;
			_myTrigger.Main[i].startAngle = -15;
			_myTrigger.Main[i].rangeSize = 1.5;
			break;
		}
		default:
			break;
		}

		switch (_myTrigger.Sub[i].trigger)
		{
		case FREE:
		{
			_myTrigger.Sub[i].angle = 0;
			_myTrigger.Sub[i].startAngle = 0;
			_myTrigger.Sub[i].rangeSize = 0;
			break;
		}
		case MOONBLADE:
		{
			_myTrigger.Sub[i].angle = 15;
			_myTrigger.Sub[i].startAngle = -15;
			_myTrigger.Sub[i].rangeSize = 1;
			break;
		}
		case SHIELD:
		{
			_myTrigger.Sub[i].angle = 15;
			_myTrigger.Sub[i].startAngle = -15;
			_myTrigger.Sub[i].rangeSize = 1;
			break;
		}
		case ASTEROID:
		{
			_myTrigger.Sub[i].angle = 15;
			_myTrigger.Sub[i].startAngle = -15;
			_myTrigger.Sub[i].rangeSize = 1.5;
			break;
		}
		default:
			break;
		}
	}
}

XMINT2 Icon::GetSelectedTrigger(MYTRIGGER _myTrigger)
{
	int main, sub;
	for (int i = 0; i < 4; i++) {
		if (_myTrigger.Main[i].IsSelected) {
			main = i;
		}

		if (_myTrigger.Sub[i].IsSelected) {
			sub = i;
		}
	}
	return XMINT2(main,sub);
}

XMINT2 Icon::GetPlayerOnTileNum()
{
	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	VECTOR Tposition;
	VECTOR Pposition = pl1->GetPosition();
	XMINT2 XY = { 0,0};
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			Tposition.x = tile->GetTilesData(i, j).position.x;
			Tposition.y = tile->GetTilesData(i, j).position.y;
			Tposition.z = tile->GetTilesData(i, j).position.z;
			if (Tposition.x == Pposition.x && Tposition.y == Pposition.y && Tposition.z == Pposition.z) {
				XY.x = i;
				XY.y = j;
			}
		}
	}
	return XMINT2(XY.x,XY.y);
}
