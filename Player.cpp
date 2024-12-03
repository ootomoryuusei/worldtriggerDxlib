#include "Player.h"
#include "Ground.h"
#include "Goblin.h"
#include "ImGUI/imgui.h"
#include "Camera.h"

Player::Player(GameObject* parent) : Object3D(parent)
{
	/*static const std::string folder = "Assets/Character/Player/";*/
	hModel = MV1LoadModel("Assets//human.mv1");
	assert(hModel > 0);
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	hSabel = MV1LoadModel("Assets//blade.mv1");
	assert(hSabel > 0);

	//static const std::string filename[MAX] = {
	//	"Anim_Neutral.mv1",
	//	"Anim_Run.mv1",
	//	"Anim_Attack1.mv1",
	//	"Anim_Attack2.mv1",
	//	"Anim_Attack3.mv1",
	//};

	//for (int n = 0; n < MAX; n++) {
	//	hAnimData[n] = MV1LoadModel((folder + filename[n]).c_str());
	//	assert(hAnimData[n] > 0);
	//}
	//animator = new Animator();
	//animator->SetModel(hModel); // 基準のモデルデータ
	//animator->Play(hAnimData[WAIT]); // アニメーション再生
}

Player::~Player()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
	if (hSabel > 0) {
		MV1DeleteModel(hSabel);
		hSabel = -1;
	}
}

void Player::Update()
{
	/*switch (state) {
	case sNORMAL:	updateNormal();  break;
	case sATTACK1:	updateAttack1(); break;
	case sATTACK2:	updateAttack2(); break;
	case sATTACK3:	updateAttack3(); break;
	}

	Goblin* gob = GetParent()->FindGameObject<Goblin>();
	if (gob != nullptr) {
		gob->PushByPlayer(position, position + VGet(0, 160, 0), 30);
	}*/

	/*animator->Update();
	attKey.Update();*/

	//// カメラの設定
	//MATRIX mRot = MGetRotY(rotation.y);  // 回転行列
	//// 回ってないとき、プレイヤーからどれぐらい後ろ？→ベクトル
	//VECTOR tmpP = VGet(0, 200, -300);
	//// これに回転行列をかける
	//VECTOR pRot = tmpP * mRot;
	//// これにプレイヤーの座標を足すと、カメラ位置が出る
	//VECTOR vRot = VGet(0, 100, 300) * mRot;
	//SetCameraPositionAndTarget_UpVecY(position + pRot, position + vRot);

	ImGui::Begin("position");
	ImGui::InputFloat("X", &position.x);
	ImGui::InputFloat("Y", &position.y);
	ImGui::InputFloat("Z", &position.z);
	ImGui::End();
}

