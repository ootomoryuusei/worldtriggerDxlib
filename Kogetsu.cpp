#include "Kogetsu.h"


AutoRegister<Kogetsu, TriggerFactory> Kogetsu::register_("KOGETSU");

Kogetsu::Kogetsu(GameObject* parent) : Trigger(parent)
{
	hModel = MV1LoadModel("Assets//Model//SampleKogetsu.mv1");
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
