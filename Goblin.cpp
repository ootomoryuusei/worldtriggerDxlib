#include "Goblin.h"
#include <assert.h>
#include "Ground.h"
#include "Player.h"

Goblin::Goblin(GameObject* parent) : Object3D(parent)
{
	hModel = MV1LoadModel("Assets/Character/Goblin/Goblin.mv1");
	assert(hModel > 0);
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	static const std::string folder = "Assets/Character/Goblin/";
	static const std::string filename[MAX] = {
		"Anim_Neutral.mv1",
		"Anim_Run.mv1",
		"Anim_Damage.mv1",
		"Anim_Blow_In.mv1",
		"Anim_Blow_Loop.mv1",
		"Anim_Blow_Out.mv1",
		"Anim_Down_Loop.mv1",

	};

	for (int n = 0; n < MAX; n++) {
		hAnimData[n] = MV1LoadModel((folder + filename[n]).c_str());
		assert(hAnimData[n] > 0);
	}
	animator = new Animator();
	animator->SetModel(hModel); // 基準のモデルデータ
	animator->Play(hAnimData[WAIT]); // アニメーション再生

	position = VGet(0, 100, 500);
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	animator->Update();

	switch (state) {
	case sNORMAL:
		updateNormal();
		break;
	case sDAMAGE:
		updateDamage();
		break;
	}
}

bool Goblin::PushByPlayer(VECTOR p1, VECTOR p2, float rad)
{
	VECTOR g1 = position;
	VECTOR g2 = position + VGet(0, 160, 0);
	float dist = Segment_Segment_MinLength(p1, p2, g1, g2);
	if (dist < rad + 30) {
		VECTOR dir = g1 - p1; //押される向きと今の距離が入っている
		dir.y = 0;
		float len = VSize(dir); // 今の距離
		float pushLen = rad + 30 - len; // 押す距離

		dir = VNorm(dir); // 長さを1にする（これが向きを表す）
		VECTOR push = dir * pushLen;
		position += push;
		// あたってる
		return true;
	}
	// 当たってない
	return false;
}

bool Goblin::CheckAttacked(VECTOR playerPos, VECTOR p1, VECTOR p2, VECTOR p3, VECTOR p4)
{
	//4頂点のポリゴンと、カプセルが当たっているか
	VECTOR begin = position + VGet(0, 0, 0);
	VECTOR end = position + VGet(0, 100, 0);
	float r1 = Segment_Triangle_MinLength(begin, end, p1, p2, p3);
	float r2 = Segment_Triangle_MinLength(begin, end, p2, p3, p4);
	if (r1 < 30 || r2 < 30) {
		animator->Play(hAnimData[DAMAGE], false); // アニメーション再生
		state = sDAMAGE;
		// ①ゴブリンはプレイヤーの方を向く プレイヤーの座標はplayerPos, 自分の座標はpositionにある。向きは、rotation.yに代入する
		VECTOR direction = playerPos - position; // ゴブリンからプレイヤーへのベクトル
		rotation.y = atan2f(direction.x, direction.z);
		// ②ゴブリンは背中側にノックバックする
		VECTOR push = VNorm(direction) * -30.0f;
		position += push;
		return true;
	}
	return false;
}

void Goblin::updateNormal()
{
	// プレイヤーに向かっていく動き
	Player* pPl = GetParent()->FindGameObject<Player>();
	VECTOR playerPos = pPl->GetPosition(); // プレイヤーの座標
	if (InFront(playerPos, ToRad(10.0f))) { 
		position += FrontVec() * 2.0f; // プレイヤーが正面に居れば前に進む
	}
	else {
		if (InRight(playerPos)) { // プレイヤーの方を向こうとする
			rotation.y += ToRad(3.0f);
		}
		else {
			rotation.y -= ToRad(3.0f);
		}
	}

	// 地面の上に乗せる
	Ground* pG = GetParent()->FindGameObject<Ground>();
	if (pG != nullptr) {
		VECTOR hit;
		if (pG->CheckRayCollision(position + VGet(0, 100, 0), position + VGet(0, -30, 0), &hit)) {
			position = hit;
		}
	}
}

void Goblin::updateDamage()
{
	if (animator->IsEnd()) {
		state = sNORMAL;
		animator->Play(hAnimData[WAIT]);
	}
}
