#include "Icon.h"
#include"Tile.h"
#include"Player1.h"
#include "ImGui/imgui.h"

Icon::Icon(GameObject* parent) : Object3D(parent)
{
	hTile = LoadGraph("Assets//Image//Tile.png");
	assert(hTile >= 0);
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


	SetTrigger = { { {ASTEROID,false},{MOONBLADE,true},{FREE,false},{SHIELD,false} }, //Mainの初期化,
		{ {MOONBLADE,true},{FREE,false},{SHIELD,false},{ ASTEROID,false} } }; //Subの初期化
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
	SetMouseDispFlag(true);

	GetMousePoint(&MouseX, &MouseY);
	POSITION_F mousePos = { MouseX,MouseY };

	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	VECTOR Tposition;
	VECTOR Pposition = pl1->GetPosition();

	POSITION_F P1, P2, P3, P4;
	VECTOR P1P2, P2P3, P3P4, P4P1;
	VECTOR P1P, P2P, P3P, P4P;

	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			Tposition.x = tile->GetTilesData(i, j).position.x;
			Tposition.y = tile->GetTilesData(i, j).position.y;
			Tposition.z = tile->GetTilesData(i, j).position.z;
			if (Tposition.x == Pposition.x && Tposition.y == Pposition.y && Tposition.z == Pposition.z) {
				POSITION_F MCircle;
				POSITION_F SCircle;
				MCircle.x = pTile[i][j].position.x;
				MCircle.y = pTile[i][j].position.y;
				SCircle.x = pTile[i][j].position.x;
				SCircle.y = pTile[i][j].position.y;

				P1 = { MCircle.x,MCircle.y };
				P2 = { MCircle.x + TgraphSize.x,MCircle.y };
				P3 = { MCircle.x + TgraphSize.x,MCircle.y + TgraphSize.y};
				P4 = { MCircle.x ,MCircle.y +TgraphSize.y};

				P1P2 = { P2.x - P1.x,P2.y - P1.y };
				P2P3 = { P3.x - P2.x,P3.y - P2.y };
				P3P4 = { P4.x - P3.x,P4.y - P3.y };
				P4P1 = { P1.x - P4.x,P1.y - P4.y };

				P1P = { mousePos.x - P1.x,mousePos.y - P1.y };
				P2P = { mousePos.x - P2.x,mousePos.y - P2.y };
				P3P = { mousePos.x - P3.x,mousePos.y - P3.y };
				P4P = { mousePos.x - P4.x,mousePos.y - P4.y };
			}
		}
	}
	
	if ((VCross(P1P2, P1P).x < 0 && VCross(P1P2, P1P).y < 0) && (VCross(P2P3, P2P).x < 0 && VCross(P2P3, P2P).y < 0)
		&& (VCross(P3P4, P3P).x < 0 && VCross(P3P4, P3P).y < 0) && (VCross(P4P1, P4P).x < 0 && VCross(P4P1, P4P).y < 0)) 
	{
		CircleSelected = true;
	}

	ImGui::Begin("rotation");
	ImGui::InputFloat("X", &mousePos.x);
	ImGui::InputFloat("Y", &mousePos.y);
	ImGui::End();
	KeyInput();
}

void Icon::Draw()
{
	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	VECTOR Tposition;
	VECTOR Pposition = pl1->GetPosition();

	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			DrawGraph(pTile[i][j].position.x, pTile[i][j].position.y, hTile, TRUE);
		}
	}

	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			Tposition.x = tile->GetTilesData(i, j).position.x;
			Tposition.y = tile->GetTilesData(i, j).position.y;
			Tposition.z = tile->GetTilesData(i, j).position.z;
			if (Tposition.x == Pposition.x && Tposition.y == Pposition.y && Tposition.z == Pposition.z) {
				DrawCircleGauge(pTile[i][j].position.x + TgraphSize.halfX, pTile[i][j].position.y + TgraphSize.halfY, 15.0, hMainCircle, -15.0,1.0f);
				DrawCircleGauge(pTile[i][j].position.x + TgraphSize.halfX, pTile[i][j].position.y + TgraphSize.halfY, 15.0, hSubCircle, -15.0, 1.0f);
				DrawGraph(pTile[i][j].position.x + (TgraphSize.halfX - PgraphSize.halfX), pTile[i][j].position.y + (TgraphSize.halfY - PgraphSize.halfY), hPIcon, TRUE);
				
			}
		}
	}

	DrawGraph(pTile[cY][cX].position.x, pTile[cY][cX].position.y, hTileFrame, TRUE);

	DrawGraph(0, 0, hSelectIcon, TRUE);

	DrawGraph(0, 0, hATIcon, TRUE);
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
