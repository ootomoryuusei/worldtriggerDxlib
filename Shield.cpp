#include "Shield.h"
#include<list> 
#include"CharacterGroup.h"

using std::list;

AutoRegister<Shield, TriggerFactory> Shield::register_("SHIELD");

Shield::Shield(GameObject* parent) : Trigger(parent)
{
	hModel = MV1LoadModel("Assets//Model//SampleShield.mv1");
	assert(hModel >= 0);
}

Shield::~Shield()
{
}

void Shield::Initialize()
{
}

void Shield::Update()
{
	matrix = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
}

void Shield::Draw()
{
	MV1SetMatrix(hModel, matrix);
	MV1DrawModel(hModel);
}