void Player::updateNormal()
{
	Camera* pCam = GetParent()->FindGameObject<Camera>();
	float camRotY = pCam->GetRotation().y;

	VECTOR inputDirection = VGet(0, 0, 0);
	{
		int x;
		int y;
		GetJoypadAnalogInput(&x, &y, DX_INPUT_PAD1);
		inputDirection.x = (float)x / 1000.0f;
		inputDirection.z = -(float)y / 1000.0f;
		if (VSize(inputDirection) < 0.3f) { // 中心付近の誤差を除く
			inputDirection = VGet(0, 0, 0);
		}
	}

	if (CheckHitKey(KEY_INPUT_W)) {
		inputDirection.z = 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		inputDirection.z = -1.0f;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		inputDirection.x = 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		inputDirection.x = -1.0f;
	}
//	inputDirection = VNorm(inputDirection); // 入力の向き
	if (VSize(inputDirection) > 1.0f) { // 入力値がオーバーしている
		inputDirection = VNorm(inputDirection);
	}
	if (VSize(inputDirection) > 0.0f) {
		// ToDo：　その向きに移動
		// 方法１：入力から回転角を求めて、atan2(x, z)進行方向を角度で求める
#if 0
		float inputRot = atan2f(inputDirection.x, inputDirection.z); // ここをatan2にする
		MATRIX mRot = MGetRotY(camRotY + inputRot);
		VECTOR move = VGet(0, 0, 300 * Time::DeltaTime()) * VSize(inputDirection);         // 回ってないときの移動ベクトル
		VECTOR add = move * mRot; // ベクトルに行列をかけると、向いてる方への移動量
		position += add;
		rotation.y = camRotY + inputRot;
#endif
		// 方法２：inputDirectionから、移動ベクトルを作る
		VECTOR move = inputDirection * 300.0f * Time::DeltaTime();
		VECTOR add = move * MGetRotY(camRotY);
		position += add;
		rotation.y = atan2f(add.x, add.z);
		// 方法３：入力から回転角を求めて、行列を使って移動ベクトルを作る
		/*animator->Play(hAnimData[RUN]);*/
	}
	else {
		/*animator->Play(hAnimData[WAIT]);*/
	}

/*	if (CheckHitKey(KEY_INPUT_W)) {
		MATRIX mRot = MGetRotY(camRotY);
		VECTOR move = VGet(0, 0, 300 * Time::DeltaTime());         // 回ってないときの移動ベクトル
		VECTOR add = move * mRot; // ベクトルに行列をかけると、向いてる方への移動量
		position += add;
		rotation.y = camRotY;
		animator->Play(hAnimData[RUN]);
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		MATRIX mRot = MGetRotY(camRotY + XM_PI/2.0f);
		VECTOR move = VGet(0, 0, 300 * Time::DeltaTime());         // 回ってないときの移動ベクトル
		VECTOR add = move * mRot; // ベクトルに行列をかけると、向いてる方への移動量
		position += add;
		rotation.y = camRotY + XM_PI / 2.0f;
		animator->Play(hAnimData[RUN]);
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		MATRIX mRot = MGetRotY(camRotY - XM_PI / 2.0f);
		VECTOR move = VGet(0, 0, 300 * Time::DeltaTime());         // 回ってないときの移動ベクトル
		VECTOR add = move * mRot; // ベクトルに行列をかけると、向いてる方への移動量
		position += add;
		rotation.y = camRotY - XM_PI / 2.0f;
		animator->Play(hAnimData[RUN]);
	}
	else {
		animator->Play(hAnimData[WAIT]);
	}
*/
	if (attKey.IsPush()) { // 攻撃１
		Camera* pCam = GetParent()->FindGameObject<Camera>();
		pCam->Vibration(VGet(0, 10, 0));

		/*animator->Play(hAnimData[ATTACK1], false);*/
		state = sATTACK1;
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

void Player::updateAttack1()
{
	/*float time = animator->GetCurrentFrame();*/
	//if (time < 4.0f) {
	//	// ゴブリンに向かって踏み込む
	//	Goblin* pGob = GetParent()->FindGameObject<Goblin>();
	//	// ゴブリンの座標pGob->GetPosition()
	//	// ゴブリンとの距離が70～200の場合で、
	//	// ゴブリンが前方60度以内に入った時
	//	// ゴブリンの方を向いて、ゴブリンに近づく
	//	VECTOR gobPos = pGob->GetPosition();
	//	VECTOR toGob = ToTarget(gobPos);
	//	float len = VSize(toGob);
	//	if (len > 70.0f && len < 200.0f) {
	//		if (InFront(gobPos, ToRad(60.0f))) {
	//			HeadingTo(toGob);
	//			MoveTo(toGob, 40.0f);
	//		}
	//	}
	//}
	//if (time >= 4.0f && time <= 7.0f) {
	//	int wp = MV1SearchFrame(hModel, "wp");
	//	MATRIX mSabel = MV1GetFrameLocalWorldMatrix(hModel, wp);
	//	attack(VGet(0, 0, 0) * mSabel, VGet(0, -150, 0) * mSabel);
	//	// ここでGoblinに攻撃する
	//}
	//if (time >= 8.0f) {
	//	if (attKey.IsPush()) { // 攻撃２
	//		animator->Play(hAnimData[ATTACK2], false);
	//		state = sATTACK2;
	//	}
	//}
	//if (time >= 9.0f) {
	//	if (CheckHitKey(KEY_INPUT_W)) { // 前移動
	//		state = sNORMAL;
	//	}
	//}

}

void Player::updateAttack2()
{
	/*if (animator->IsEnd()) {
		state = sNORMAL;
	}*/
}

void Player::updateAttack3()
{
	/*if (animator->IsEnd()) {
		state = sNORMAL;
	}*/
}

void Player::attack(VECTOR p1, VECTOR p2)
{
	Goblin* pGob = GetParent()->FindGameObject<Goblin>();
	pGob->CheckAttacked(position, prevP1, prevP2, p1, p2);
	prevP1 = p1;
	prevP2 = p2;
}

void Player::Draw()
{
	Object3D::Draw(); // 基底クラスの関数を呼ぶ→Playerキャラを描画する

	/*DrawCapsule3D(position, position + VGet(0, 160, 0), 30, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);*/

	int wp = MV1SearchFrame(hModel, "wp");
	MATRIX mSabel = MV1GetFrameLocalWorldMatrix(hModel, wp);

	// サーベルを描画する
	MV1SetMatrix(hSabel, mSabel);
	MV1DrawModel(hSabel);

	// サーベルの刃は、(0,0,0)～(0,-150,0)にある。これにmSabelをかけると、今の座標が手に入る
	/*DrawLine3D(VGet(0, 0, 0) * mSabel, VGet(0, -150, 0) * mSabel, GetColor(255, 0, 0));*/
}

Player::AttackKey::AttackKey()
{
	current = false;
	previous = false;
}

void Player::AttackKey::Update()
{
	previous = current;
	current = CheckHitKey(KEY_INPUT_M);
}

bool Player::AttackKey::IsPush()
{
	return !previous && current;
}

bool Player::AttackKey::IsPress()
{
	return current;
}
