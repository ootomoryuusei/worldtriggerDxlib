#include "Asteroid.h"

Asteroid::Asteroid(GameObject* parent) : Object3D(parent)
{
	hModel = MV1LoadModel("Assets//Model//SampleAsteroid.mv1");
	assert(hModel >= 0);
}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialize()
{
}

void Asteroid::Update()
{
}

void Asteroid::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
