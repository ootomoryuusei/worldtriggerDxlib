#include "Amatori_Chika.h"
#include"Tile.h"
#include<algorithm>

Amatori_Chika::Amatori_Chika(GameObject* parent) : Character(parent)
{
	hModel = MV1LoadModel("Assets//Model//human.mv1");
	assert(hModel >= 0);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	cStatus.move = 5;
	cStatus.attack = 4;
	cStatus.speed = 6;
	cStatus.defense = 10;

	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;

	myTrigger_ = {};
}

Amatori_Chika::~Amatori_Chika()
{
}

void Amatori_Chika::Initialize()
{
	pTile = GetParent()->GetParent()->FindGameObject<Tile>();
}

void Amatori_Chika::Update()
{
	//if (!firstSet) {
	//	for (auto& itr : moveMent) {
	//		dq_moveMent.push_back(itr);
	//	}

	//	int x = dq_moveMent.front() % MAX_MAP_WIDTH;
	//	int y = dq_moveMent.front() / MAX_MAP_WIDTH;
	//	position = pTile->GetTilesData(x,y).position;
	//	firstSet = true;
	//	moveing = true;
	//}
	//if (moveing) {
	//	if (dq_moveMent.size() >= 2) {
	//		auto it = dq_moveMent.begin();
	//		auto startIndex = *it;
	//		auto targetIndex = *(++it);

	//		int x = startIndex % MAX_MAP_WIDTH;
	//		int y = startIndex / MAX_MAP_WIDTH;
	//		VECTOR start = pTile->GetTilesData(x, y).position;
	//		x = targetIndex % MAX_MAP_WIDTH;
	//		y = targetIndex / MAX_MAP_WIDTH;
	//		VECTOR target = pTile->GetTilesData(x, y).position;
	//		float percent = elapsedTime / totalTime;
	//		percent = std::clamp(percent, 0.0f, 1.0f);
	//		position = Lerp3D(start, target, percent);
	//		if (percent >= 1.0f) {
	//			// ˆÚ“®Š®—¹ ¨ Ÿ‚Ì‹æŠÔ‚Ö
	//			elapsedTime = 0.0f;
	//			dq_moveMent.pop_front();
	//		}
	//	}

	//	if (dq_moveMent.size() < 2) {
	//		moveing = false;
	//	}
	//	elapsedTime += Time::DeltaTime();
	//}
}

void Amatori_Chika::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
