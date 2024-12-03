#include "Tile.h"

Tile::Tile(GameObject* parent) : Object3D(parent)
{
	tWSize = 1.7;
	tHSize = 1.5;
	hModel = MV1LoadModel("Assets//Tile.mv1");
	assert(hModel >= 0);
	int count = 0;
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			if (i % 2 == 1) {
				Tiles[i][j].position = { position.x - tWSize / 2 +tWSize * j,position.y,position.z - tHSize * i };
			}
			else {
				Tiles[i][j].position = { position.x + tWSize * j,position.y,position.z - tHSize * i };
			}
			
			Tiles[i][j].num = count;
			count++;
		}
	}
}

Tile::~Tile()
{
	if(hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
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
}

void Tile::Draw()
{
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			MV1SetMatrix(hModel, Object3D::ChangeFLOAT3ToMATRIX(Tiles[i][j].position, rotation));
			MV1DrawModel(hModel);
		}
	}
}
