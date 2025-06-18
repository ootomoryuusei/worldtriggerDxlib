#include "Amatori_Chika.h"
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
}

void Amatori_Chika::Update()
{
	switch (state_)
	{
	case FIRST: break;
	case SECONDE: break;
	case THIRD:
	{
		MoveMent();
		break;
	}
	default:
		break;
	}
}

void Amatori_Chika::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
