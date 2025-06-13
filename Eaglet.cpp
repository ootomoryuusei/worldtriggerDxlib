#include "Eaglet.h"

Eaglet::Eaglet(GameObject* parent) : Object3D(parent)
{
	hModel = MV1LoadModel("Assets//Model//SampleEaglet.mv1");
	assert(hModel >= 0);
}

Eaglet::~Eaglet()
{
}

void Eaglet::Initialize()
{
}

void Eaglet::Update()
{
}

void Eaglet::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
