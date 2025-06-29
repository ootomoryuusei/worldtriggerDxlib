#include "Mikumo_Osamu.h"

AutoRegister<Mikumo_Osamu,CharacterFactory> Mikumo_Osamu::register_("Mikumo_Osamu");

Mikumo_Osamu::Mikumo_Osamu(GameObject* parent) :Character(parent)
{
	hModel = MV1LoadModel("Assets//Model//human.mv1");
	assert(hModel >= 0);
	
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;

	myTrigger_ = {};
}

Mikumo_Osamu::~Mikumo_Osamu()
{
}

void Mikumo_Osamu::Initialize()
{
}

void Mikumo_Osamu::Update()
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

void Mikumo_Osamu::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
