#include "Tile.h"
#include"Player1.h"
#include "ImGui/imgui.h"

Tile::Tile(GameObject* parent) : Object3D(parent)
{
	tWSize = 1.5;
	tHSize = 1.75;
	hModel = MV1LoadModel("Assets//Tile.mv1");
	assert(hModel >= 0);
	hTile = LoadGraph("Assets//Image//Tile.png");
	assert(hTile >= 0);
	hTileFrame = LoadGraph("Assets//Image//TileSelectFrame.png");
	assert(hTileFrame >= 0);
	position = VGet(0, 0, 0);
	rotation.y = XMConvertToRadians(90.0f);
	int count = 0;
	float xpos = 1100;
	float ypos = 600;
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			if (j % 2 == 1) {
				Tiles[i][j].position = { position.x + tWSize * j,position.y,position.z - tHSize/2 - tHSize * i };
				pTile[i][j].position = { xpos - j * 26, ypos - 28 / 2 - i * 28 };
			}
			else {
				Tiles[i][j].position = { position.x + tWSize * j,position.y,position.z - tHSize * i };
				pTile[i][j].position = { xpos - j * 26, ypos - i * 28 };
			}
			
			Tiles[i][j].num = count;
			pTile[i][j].num = count;
			count++;
		}
	}
	prevKey = false;
	prevX = 0;
	prevY = 0;
	cX = 0;
	cY = 0;
}

Tile::~Tile()
{
	if(hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
	if (hTile > 0) {
		DeleteGraph(hTile);
		hTile = -1;
	}
	if (hTileFrame > 0) {
		DeleteGraph(hTileFrame);
		hTileFrame = -1;
	}
}

void Tile::Update()
{
	//// カメラの設定
	//MATRIX mRot = MGetRotY(rotation.y);  // 回転行列
	//// 回ってないとき、プレイヤーからどれぐらい後ろ？→ベクトル
	//VECTOR tmpP = VGet(0, 200, -300);
	//// これに回転行列をかける
	//VECTOR pRot = tmpP * mRot;
	//// これにプレイヤーの座標を足すと、カメラ位置が出る
	//VECTOR vRot = VGet(0, 200, -300) * mRot;
	//SetCameraPositionAndTarget_UpVecY(position + pRot, position + vRot);
	/*rotation.y += 0.01;

	ImGui::Begin("rotation");
	ImGui::InputFloat("X", &rotation.x);
	ImGui::InputFloat("Y", &rotation.y);
	ImGui::InputFloat("Z", &rotation.z);
	ImGui::End();*/

	if (CheckHitKey(KEY_INPUT_W)) {
		if (prevKey == false) {
			prevY = cY;
			cY += 1;
			if (cY > z - 1) {
				cY = prevY;
			}
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_S)) {
		if (prevKey == false) {
			prevY = cY;
			cY -= 1;
			if (cY < 0) {
				cY = prevY;
			}
		}
		prevKey = true;
	}else if (CheckHitKey(KEY_INPUT_A)) {
		if (prevKey == false) {
			prevX = cX;
			cX += 1;
			if (cX > x - 1) {
				cX = prevX;
			}
		}
		prevKey = true;
	}else if (CheckHitKey(KEY_INPUT_D)) {
		if (prevKey == false) {
			prevX = cX;
			cX -= 1;
			if (cX < 0) {
				cX = prevX;
			}
		}
		prevKey = true;	
	}else {
		prevKey = false;
	}

	if (CheckHitKey(KEY_INPUT_RETURN)) {
		Player1* pl1 = GetParent()->FindGameObject<Player1>();
		getStatus = pl1->GetCStatus();
		int size = way.size();
		if (getStatus.move > size) {
			way[size] = (cY, cX);
		}
		else {

		}
		
	}
}

void Tile::Draw()
{
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			MV1SetMatrix(hModel, Object3D::ChangeFLOAT3ToMATRIX(Tiles[i][j].position, rotation));
			MV1DrawModel(hModel);
		}
	}

	/*MV1SetMatrix(hModel, Object3D::ChangeFLOAT3ToMATRIX(Tiles[0][1].position, rotation));
	MV1DrawModel(hModel);*/

	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			DrawGraph(pTile[i][j].position.x,pTile[i][j].position.y, hTile, TRUE);
		}
	}

	DrawGraph(pTile[cY][cX].position.x,pTile[cY][cX].position.y, hTileFrame, TRUE);
}
