#include "Kuga_Yuuma.h"

Kuga_Yuuma::Kuga_Yuuma(GameObject* parent) : Character(parent)
{
	hModel = MV1LoadModel("Assets//Model//human.mv1");
	assert(hModel >= 0);
	hBlade = MV1LoadModel("Assets//Model//blade.mv1");
	assert(hBlade >= 0);
	hShield = MV1LoadModel("Assets//Model//SampleSheald.mv1");
	assert(hShield >= 0);
	hAsteroid = MV1LoadModel("Assets//Model//SampleAsteroid.mv1");
	assert(hAsteroid >= 0);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	cPos.x = 0;
	cPos.y = 0;
	prevX = 0;
	prevY = 0;
	prevKey = false;

	cStatus.move = 5;
	cStatus.attack = 4;
	cStatus.speed = 6;
	cStatus.defense = 10;

	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;

	myTrigger_ = {};
}

Kuga_Yuuma::~Kuga_Yuuma()
{
}

void Kuga_Yuuma::Update()
{
}

void Kuga_Yuuma::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
