#include "Kogetsu.h"

Kogetsu::Kogetsu(GameObject* parent) : Object3D(parent)
{
	hModel = MV1LoadModel("Assets//Model//SampleMoonBlade.mv1");
	assert(hModel >= 0);
}

Kogetsu::~Kogetsu()
{
}

void Kogetsu::Initialize()
{
}

void Kogetsu::Update()
{
}

void Kogetsu::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
