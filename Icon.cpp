#include "Icon.h"
#include"Tile.h"
#include"Player1.h"

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
}

void Icon::Update()
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
}

void Icon::Draw()
{
	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	int TpositionX;
	int TpositionZ;

	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			DrawGraph(pTile[i][j].position.x, pTile[i][j].position.y, hTile, TRUE);
		}
	}

	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			TpositionX = tile->GetTilesData(i, j).position.x;
			TpositionZ = tile->GetTilesData(i, j).position.z;
			if (TpositionX == pl1->GetPosition().x && TpositionZ == pl1->GetPosition().z) {
				DrawGraph(pTile[i][j].position.x, pTile[i][j].position.y,hPIcon, TRUE);
			}
		}
	}

	DrawGraph(pTile[cY][cX].position.x, pTile[cY][cX].position.y, hTileFrame, TRUE);

	DrawGraph(0,0 ,hATIcon, TRUE);
}
