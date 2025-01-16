#include "Icon.h"
#include"Tile.h"
#include"Player1.h"
#include "ImGui/imgui.h"

namespace {
	POSITION_F MCircle;
	POSITION_F SCircle;

	POSITION_F mP1, mP2, mP3, mP4;
	POSITION_F sP1, sP2, sP3, sP4;
	POSITION_F pP1, pP2, pP3, pP4;
	VECTOR P1P2, P2P3, P3P4, P4P1;
	VECTOR P1P, P2P, P3P, P4P;

	POSITION_F TCenter;
}

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

	SetTrigger = { { {ASTEROID,false},{MOONBLADE,false},{FREE,true},{SHIELD,false} }, //Mainの初期化,
		{ {MOONBLADE,false},{FREE,true},{SHIELD,false},{ ASTEROID,false} } }; //Subの初期化

	SetTriggerParam(SetTrigger);
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
	POSITION_F mousePos = { MouseX,MouseY };

	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	VECTOR Tposition;
	VECTOR Pposition = pl1->GetPosition();



	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			Tposition.x = tile->GetTilesData(i, j).position.x;
			Tposition.y = tile->GetTilesData(i, j).position.y;
			Tposition.z = tile->GetTilesData(i, j).position.z;
			if (Tposition.x == Pposition.x && Tposition.y == Pposition.y && Tposition.z == Pposition.z) {
				TCenter = { pTile[i][j].position.x + TgraphSize.halfX, pTile[i][j].position.y + TgraphSize.halfY };

				//maincircle
				mP1 = { TCenter.x - MCgraphSize.halfX,  TCenter.y -MCgraphSize.halfY}; //左上
				mP2 = { TCenter.x + MCgraphSize.halfX, TCenter.y - MCgraphSize.halfY }; //右上
				mP3 = { TCenter.x + MCgraphSize.halfX , TCenter.y + MCgraphSize.halfY }; //右下
				mP4 = { TCenter.x - MCgraphSize.halfX,TCenter.y + MCgraphSize.halfY }; //左下

				//subcircle
				sP1 = { TCenter.x - SCgraphSize.halfX,  TCenter.y - SCgraphSize.halfY }; //左上
				sP2 = { TCenter.x + SCgraphSize.halfX, TCenter.y - SCgraphSize.halfY }; //右上
				sP3 = { TCenter.x + SCgraphSize.halfX , TCenter.y + SCgraphSize.halfY }; //右下
				sP4 = { TCenter.x - SCgraphSize.halfX,TCenter.y + SCgraphSize.halfY }; //左下

				//subcircle
				pP1 = { TCenter.x - SCgraphSize.halfX,  TCenter.y - SCgraphSize.halfY }; //左上
				pP2 = { TCenter.x + SCgraphSize.halfX, TCenter.y - SCgraphSize.halfY }; //右上
				pP3 = { TCenter.x + SCgraphSize.halfX , TCenter.y + SCgraphSize.halfY }; //右下
				pP4 = { TCenter.x - SCgraphSize.halfX,TCenter.y + SCgraphSize.halfY }; //左下
			}
		}
	}

	if (MousePointInBox(mousePos,mP1,mP2,mP3,mP4)) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			StartAngle -= 0.1f;
			Angle -= 0.1f;
		}
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
			StartAngle += 0.1f;
			Angle += 0.1f;
		}
	}

	KeyInput();
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
			}
			
		}
	}

	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			Tposition.x = tile->GetTilesData(i, j).position.x;
			Tposition.y = tile->GetTilesData(i, j).position.y;
			Tposition.z = tile->GetTilesData(i, j).position.z;
			if (Tposition.x == Pposition.x && Tposition.y == Pposition.y && Tposition.z == Pposition.z) {
				
				DrawCircleGauge(TCenter.x,TCenter.y,SetTrigger.Main[main].angle, hMainCircle,SetTrigger.Main[main].startAngle,SetTrigger.Main[main].rangeSize);
				DrawCircleGauge(TCenter.x,TCenter.y, SetTrigger.Sub[sub].angle, hSubCircle, SetTrigger.Sub[sub].startAngle,SetTrigger.Sub[sub].rangeSize);
				DrawGraph(pTile[i][j].position.x + (TgraphSize.halfX - PgraphSize.halfX), pTile[i][j].position.y + (TgraphSize.halfY - PgraphSize.halfY), hPIcon, TRUE);
				DrawBoxAA(TCenter.x - MCgraphSize.halfX * SetTrigger.Main[main].rangeSize, TCenter.y - MCgraphSize.halfY * SetTrigger.Main[main].rangeSize,
					TCenter.x + MCgraphSize.halfX * SetTrigger.Main[main].rangeSize, TCenter.y + MCgraphSize.halfY * SetTrigger.Main[main].rangeSize, GetColor(255, 0, 0), FALSE); //メインサークルのボックス
				DrawBoxAA(TCenter.x - SCgraphSize.halfX * SetTrigger.Sub[sub].rangeSize, TCenter.y - SCgraphSize.halfY * SetTrigger.Sub[sub].rangeSize,
					TCenter.x + SCgraphSize.halfX * SetTrigger.Sub[sub].rangeSize, TCenter.y + SCgraphSize.halfY *SetTrigger.Sub[sub].rangeSize, GetColor(0, 0, 255), FALSE); //サブサークルのボックス
			}
		}
	}

	DrawGraph(pTile[cY][cX].position.x, pTile[cY][cX].position.y, hTileFrame, TRUE);

	/*DrawGraph(0, 0, hSelectIcon, TRUE);

	DrawGraph(0, 0, hATIcon, TRUE);*/

	
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

bool Icon::MousePointInBox(POSITION_F _mousePoint, POSITION_F _leftUp, POSITION_F _rightUp, POSITION_F _rightDown, POSITION_F _leftDown)
{
	P1P2 = { _rightUp.x - _leftUp.x,_rightUp.y - _leftUp.y };
	P2P3 = { _rightDown.x - _rightUp.x,_rightDown.y - _rightUp.y };
	P3P4 = { _leftDown.x - _rightDown.x,_leftDown.y - _rightDown.y };
	P4P1 = { _leftUp.x - _leftDown.x,_leftUp.y - _leftDown.y };

	P1P = { _mousePoint.x - _leftUp.x,_mousePoint.y - _leftUp.y };
	P2P = { _mousePoint.x - _rightUp.x,_mousePoint.y - _rightUp.y };
	P3P = { _mousePoint.x - _rightDown.x,_mousePoint.y - _rightDown.y };
	P4P = { _mousePoint.x - _leftDown.x,_mousePoint.y - _leftDown.y };

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
