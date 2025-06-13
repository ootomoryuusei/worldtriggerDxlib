#include "Shield.h"

Shield::Shield(GameObject* parent) : Object3D(parent)
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
}

void Shield::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
