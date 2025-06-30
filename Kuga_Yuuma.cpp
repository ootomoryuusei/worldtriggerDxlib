#include "Kuga_Yuuma.h"

AutoRegister<Kuga_Yuuma,CharacterFactory> Kuga_Yuuma::register_("Kuga_Yuuma");

Kuga_Yuuma::Kuga_Yuuma(GameObject* parent) : Character(parent)
{
	hModel = MV1LoadModel("Assets//Model//human.mv1");
	assert(hModel >= 0);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	
	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;
}

Kuga_Yuuma::~Kuga_Yuuma()
{
}

void Kuga_Yuuma::Initialize()
{
}

void Kuga_Yuuma::Update()
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

void Kuga_Yuuma::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
